#include <iostream>
#include <cstdlib>
#include "NPCCraftsman.h"

using namespace std;

NPCCraftsman::NPCCraftsman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_idle", 1, 1, true);
	this->play("craftsman_idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;

    this->inventory = &passedInventory;
}

void NPCCraftsman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        ability = true;
    }
    state_switch(npc_states::Possessed);
}

void NPCCraftsman::resolve_adjacency(DisplayObject *obj, int status){
    Mineral * m = dynamic_cast<Mineral*>(obj);
    CaveLake * c = dynamic_cast<CaveLake*>(obj);
    MountainTree * t = dynamic_cast<MountainTree*>(obj);
    Workbench * w = dynamic_cast<Workbench*>(obj);

    vector<DisplayObject*> inv = *inventory;

    //MINE MINERAL
    if (m && ability){

        if (status != 0 && !m->mined){
            //ADD ITEM TO INVENTORY
            DisplayObject* item = new DisplayObject(m->id,"./resources/items/mineral_1.png");     
            inventory->push_back(item);

            ability = false;
            m->mined = true;
            return;
        }
        //ability = false;
    }

    //MINE LAKE W/BUCKET
    if (c && ability){
        
        if (status != 0 && !c->mined){

            //make sure you have bucket
            for (int i = 0; i < inv.size(); i++){
                if (inv[i]->id == "Bucket"){
                    std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), inv[i]);
                    if (position != inventory->end()){
                        inventory->erase(position);
                        cout << "FILLED BUCKET" << endl;
                    }
                    //ADD ITEM TO INVENTORY
                    DisplayObject* item = new DisplayObject("Water Bucket","./resources/items/bucket_full_1.png");     
                    inventory->push_back(item);
                    c->mined = true;
                    break;
                }
            }

            ability = false;
            return;
        }
    }

    //MINE TREE
    if (t && ability){

        if (status != 0 && !t->mined){
            //ADD ITEM TO INVENTORY
            DisplayObject* item = new DisplayObject("Wood","./resources/items/wood_1.png");     
            inventory->push_back(item);

            ability = false;
            t->mined = true;
            return;
        }
    }

    //USE WORKSTATION
    if (w && ability){
        vector<DisplayObject*> minerals_to_spend;
        vector<DisplayObject*> buckets_to_spend;
        vector<DisplayObject*> wood_to_spend;

        int recipe_minerals_max = 2;
        int recipe_buckets_max = 1;
        int recipe_wood_max = 3;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Mineral"){
                minerals_to_spend.push_back(inv[i]);
            }
            if (inv[i]->id == "Water Bucket"){
                buckets_to_spend.push_back(inv[i]);
            }
            if (inv[i]->id == "Wood"){
                wood_to_spend.push_back(inv[i]);
            }
        }

        //BUILD THE THING
        if (minerals_to_spend.size() >= recipe_minerals_max && buckets_to_spend.size() >= recipe_buckets_max && wood_to_spend.size() >= recipe_wood_max){

            DisplayObject* sign = new DisplayObject("Sign","./resources/items/sign_1.png");     
            inventory->push_back(sign);
            cout << "SIGN CRAFTED" << endl;

            counter = 0;

            //DELETE SPENT RESOURCES
            for (DisplayObject* item : minerals_to_spend){
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), item);
                if (position != inventory->end()){
                    inventory->erase(position);
                    cout << "SPENT MINERAL" << endl;
                }
                counter++;
                //exit loop if spent enough
                if (counter == recipe_minerals_max) break;
            }
            
            counter = 0;
            for (DisplayObject* item : buckets_to_spend){
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), item);
                if (position != inventory->end()){
                    inventory->erase(position);
                    cout << "SPENT CAVELAKE" << endl;
                }
                counter++;
                //exit loop if spent enough
                if (counter == recipe_buckets_max) break;
            }

            counter = 0;
            for (DisplayObject* item : wood_to_spend){
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), item);
                if (position != inventory->end()){
                    inventory->erase(position);
                    cout << "SPENT WOOD" << endl;
                }
                counter++;
                //exit loop if spent enough
                if (counter == recipe_wood_max) break;
            }

            ability = false;
            return;
        }

    }

}