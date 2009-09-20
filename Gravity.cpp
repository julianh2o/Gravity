/*
 *  Gravity.cpp
 *  Gravity
 *
 *  Created by Julian on 8/16/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Gravity.h"

Gravity::Gravity() {
//	printf("sizeof ship: %d\n",sizeof(Ship));
//	printf("sizeof proj: %d\n",sizeof(Projectile));
//	printf("sizeof planet: %d\n",sizeof(Planet));
//	printf("sizeof vect: %d\n",sizeof(Vector2D));
	srand(time(NULL));
	k = new KeyBinding();
	v = new View(200,200);
	fullscreen = false;
	
	k->bind("up",SDLK_w);
	k->bind("left",SDLK_a);
	k->bind("down",SDLK_s);
	k->bind("right",SDLK_d);
	k->bind("fire",SDLK_SPACE);
	k->bind("reset",SDLK_BACKQUOTE);
	
	k->bind("pan_up",SDLK_UP);
	k->bind("pan_left",SDLK_LEFT);
	k->bind("pan_down",SDLK_DOWN);
	k->bind("pan_right",SDLK_RIGHT);
	
	k->bind("zoom_out",SDLK_MINUS);
	k->bind("zoom_in",SDLK_EQUALS);

	k->bind("equip 1",SDLK_1);
	k->bind("equip 2",SDLK_2);
	
	k->bind("pause",SDLK_ESCAPE);
	
	planets.push_back(new Planet(400,-50,20,50));
	planets.push_back(new Planet(500,500,35,150));
//	planets.push_back(new Planet(600,350,5,30));

	eq = new EquipmentCollection();
	
//	Thruster(double thrust, double usageDrain, double usageHeat, double heatCapacity, double coolingRate, double mass);
	PartSet * thrusters = new PartSet();
	thrusters->addPart(new Thruster(50, 15, 40, 20, 20, 1));
	thrusters->addPart(new Thruster(200, 60, 100, 20, 20, 1));
	thrusters->addPart(new Thruster(200, 10, 10, 20, 20, 1));
	eq->setPartSet(EquipmentCollection::THRUSTER,thrusters);

//	Capacitor(double capacity, double overchargeLeak, double mass);
	PartSet * capacitors = new PartSet();
	capacitors->addPart(new Capacitor(100, 2, 1));
	capacitors->addPart(new Capacitor(200, 1, 3));
	eq->setPartSet(EquipmentCollection::CAPACITOR,capacitors);
	
//	Generator(double energyOutput, double emergencyOutput, double usageHeat, double heatCapacity, double coolingRate, double mass);
	PartSet * generators = new PartSet();
	generators->addPart(new Generator(5, 2, 5, 100, 3, 1));
	generators->addPart(new Generator(7, 4, 7, 100, 3, 2));
	eq->setPartSet(EquipmentCollection::GENERATOR,generators);
	
//	Radiator(double coolingRate, double emergencyRate, double energyDrain, double flashCoolingRate, double flashCoolingCapacity, double flashCoolingRecharge, double mass);
	PartSet * radiators = new PartSet();
	radiators->addPart(new Radiator(1, 5, 10, 3, 50, 30, 5, 1));
	radiators->addPart(new Radiator(2, 5, 15, 3, 50, 30, 5, 2));
	eq->setPartSet(EquipmentCollection::RADIATOR,radiators);

	ship = new Ship(200,200);
	ship->equip(thrusters->getPartAt(0));
	ship->equip(capacitors->getPartAt(0));
	ship->equip(generators->getPartAt(0));
	ship->equip(radiators->getPartAt(0));

	menu = new EquipMenu(eq, ship);

	for (int i=0; i<5; i++) {
		Ship * enemy = new Ship(rand()%600,rand()%600);
		enemy->equip(thrusters->getPartAt(2));
		enemy->equip(capacitors->getPartAt(0));
		enemy->equip(generators->getPartAt(0));
		enemy->equip(radiators->getPartAt(0));
		enemies.push_back(enemy);
	}
	
	Vector2D a = planets[0]->getPos();
	Vector2D diff = *ship - a;
	double rad = diff.getMagnitude();
	double mass = planets[0]->getMass();
	double mu = mass*GRAV_G;
	double v = sqrt(mu/rad);
	double ang = diff.getAngle();
	ang += M_PI/4;
	Vector2D thrust = Vector2D(ang)*v;
	ship->incVel(thrust);
}

void Gravity::update(int delta) {
	menu->update(delta);
	if (paused) return;
	int loopDelta = 10;
	int cdelta = delta;
	while(cdelta > 0) {
		cdelta -= loopDelta;
	
		if (k->check("left")) ship->incHeading(-pps(3,loopDelta));
		if (k->check("right")) ship->incHeading(pps(3,loopDelta));
		if (k->check("up")) {
			ship->thrust(loopDelta);
		}

		if (k->check("fire") && reloadTime <= 0) {
//			Vector2D pos = Vector2D(ship->getX(), ship->getY());
			int shotSpeed = 200;
			Projectile * shot = new Projectile(); //ship->getVel()
			shot->set(ship->getX(),ship->getY());
			shot->setVel(ship->getVel());
			shot->setMass(1);
			shot->setLife(10000);
			shot->incVel(Vector2D(ship->getHeading())*shotSpeed);
			shot->setHeading(ship->getHeading());
			projectiles.push_back(shot);
			reloadTime = 200;
		}
		if (reloadTime > 0) reloadTime-=loopDelta;
		
		if (k->check("reset")) {
			ship->set(-50,200);
			ship->setVel(0,0);		
		}
		
		int panSpeed = 300;
		if (k->check("pan_up")) v->incY(-pps(panSpeed,loopDelta));
		if (k->check("pan_down")) v->incY(pps(panSpeed,loopDelta));
		if (k->check("pan_left")) v->incX(-pps(panSpeed,loopDelta));
		if (k->check("pan_right")) v->incX(pps(panSpeed,loopDelta));
		v->set(ship->getX(), ship->getY());


		for (int i=0; i<planets.size(); i++) {
			if (planets[i]->distanceTo(ship) < planets[i]->getRadius()) {
				ship->set(-50,200);
				ship->setVel(0,0);
			}
			planets[i]->affect(ship,loopDelta);
			for (int l=0; l < enemies.size(); l++) {
				planets[i]->affect(enemies[l],loopDelta);
				if (planets[i]->distanceTo(enemies[l]) < planets[i]->getRadius()) {
					enemies[l]->kill();
				}
			}
		}

		
		for (int i=0; i<projectiles.size(); i++) {
/*			Projectile * proj = projectiles[i];
			Vector2D target = v->getMouse();
			target -= Vector2D(*proj);
			double bearing = target.getAngle();
			double angleDiff = angleTo(proj->getHeading(),bearing);
			if (fabs(angleDiff) > M_PI/100) {
				double turnSpeed = pps(M_PI,loopDelta);
				double turn = fmin(fabs(angleDiff),turnSpeed);
				if (angleDiff > 0) {
					proj->incHeading(-turn);
				} else {
					proj->incHeading(turn);						
				}
			}
			proj->setVel(Vector2D(proj->getHeading())*300);*/
			
			for (int l=0; l<planets.size(); l++) {
				if (planets[l]->distanceTo(projectiles[i]) < planets[l]->getRadius()) {
					projectiles[i]->setLife(0);
				}
				planets[l]->affect(projectiles[i],loopDelta);
			}
			
			int targetEnemy = -1;
			for (int l=0; l < enemies.size(); l++) {
				Vector2D diff = *projectiles[i] - *enemies[l];
				//SEEK
				double searchDistance = 800;
				double coneSlope = .3;
				double mag = diff.getMagnitude();
				double angle = diff.getAngle();
				double angto = fabs(angleTo(projectiles[i]->getHeading(),angle));
				if (angto < coneSlope*mag && mag < searchDistance) {
					//FOUND
					if (targetEnemy == -1 || (projectiles[i]->distanceTo(enemies[targetEnemy]) > projectiles[i]->distanceTo(enemies[l]))) {
						targetEnemy = l;
					}
				}

				
				//DESTROY
				if (diff.getMagnitude() < 7) {
					for (int j=0; j<200; j++) {
						int angle = rand()%360;
						int mag = rand()%20;
						int size = rand()%30;
						Particle * p = new Particle();
						p->setX(enemies[l]->getX());
						p->setY(enemies[l]->getY());
						Vector2D vel(M_PI*(angle/180.0));
						vel *= mag;
						vel += enemies[l]->getVel();
						p->setVel(vel.getX(),vel.getY());
						p->setMass(size/10.0);
						particles.push_back(p);
					}
					enemies[l]->kill();
					projectiles[i]->kill();
				}
			}
			projectiles[i]->targetEnemy = targetEnemy;
			
			
			projectiles[i]->update(loopDelta);
			if (projectiles[i]->isDead()) {
				delete projectiles[i];
				projectiles.erase(projectiles.begin()+i);
				i--;
			}
		}
		
		for (int i=0; i < particles.size(); i++) {
			for (int l=0; l < planets.size(); l++) {
				planets[l]->affect(particles[i],loopDelta);
				if (planets[l]->distanceTo(particles[i]) < planets[l]->getRadius()) {
					particles[i]->kill();
				}
			}
			particles[i]->update(loopDelta);
			if (particles[i]->isDead()) {
				delete particles[i];
				particles.erase(particles.begin()+i);
				i--;
			}
		}
		
		for (int i=0; i < enemies.size(); i++) {
			if (enemies[i]->isDead()) {
				delete enemies[i];
				enemies.erase(enemies.begin()+i);
				i--;
				continue;
			}
			enemies[i]->update(loopDelta);
			
			
			int lookAhead = 2000;
			int cLook = 0;
			bool collide = false;
			int collidedPlanet = -1;
			Inertial * ghost = new Inertial(*enemies[i]);
			int loopDelta = 10;
			while(cLook < lookAhead) {
				cLook += loopDelta;
				float color = (float)(lookAhead-cLook)/lookAhead;
				glColor3f(color,0.0,color);
				gvi(ghost->getX(), ghost->getY());
				for (int l=0; l<planets.size(); l++) {
					planets[l]->affect(ghost,loopDelta);
					if (planets[l]->distanceTo(ghost) < planets[l]->getRadius()) {
						collide = true;
						collidedPlanet = l;
						break;
					}
				}
				if (collide) break;
				ghost->updatePos(loopDelta);
				gvi(ghost->getX(),ghost->getY());
				double dAngle = ghost->getVel().getAngle() - ship->getVel().getAngle();
				if (ghost->distanceTo(ship) < 3 && fabs(dAngle) < M_PI/48 && cLook > lookAhead/10 ) break;
			}
			delete ghost;
			if (collide) {
				Vector2D diff = *enemies[i] - planets[collidedPlanet]->getPos();
				double ang = diff.getAngle();
				double left = ang + M_PI/4;
				double right = ang + M_PI/4;
				double velAng = enemies[i]->getVel().getAngle();
				double thrustDirection = 0;
				if (fabs(left-velAng) > fabs(right-velAng)) {
					thrustDirection = right;
				} else {
					thrustDirection = left;
				}
				enemies[i]->setHeading(thrustDirection);
				enemies[i]->thrust(loopDelta);
			}
			enemies[i]->setHeading(enemies[i]->getVel().getAngle());
		}
		ship->update(loopDelta);
			
		v->update(loopDelta);
	}
}

void Gravity::draw() {
	glPushMatrix();
	v->apply();
	
	Color(255,255,255).set();
	glBegin(GL_POLYGON);
	Vector2D mouse = v->getMouse();
	dot(mouse.getX(), mouse.getY(), 7);
	glEnd();
	
/*	glBegin(GL_LINES);
	for(int i=0; i<projectiles.size(); i++) {
		gvi(projectiles[i]->getX(),projectiles[i]->getY());
		Vector2D target = v->getMouse();
		target -= Vector2D(*projectiles[i]);
		target = target.getUnitVector()*10 + Vector2D(projectiles[i]->getX(), projectiles[i]->getY());
		gvi(target);
	}
	glEnd();*/
	
	for (int i=0; i<projectiles.size(); i++) {
		drawPrediction(projectiles[i]);
	}
	drawPrediction(ship);
	
	glColor3f(1.0,1.0,1.0);
	
	for(int i=0; i<enemies.size(); i++) {
		enemies[i]->draw();
		bool targeted = false;
		for (int l = 0; l<projectiles.size(); l++) {
			if (projectiles[l]->targetEnemy == i) {
				targeted = true;
				break;
			}
		}
		if (targeted) {
			glBegin(GL_LINE_LOOP);
			dot(enemies[i]->getX(),enemies[i]->getY(),50);
			glEnd();
		}
	}
	
	for(int i=0; i<particles.size(); i++) {
		particles[i]->draw();
	}
	
	ship->draw();
	for (int i=0; i<planets.size(); i++) {
		planets[i]->draw();
	}
	
	for (int i=0; i<projectiles.size(); i++) {
		double heading = projectiles[i]->getHeading();
		double dist = 800;
		double coneslope = .3;
		Color(255,255,255).set();
		Vector2D ppos = Vector2D(projectiles[i]->getX(),projectiles[i]->getY());
		Vector2D left = ppos + Vector2D(heading-coneslope)*dist;
		Vector2D right = ppos + Vector2D(heading+coneslope)*dist;
		glBegin(GL_LINE_LOOP);
		gvi(left);
		gvi(right);
		gvi(ppos);
		glEnd();
		
		projectiles[i]->draw();		
	}

	glPopMatrix();
	
	//gui
	glPushMatrix();
	v->applyGUI();
	
	if (paused) menu->draw();
	
	Color(255,255,255).set();
//	for (int l = 0; l < thrusters->size(); l++) {
//		std::vector<Attribute> attribs = thrusters[l]->getAttributes();
//		for (int i=0; i<attribs.size(); i++) {
//			drawText(100+280*l,100+20*i,attribs[i].getString(),GLUT_BITMAP_HELVETICA_10);
//		}
//	}
	
	glBegin(GL_POLYGON);
	glEnd();
	Ship * monitor = ship;
	if (monitor) {
		Color heat = Color(221,57,217);
		Color overHeat = Color(255,0,0);
		makeBar(10,10,10,50,monitor->getEnergy(),monitor->getCapacitor()->getCapacity(),false, Color(50,50,50), Color(0,0,255));
		
		Color use = heat;
		if (ship->isThrusterOverheating()) use = overHeat;
		makeBar(30,10,10,50,monitor->getThrusterHeat(),monitor->getThruster()->getHeatCapacity(),false, Color(50,50,50), use);
		use = heat;
		if (ship->isGeneratorOverheating()) use = overHeat;
		makeBar(50,10,10,50,monitor->getGeneratorHeat(),monitor->getGenerator()->getHeatCapacity(),false, Color(50,50,50), use);
		use = Color(150,150,255);
		makeBar(70,10,10,50,monitor->getFlashCooling(),monitor->getRadiator()->getFlashCoolingCapacity(),false, Color(50,50,50), use);
	}
	//end gui
	glPopMatrix();
}

void Gravity::mouseMoved(SDL_Event event) {
	v->setMouse(event.motion.x, event.motion.y);
}

void Gravity::mouseButton(SDL_Event event) {
//	k->handleMouseEvent(event);
}

void Gravity::keyDown(SDL_Event event) {
	k->handleKeyEvent(event);
	if (k->check("zoom_in",event)) v->zoomIn();
	if (k->check("zoom_out",event)) v->zoomOut();
//	if (k->check("equip 1",event)) ship->equip(thrusters[0]);
//	if (k->check("equip 2",event)) ship->equip(thrusters[1]);
	if (k->check("pause",event)) paused = !paused;
	
	if (k->check("pan_left",event)) menu->left();
	if (k->check("pan_right",event)) menu->right();
	if (k->check("pan_up",event)) menu->up();
	if (k->check("pan_down",event)) menu->down();

	if (event.key.keysym.sym == SDLK_f && (event.key.keysym.mod & KMOD_LMETA || event.key.keysym.mod & KMOD_RMETA)) {
		fullscreen = !fullscreen;
		if (fullscreen) {
			const SDL_VideoInfo * vi = SDL_GetVideoInfo();
			
			int resx = vi->current_w;
			int resy = vi->current_h;
			SDL_SetVideoMode(resx, resy, 0, SDL_OPENGL | SDL_FULLSCREEN);
		} else {
			SDL_SetVideoMode(1024, 640, 0, SDL_OPENGL);
		}
	}
}

void Gravity::keyUp(SDL_Event event) {
	k->handleKeyEvent(event);
}

void Gravity::drawPrediction(Inertial * target) {
	glBegin(GL_LINES);
	int lookAhead = 20000;
	int cLook = 0;
	bool collide = false;
	Inertial * ghost = new Inertial(*target);
	int loopDelta = 10;
	while(cLook < lookAhead) {
		cLook += loopDelta;
		float color = (float)(lookAhead-cLook)/lookAhead;
		glColor3f(color,0.0,color);
		gvi(ghost->getX(), ghost->getY());
		for (int l=0; l<planets.size(); l++) {
			planets[l]->affect(ghost,loopDelta);
			if (planets[l]->distanceTo(ghost) < planets[l]->getRadius()) {
				collide = true;
				break;
			}
		}
		if (collide) break;
		ghost->updatePos(loopDelta);
		gvi(ghost->getX(),ghost->getY());
		double dAngle = ghost->getVel().getAngle() - ship->getVel().getAngle();
		if (ghost->distanceTo(ship) < 3 && fabs(dAngle) < M_PI/48 && cLook > lookAhead/10 ) break;
	}
	delete ghost;
	glEnd();
}