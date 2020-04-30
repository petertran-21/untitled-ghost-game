#include <iostream>
#include <cstdlib>
#include "NPCDoctor.h"

using namespace std;

NPCDoctor::NPCDoctor(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/npcs/doctor/", "doctor_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/doctor/", "doctor_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/doctor/", "doctor_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/doctor/", "doctor_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/doctor/", "doctor_back", 6, 10, true, "back");

    this->inventory = &passedInventory;
	this->play("idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCDOCTOR_SUBTYPE;
}

void NPCDoctor::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
    }
    state_switch(npc_states::Possessed);
}

void NPCDoctor::resolve_collision(DisplayObject * obj){ 
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);

}