#include <iostream>
#include <cstdlib>
#include "NPCSkeleton.h"

using namespace std;

NPCSkeleton::NPCSkeleton(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    //this->id = "pyro";
	this->addAnimation("../resources/npcs/", "npc_base", 1, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCSkeleton::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    
    state_switch(npc_states::Possessed);
}

void NPCSkeleton::resolve_collision(DisplayObject *obj){
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
}