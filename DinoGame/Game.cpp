#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

    const char* dinoFileName;
    const char* backgroundFileName;
	const char* bobcatFileName;
	const char* gameoverFileName;
	const char* birdFileName;

	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	dinoFileName = "../dinoWalk.png";
	backgroundFileName = "../background.png";
	gameoverFileName = "../gameover.png";
	birdFileName = "../bird.png";
	#else

    dinoFileName = "dinoWalk.png";
	backgroundFileName = "background.png";
	gameoverFileName = "gameover.png";
	birdFileName = "bird.png";
	#endif

    //mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    //projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
   // explosion = new AnimatedRect(fireballFileName, 6, 6, 64, false, false, -0.25, 0.8, 0.5, 0.5);
	dino = new AnimatedRect(dinoFileName, 2, 1, 100, true, true, -0.95, 0.10, 0.6, 0.35);
	background = new TexRect(backgroundFileName, -2, 1, 4, 2);
	background2 = new TexRect(backgroundFileName, -2, 1, 4, 2);
	gameover = new TexRect(gameoverFileName,- 0.35, 0.50, 1.0, 0.95);
	bird = new TexRect(birdFileName, 0.25, 0.35, 0.7, 0.5);
	

	dino->playLoop();
	dino->pause();
	
	
	currentX = background->getX();
	newX = currentX;
	diff = currentX;

	//up = true;
	jump = false;
	duck = false;
	birdVisible = true;
	gameOver = false;
	hit = false;
	startGame = false;
	backgroundVisible = true;
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
		//randomObject(diff);
		//bird->setX(0 - diff);

		if (!(diff < 2)) {
			background->setX(-2.0);
			background2->setX(0.0);
			//bird->setX(1.0);
			diff = -2.0;
			newX = -2.0;
		}
	}

	if (jump || duck) {
		//randomObject();

		float currentBird = bird->getX();
		float newBird = currentBird;
		float birdDiff = currentBird;
		float birdMove = 0.14;

		birdDiff += currentBird;
		bird->setX(0 - diff);

		if (bird->contains(dinoX + 0.23, dinoY-0.18)) {
			//dino->pause();
			//startGame = false;
			//hit = true;
			//gameOver = true;
			restartGame();
		}
	}
}

/*
void Game::detect() {
	float currentBird = bird->getX();
	float newBird = currentBird;
	float birdDiff = currentBird;
	float birdMove = 0.14;

	birdDiff += currentBird;
	bird->setX(0 - diff);


	/*
if (cactus->contains(dinoX - 0.10, dinoY)) {
	dino->pause();
	startGame = false;
	hit = true;
	gameOver = true;
}


	if (bird->contains(dinoX - 10, dinoY - 10)) {
		dino->pause();
		startGame = false;
		hit = true;
		gameOver = true;
	}
}
*/
void Game::draw() const {
	if (backgroundVisible) {
		background->draw(0.0);
		background2->draw(0.0);
		if (gameOver) {
			gameover->draw(1.0);
		}
		dino->draw(1.0);
		if (birdVisible) {
			bird->draw(1.0);
		}
	}
}


void Game::randomObject() {
	srand(time(0));
	
	int pick = rand() % 2;

	if (pick == 0) {
		bird->setY(0.35);
	}
	else {
		bird->setY(0.15);
	}
}


void Game::handleKeyDown(unsigned char key, float x, float y){
	// *********************NEED TO HOLD KEY DOWN FOR "1 - 2 SECONDS " SO GAMEOVER WILL BE GONE****************************************
	
    if (key == ' '){
		dino->setY(0.50);
		startGame = true;
		//up = true;
		gameOver = false;
		jump = true;
    }
	else if (key == 'w') {
		dino->setY(0.50);
		startGame = true;
		gameOver = false;
		jump = true;
	}
	else if (key == 's') {
		dino->setH(0.20);
		dino->setY(-0.05);
		duck = false;
	}
	else if (key == 'r') {
		restartGame();
	}
	else if (key == 'p') {
		dino->pause();
	}
	else if (key == 'c') {
		dino->resume();
	}
}



void Game::handleKeyUp(unsigned char key, float x, float y) {
	// *********************NEED TO HOLD KEY DOWN FOR "1 - 2 SECONDS " SO GAMEOVER WILL BE GONE****************************************
	if (key == ' ') {
		dino->setY(0.10);
		startGame = true;
		gameOver = false;
		jump = true;
		randomObject();
	}
	else if(key == 'w') {
		dino->setY(0.10);
		startGame = true;
		gameOver = false;
		jump = true;
		randomObject();
	}
	else if(key == 's') {
		dino->setH(0.35);
		dino->setY(0.10);
		duck = true;
		randomObject();
	}
}


void Game::restartGame() {
	dino->pause();
	hit = false;
	gameOver = true;
	startGame = false;
	backgroundVisible = true;
	background->setX(-2);
	background2->setX(-2);
	bird->setX(0.25);
	dino->setY(0.10);
	dino->setH(0.35);
	dino->setW(0.60);

}


Game::~Game(){
    stop();
	delete background;
	delete background2;
	delete dino;
}
