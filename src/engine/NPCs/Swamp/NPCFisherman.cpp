#include <iostream>
#include <cstdlib>
#include "NPCFisherman.h"

using namespace std;

NPCFisherman::NPCFisherman() : MainNPC(){
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
}

void NPCFisherman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
    }
    state_switch(npc_states::Possessed);
}