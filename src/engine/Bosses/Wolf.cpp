#include <iostream>
#include <cstdlib>
#include "Wolf.h"
#include "MainNPC.h"

using namespace std;

Wolf::Wolf(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainBoss(){
    this->subtype = WOLF_SUBTYPE;
    this->id = "wolfBoss";

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

    if (!stunned){
        bark_timer++;
        if (bark_timer == bark_timer_max) state_switch(boss_states::Attack);
    }
    else {
        stun_timer++;
        if (stun_timer == 180){
            stunned = false;
            stun_timer = 0;
        }
    }

}

void Wolf::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "WOLF STATE: ATTACK" << endl;
        //BARK
        for (int i=0; i < 8; i++){
            Bark *b = new Bark(position, (M_PI/4 + bark_angle)*i, collisionContainer, drawingContainer);
        }

        bark_angle += M_PI/16;
        
	}
	//anything that should always run while in this state
    this->play("wolf_attack");
    bark_timer++;
    if (bark_timer == bark_timer_max+20) state_switch(boss_states::Idle);
}

void Wolf::resolve_collision(DisplayObject *obj){
    Arrow *a = dynamic_cast<Arrow*>(obj);
    if (a){
        stunned = true;
    }
}