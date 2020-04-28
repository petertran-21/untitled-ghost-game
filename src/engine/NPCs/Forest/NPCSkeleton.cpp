#include <iostream>
#include <cstdlib>
#include "NPCSkeleton.h"

using namespace std;

NPCSkeleton::NPCSkeleton(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
	this->addAnimation("./resources/npcs/skeleton/", "bones", 1, 1, true);
    this->addAnimation("./resources/npcs/skeleton/", "skeleton", 1, 1, true);

    this->inventory = &passedInventory;
	this->play("bones");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCSKELETON_SUBTYPE;
    this->grid_size = 0;
}

void NPCSkeleton::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPC::update(pressedKeys, currState);
    if (alive){
        this->play("skeleton");
        this->grid_size = 100;

        //collapse into bones
        if (life_timer >= life_timer_max){
            life_timer = 0;
            alive = false;
            this->play("bones");
            this->grid_size = 0;

            //eject ghost from  NPC
            state_switch(npc_states::Idle);
            is_possessed = false;
        }
        else life_timer++;
    }
}

void NPCSkeleton::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        alive = true;
    }
    state_switch(npc_states::Possessed);
}

void NPCSkeleton::resolve_collision(DisplayObject *obj){
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
}