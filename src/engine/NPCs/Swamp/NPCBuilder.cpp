#include <iostream>
#include <cstdlib>
#include "NPCBuilder.h"

using namespace std;

NPCBuilder::NPCBuilder(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_idle", 1, 1, true);
	this->play("craftsman_idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;

    this->inventory = &passedInventory;
}

void NPCBuilder::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        ability = true;
    }
    state_switch(npc_states::Possessed);
}

void NPCBuilder::resolve_adjacency(DisplayObject *obj, int status){
    Workbench * w = dynamic_cast<Workbench*>(obj);
    SwampBridge * s = dynamic_cast<SwampBridge*>(obj);

    vector<DisplayObject*> inv = *inventory;

    //BUILD BRIDGE
    if (s && ability){
        vector<DisplayObject*> wood_to_spend;

        int recipe_wood_max = 5;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Driftwood"){
                wood_to_spend.push_back(inv[i]);
            }
        }

        //BUILD BRIDGE
        if (wood_to_spend.size() >= recipe_wood_max){

            cout << "BRIDGE CRAFTED" << endl;
            
            counter = 0;

            //DELETE SPENT RESOURCES
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

    //USE WORKBENCH
    if (w && ability){
        
        vector<DisplayObject*> collectibles_to_spend;

        int recipe_collectible_max = 3;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Collectible 1" || inv[i]->id == "Collectible 2" || inv[i]->id == "Collectible 3"){
                collectibles_to_spend.push_back(inv[i]);
            }
        }

        //BUILD HAMMER
        if (collectibles_to_spend.size() >= recipe_collectible_max){

            DisplayObject* hammer = new DisplayObject("Hammer","./resources/items/hammer_1.png");     
            inventory->push_back(hammer);
            cout << "HAMMER CRAFTED" << endl;
            
            counter = 0;

            //DELETE SPENT RESOURCES
            for (DisplayObject* item : collectibles_to_spend){
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), item);
                if (position != inventory->end()){
                    inventory->erase(position);
                    cout << "SPENT COLLECTIBLE" << endl;
                }
                counter++;
                //exit loop if spent enough
                if (counter == recipe_collectible_max) break;
            }

            ability = false;
            return;
        }

    }

}