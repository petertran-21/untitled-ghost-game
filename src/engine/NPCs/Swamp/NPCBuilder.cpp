#include <iostream>
#include <cstdlib>
#include "NPCBuilder.h"

using namespace std;

NPCBuilder::NPCBuilder(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/craftsman/", "craftsman_back", 6, 10, true, "back");
	
    this->play("idle");
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

        int recipe_wood_max = 1; 
        bool has_hammer = false; 
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Driftwood"){
                wood_to_spend.push_back(inv[i]);
            }
            if (inv[i]->id == "Hammer"){
                has_hammer = true;
            }
        }

        //BUILD BRIDGE
        if (wood_to_spend.size() >= recipe_wood_max && has_hammer){
            if (s->cancross == true){
                return;
            }
            s->play("built");
            s->cancross = true;
            
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