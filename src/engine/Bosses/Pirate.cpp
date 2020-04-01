#include <iostream>
#include <cstdlib>
#include "Pirate.h"

using namespace std;

Pirate::Pirate() : MainBoss(){
    this->position.x = 100;
    this->position.y = 100;
	// this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
	// this->play("npc_base");
}

void Pirate::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ATTACK" << endl;
    }
    state_switch(boss_states::Idle);
}