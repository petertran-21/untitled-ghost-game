#include <iostream>
#include <cstdlib>
#include "NPCArcher.h"
#include "DisplayObjectContainer.h"

using namespace std;

NPCArcher::NPCArcher(DisplayObjectContainer* container) : MainNPC(){
    //this->id = "archer";
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
}

void NPCArcher::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        if (abilityPt.x != 0 || abilityPt.y != 0){
            Arrow *arr = new Arrow(abilityPt, dir);
            Arrow *arrCollision = new Arrow(abilityPt, dir);
            this->addChild(arr);

            //add to collision system container
            arrCollision->position.x = this->position.x + arr->position.x;
            arrCollision->position.y = this->position.y + arr->position.y;
            arrCollision->movespeed = arr->movespeed*2;
            this->collisionContainer->addChild(arrCollision);

        }
    }
    state_switch(npc_states::Possessed);
}