#include <iostream>
#include <cstdlib>
#include "NPCStrongman.h"
#include "FallenTree.h"

using namespace std;

NPCStrongman::NPCStrongman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/npcs/strongman/", "strongman_idle", 1, 1, true);
	this->play("strongman_idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;

    this->inventory = &passedInventory;
}


void NPCStrongman::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPC::update(pressedKeys, currState);

    if (strongmode_timer > 0) strongmode_timer--;
    else strongmode = false;
}

void NPCStrongman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        cout << "STRONG MODE ACTIVATED" << endl;
        
        if (!strongmode){
            strongmode = true;
            strongmode_timer = strongmode_timer_max;
        }
    }
    state_switch(npc_states::Possessed);
}

void NPCStrongman::resolve_adjacency(DisplayObject *obj, int status){

    FallenTree* ft = dynamic_cast<FallenTree*>(obj);

    if (ft && strongmode){
        ft->destroyed = true;
        return;
    }

    Sign * s = dynamic_cast<Sign*>(obj);

    //POST SIGN
    if (s && strongmode){

        if (status != 0 && !s->posted){

            vector<DisplayObject*> inv = *inventory;
            DisplayObject* temp = NULL;

            //LOOK FOR SIGN IN INVENTORY
            for (int i = 0; i < inv.size(); i++){
                if (inv[i]->id == "Sign") temp = inv[i];
            }

            //IF YOU HAVE A SIGN, POST IT AND REMOVE FROM INV
            if (temp){
                s->posted = true;
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), temp);
                if (position != inventory->end()){
                    inventory->erase(position);
                }
            }
            return;
        }
    }
}