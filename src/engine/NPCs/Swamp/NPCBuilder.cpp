#include <iostream>
#include <cstdlib>
#include "NPCBuilder.h"

using namespace std;

NPCBuilder::NPCBuilder(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCBuilder::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
    }
    state_switch(npc_states::Possessed);
}

void NPCBuilder::resolve_collision(DisplayObject * obj){ 
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);

}