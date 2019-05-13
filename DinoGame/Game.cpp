#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	//const char* shroomFileName;
	//const char* fireballFileName;
    const char* dinoFileName;
    const char* backgroundFileName;
	const char* bobcatFileName;
	const char* cactusFileName;
	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	//shroomFileName = "../mushroom.png";
	//fireballFileName = "../fireball.bmp";
	dinoFileName = "../dino.png";
	backgroundFileName = "../background.png";
	cactusFileName = "../cactus.png";
	bobcatFileName = "../cat.png";
	#else
	//shroomFileName = "mushroom.png";
	//fireballFileName = "fireball.bmp";
    //dinoFileName = "dino.png";
	backgroundFileName = "background.png";
	cactusFileName = "cactus.png";
	bobcatFileName = "cat.png";
	#endif

    //mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    //dino = new AnimatedRect(dinoFileName, )
    //projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    //explosion = new AnimatedRect(fireballFileName, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);
	background = new TexRect(backgroundFileName, -2, 1, 4, 2);
	background2 = new TexRect(backgroundFileName, -2, 1, 4, 2);
	cactus = new TexRect(cactusFileName, 0.25, 0.1, 0.15, 0.25);
	bobcat = new AnimatedRect(bobcatFileName, 4, 2, 100, true, false, -0.95, 0.10, 0.6, 0.35);

	bobcat->playLoop();
	currentX = background->getX();
	newX = currentX;
	diff = currentX;

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

	newX -= modi;
	diff += modi;

	background->setX(newX);
	background2->setX(0 - diff);

	if (!(diff < 2)) {
		background->setX(-2.0);
		background2->setX(0.0);
		diff = -2.0;
		newX = -2.0;
		if (background2->getX() == 0.0) {
			cactusVisible = true;
		}
		else {
			cactusVisible = false;
		}
	}


	/*
    float mx = 0.5;
    float my = 0;
    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    
//    if (left)
//        mx -= 0.0005;
//    else
//        mx += 0.0005;
//
//    if (mx < -1.6f){
//        left = false;
//    }
//    if (mx > 1.6 - mushroom->getW()){
//        left = true;
//    }
    
    
    mushroom->setX(mx - mushroom->getW()/2);
    mushroom->setY(my + mushroom->getH()/2);
    
    theta += 0.001;
    deg += 0.1;
    

    if (!hit && up){
        float ypos = projectile->getY();
        ypos +=0.005;
        projectile->setY(ypos);

        if (mushroom->contains(0, ypos-0.005)){
            up = false;
            hit = true;
            projectileVisible = false;
            mushroomVisible = false;
            explosion->setX(mushroom->getX());
            explosion->setY(mushroom->getY());
            explosion->playOnce();
        }
    }
    
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
    }
	*/
}

void Game::draw() const {
	if (backgroundVisible){
		background->draw(0.0);
		background2->draw(0.0);
		bobcat->draw(1.0);
	}
	if (cactusVisible) {
		cactus->draw(0.0);
	}
	/*
    if (projectileVisible){
        projectile->draw();
    }
    if (mushroomVisible){
        mushroom->draw(0.0);
    }
    explosion->draw(0.1);
	*/
}

void Game::handleKeyDown(unsigned char key, float x, float y){
	//bobcat = new AnimatedRect(bobcatFileName, 4, 2, 100, true, false, -0.95, 0.0, 0.6, 0.35);
	//AnimatedRect(const char* map_filename, int rows, int cols, int rate, bool visible = false, bool animated = false, float x = 0, float y = 0, float w = 0.5, float h = 0.5)
    if (key == ' '){
		bobcat->setY(0.45);
    }
	else if (key == 'w') {
		bobcat->setY(0.45);
	}
	else if (key == 's') {
		bobcat->setH(0.20);
		bobcat->setY(-0.05);
	}
}

void Game::handleKeyUp(unsigned char key, float x, float y) {
	
	if (key == ' ') {
		bobcat->setY(0.10);
	}
	else if(key == 'w') {
		bobcat->setY(0.10);
	}
	else if(key == 's') {
		bobcat->setH(0.35);
		bobcat->setY(0.10);
	}
}

Game::~Game(){
    stop();
   // delete mushroom;
    //delete explosion;
    //delete projectile;
	delete background;
	delete background2;
	delete bobcat;
}
