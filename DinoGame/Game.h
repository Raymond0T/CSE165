#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
    //TexRect* mushroom;
	//AnimatedRect* dino;
	AnimatedRect* bobcat;
    //Rect* projectile;
	TexRect* background;
	TexRect* background2;
	TexRect* cactus;

	float currentX;
	float newX;
	float diff;
	bool backgroundVisible;
	bool cactusVisible;
	bool hit;
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

    void action();

    ~Game();

};

#endif 
