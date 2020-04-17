#include <iostream>
#include <cstdlib>
#include "Pirate.h"

using namespace std;

Pirate::Pirate() : MainBoss(){
    this->subtype = PIRATE_SUBTYPE;
	this->addAnimation("./resources/bosses/", "pirate_idle", 1, 1, false);
	this->play("pirate_idle");

    // this->collisionContainer = container;
    // this->drawingContainer = allSprites;
}

void Pirate::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainBoss::update(pressedKeys, currState);

    if (this->state == boss_states::Death){
        //this->play("pirate_death");
        cout << "PIRATE STATE: DEATH" << endl;
        this->alpha = 0;
    }
}

void Pirate::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	// this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
	// this->play("npc_base");
}

void Pirate::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "PIRATE STATE: ATTACK" << endl;
    }
    state_switch(boss_states::Idle);
}

void Pirate::resolve_collision(DisplayObject *obj){
        cout << "PIRATE WAS HIT BY A CRAB" << endl;
        this->state = boss_states::Death;

}