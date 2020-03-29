#include <iostream>
#include <cstdlib>
#include "NPCArcher.h"

using namespace std;

NPCArcher::NPCArcher() : MainNPC(){
    //this->id = "archer";
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
}

void NPCArcher::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        if (abilityPt.x != 0 || abilityPt.y != 0){
            Arrow *arr = new Arrow(abilityPt, dir);
            this->addChild(arr);
        }
    }
    state_switch(npc_states::Possessed);
}