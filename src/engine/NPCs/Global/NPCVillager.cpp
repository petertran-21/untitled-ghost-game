#include <iostream>
#include <cstdlib>
#include "NPCVillager.h"

using namespace std;

NPCVillager::NPCVillager(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCVillager::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
    }
    state_switch(npc_states::Possessed);
}