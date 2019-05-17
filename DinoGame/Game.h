#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
	AnimatedRect* dino;
	TexRect* background;
	TexRect* background2;
	TexRect* gameover;
	TexRect* bird;

	float currentX;
	float newX;
	float diff;
	float dinoY;
	float dinoX;
	bool backgroundVisible;
	//bool cactusVisible;
	bool hit;
	bool startGame;
	bool gameOver;
	bool birdVisible;
	bool jump;
	bool duck;
	//bool up;

  /*
    bool projectileVisible;
    bool mushroomVisible;
    bool up;
    bool left;
    bool hit;
    float theta;
    float deg;
	*/
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
	void restartGame();
    void action();
	void randomObject();

    ~Game();

};

#endif 
