#include <iostream>
#include <cstdlib>
#include "Dragon.h"

using namespace std;

Dragon::Dragon() : MainBoss(){
    this->position.x = 100;
    this->position.y = 100;
	// this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
	// this->play("npc_base");
}

void Dragon::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
}


void Dragon::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ATTACK" << endl;
    }
    state_switch(boss_states::Idle);
}