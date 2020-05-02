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
        ability = true;
    }
    state_switch(npc_states::Possessed);
}

void NPCDoctor::resolve_collision(DisplayObject *obj){
    MainNPC::resolve_collision(obj);
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
}

void NPCDoctor::resolve_adjacency(DisplayObject *obj, int status){
    PoisonGas * pg = dynamic_cast<PoisonGas*>(obj);
    vector<DisplayObject*> inv = *inventory;

    if (pg && ability){
        vector<DisplayObject*> herb_to_spend;
        int counter = 0;

        //cout<<"DETOX: "<<this->detox<<" "<<this->inventory->size()<<endl;

        //CHECK THAT YOU HAVE HERB
        for (int i = 0; i < inv.size(); i++){
            //cout<<"INV: "<<inv[i]->id<<endl;
            if (inv[i]->id == "Herb"){
                counter++;
                herb_to_spend.push_back(inv[i]);
            }
        }

        if (counter >= 3){
            int used = 0;

            //delete used herb from inv
            for (DisplayObject* item: herb_to_spend){
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), item);
                if (position != inventory->end()){
                    inventory->erase(position);
                }
                used++;
                if (used == 3) {this->detox = true; break;}
            }
        } 

        ability = false;
        //cout<<"DETOX: "<<this->detox<<endl;
        return;

    }

}