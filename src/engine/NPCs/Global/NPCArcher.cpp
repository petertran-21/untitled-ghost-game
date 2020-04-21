#include <iostream>
#include <cstdlib>
#include "NPCArcher.h"
#include "DisplayObjectContainer.h"

using namespace std;

NPCArcher::NPCArcher(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
	this->addAnimation("../resources/npcs/", "npc_base", 2, 1, true);
    this->addAnimation("./resources/npcs/archer/", "archer_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/archer/", "archer_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/archer/", "archer_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/archer/", "archer_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/archer/", "archer_back", 6, 10, true, "back");

	this->play("idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCARCHER_SUBTYPE;
}

void NPCArcher::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        if (abilityPt.x != 0 || abilityPt.y != 0){
            Arrow *arr = new Arrow(abilityPt, dir, this);
            Arrow *arrCollision = new Arrow(abilityPt, dir, this);
            this->addChild(arr);
            arr->col_arrow = arrCollision;

            //add to collision system container
            arrCollision->position.x = this->position.x + arr->position.x;
            arrCollision->position.y = this->position.y + arr->position.y;
            arrCollision->movespeed = arr->movespeed*2;
            this->collisionContainer->addChild(arrCollision);

        }
    }
    state_switch(npc_states::Possessed);
}

void NPCArcher::resolve_collision(DisplayObject *obj){
    MainNPC::resolve_collision(obj);
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
}