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
    SwampTree * t = dynamic_cast<SwampTree*>(obj);
    Workbench * w = dynamic_cast<Workbench*>(obj);

    if (t && ability){

        if (status != 0 && !t->mined){
            //ADD ITEM TO INVENTORY
            DisplayObject* item = new DisplayObject(t->id,"./resources/items/swamptree_1.png");     
            inventory->push_back(item);

            ability = false;
            t->mined = true;
            return;
        }
    }

    if (w && ability){
        vector<DisplayObject*> inv = *inventory;
        vector<DisplayObject*> wood_to_spend;

        int recipe_wood_max = 3;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Wood"){
                wood_to_spend.push_back(inv[i]);
            }
        }

        //BUILD THE THING
        if (wood_to_spend.size() >= recipe_wood_max){

            // DisplayObject* sign = new DisplayObject("Sign","./resources/items/sign_1.png");     
            // inventory->push_back(sign);
            cout << "THING CRAFTED" << endl;

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

}