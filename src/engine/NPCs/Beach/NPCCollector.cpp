#include <iostream>
#include <cstdlib>
#include "NPCCollector.h"

using namespace std;

NPCCollector::NPCCollector(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->addAnimation("./resources/npcs/collector/", "collector_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/collector/", "collector_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/collector/", "collector_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/collector/", "collector_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/collector/", "collector_back", 6, 10, true, "back");

	this->play("idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCCOLLECTOR_SUBTYPE;
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
        MainNPC::resolve_collision(obj);
    }
}