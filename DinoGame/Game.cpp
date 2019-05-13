#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	//const char* shroomFileName;
	const char* fireballFileName;
    const char* dinoFileName;
    const char* backgroundFileName;
	const char* bobcatFileName;
	const char* cactusFileName;
	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	//shroomFileName = "../mushroom.png";
	fireballFileName = "../fireball.bmp";
	dinoFileName = "../dinoWalk.png";
	backgroundFileName = "../background.png";
	cactusFileName = "../cactus.png";
	bobcatFileName = "../cat.png";
	#else
	//shroomFileName = "mushroom.png";
	fireballFileName = "fireball.bmp";
    dinoFileName = "dinoWalk.png";
	backgroundFileName = "background.png";
	cactusFileName = "cactus.png";
	bobcatFileName = "cat.png";
	#endif

    //mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    //projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
   // explosion = new AnimatedRect(fireballFileName, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);
	dino = new AnimatedRect(dinoFileName, 2, 1, 100, true, true, -0.95, 0.10, 0.6, 0.35);
	background = new TexRect(backgroundFileName, -2, 1, 4, 2);
	background2 = new TexRect(backgroundFileName, -2, 1, 4, 2);
	cactus = new TexRect(cactusFileName, 0.25, 0.40, 1.0, 0.95);
	bobcat = new AnimatedRect(bobcatFileName, 4, 2, 100, true, false, -0.95, 0.10, 0.6, 0.35);

	dino->playLoop();
	dino->pause();
	
	currentX = background->getX();
	newX = currentX;
	diff = currentX;

	hit = false;
	startGame = false;
	backgroundVisible = true;
	cactusVisible = false;
	setRate(100);
	start();

	/*
    up = false;
    left = true;
    projectileVisible = true;
    mushroomVisible = true;
    theta = 0;
    deg = 0;
    hit = false;
    */
}

void Game::action(){

	float modi = 0.14;
	float dinoY = dino->getY();
	float dinoX = dino->getX();

	if (startGame) {
		dino->resume();

		newX -= modi;
		diff += modi;

		background->setX(newX);
		background2->setX(0 - diff);
		cactus->setX(0- diff);

		if (!(diff < 2)) {
			background->setX(-2.0);
			background2->setX(0.0);
			cactus->setX(1.0);
			diff = -2.0;
			newX = -2.0;
		}
	}

	
	if (cactus->contains(dinoX, dinoY)) {
		dino->pause();
		startGame = false;
		hit = true;
		dino->setW(0.4);
		dino->setH(0.2);
		dino->setY(-0.10);
		stop();
	}

}

void Game::draw() const {
	if (backgroundVisible) {
		background->draw(0.0);
		background2->draw(0.0);
		dino->draw(1.0);
		cactus->draw(1.0);
	}
}

void Game::handleKeyDown(unsigned char key, float x, float y){
	//bobcat = new AnimatedRect(bobcatFileName, 4, 2, 100, true, false, -0.95, 0.0, 0.6, 0.35);
	//AnimatedRect(const char* map_filename, int rows, int cols, int rate, bool visible = false, bool animated = false, float x = 0, float y = 0, float w = 0.5, float h = 0.5)
	
    if (key == ' '){
		dinoY =  0.50;
			dinoY += 0.05;
			dino->setY(dinoY);
	

		startGame = true;
    }
	else if (key == 'w') {
		dino->setY(0.50);
		startGame = true;
	}
	else if (key == 's') {
		dino->setH(0.20);
		dino->setY(-0.05);
	}
}

void Game::handleKeyUp(unsigned char key, float x, float y) {
	if (key == ' ') {

		dino->setY(0.10);
		startGame = true;
	}
	else if(key == 'w') {
		dino->setY(0.10);
		startGame = true;
	}
	else if(key == 's') {
		dino->setH(0.35);
		dino->setY(0.10);
	}
}

Game::~Game(){
    stop();
   // delete mushroom;
    //delete explosion;
    //delete projectile;
	delete background;
	delete background2;
	delete dino;
}
