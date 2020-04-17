#include <iostream>
#include <cstdlib>
#include "Wolf.h"
#include "MainNPC.h"

using namespace std;

Wolf::Wolf(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainBoss(){
    this->subtype = WOLF_SUBTYPE;

    this->collisionContainer = container;
    this->drawingContainer = allSprites;

	this->addAnimation("./resources/bosses/", "wolf_idle", 1, 1, false);
    this->addAnimation("./resources/bosses/", "wolf_attack", 1, 1, false);

    this->play("wolf_idle");
}

void Wolf::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "WOLF STATE: IDLE" << endl;
        bark_timer = 0;
	}
	//anything that should always run while in this state
	this->play("wolf_idle");
    bark_timer++;
    if (bark_timer == bark_timer_max) state_switch(boss_states::Attack);

}

void Wolf::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "WOLF STATE: ATTACK" << endl;

        
	}
	//anything that should always run while in this state
    this->play("wolf_attack");
    bark_timer++;
    if (bark_timer == bark_timer_max+20) state_switch(boss_states::Idle);
}