#include <iostream>
#include <cstdlib>
#include "Wolf.h"

using namespace std;

Wolf::Wolf() : MainBoss(){
    this->subtype = "wolf";
    this->position.x = 100;
    this->position.y = 100;

	this->addAnimation("./resources/bosses/", "wolf_idle", 1, 1, false);
	this->play("wolf_idle");
}

void Wolf::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ATTACK" << endl;
        // FORCE GHOST TO EJECT FROM NPC
    }
    state_switch(boss_states::Idle);
}