#include <iostream>
#include <cstdlib>
#include "NPCPyromancer.h"

using namespace std;

NPCPyromancer::NPCPyromancer() : MainNPC(){
    //this->id = "pyro";
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
}

void NPCPyromancer::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        if (abilityPt.x != 0 || abilityPt.y != 0){
            Fire *f = new Fire(abilityPt); 
            this->addChild(f);
        }
    }
    state_switch(npc_states::Possessed);
}