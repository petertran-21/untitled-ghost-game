#include <iostream>
#include <cstdlib>
#include "NPCPyromancer.h"

using namespace std;

NPCPyromancer::NPCPyromancer(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
	this->addAnimation("./resources/npcs/pyro/", "pyro_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/pyro/", "pyro_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/pyro/", "pyro_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/pyro/", "pyro_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/pyro/", "pyro_back", 6, 10, true, "back");

    this->inventory = &passedInventory;
	this->play("idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCPYROMANCER_SUBTYPE;
}

void NPCPyromancer::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        if (abilityPt.x != 0 || abilityPt.y != 0){
            Fire *f = new Fire(abilityPt, this); 
            this->addChild(f);
            Fire *fCollision = new Fire(abilityPt, this);

            fCollision->position.x = this->position.x + f->position.x;
            fCollision->position.y = this->position.y + f->position.y;
            this->collisionContainer->addChild(fCollision);

        }
    }
    state_switch(npc_states::Possessed);
}

void NPCPyromancer::resolve_collision(DisplayObject *obj){
    MainNPC::resolve_collision(obj);
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
}