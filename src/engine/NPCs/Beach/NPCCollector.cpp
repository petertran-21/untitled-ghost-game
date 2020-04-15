#include <iostream>
#include <cstdlib>
#include "NPCCollector.h"

using namespace std;

NPCCollector::NPCCollector(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCCollector::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPC::update(pressedKeys, currState);

    if (crab != NULL){
        if (crab->collected) crab->position = position;
    }
    if (state != npc_states::Ability){
        can_collect = true;
    }
}

void NPCCollector::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;

    //place crab
    if (crab != NULL){
        switch(dir){
            case N: 
                crab->collected = false;
                crab->position.y -= 100;
                crab = NULL;
                break;
            case S: 
                crab->collected = false;
                crab->position.y += 100;
                crab = NULL;
                break;
            case E: 
                crab->collected = false;
                crab->position.x += 100;
                crab = NULL;
                break;
            case W: 
                crab->collected = false;
                crab->position.x -= 100;
                crab = NULL;
                break;
        }
    }
    else state_switch(npc_states::Possessed);
    }
    state_switch(npc_states::Possessed);
}

void NPCCollector::resolve_collision(DisplayObject* obj){
    if (cooldown_timer > 0) return;
    
    if (obj->subtype==16){ // 16 == Crab
        //TODO: need to check for npc diagonal to crab. Cannot pick up in this situation
        //NOTE: crab is moved to position of NPC
        if (can_collect){
            crab = (Crab*) obj;
            crab->collected = true;
            can_collect = false;
        }
    }
    else{
        MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
    }
}