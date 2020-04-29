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
    Workbench * w = dynamic_cast<Workbench*>(obj);

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

    if (c && ability){

        if (status != 0 && !c->mined){
            //ADD ITEM TO INVENTORY
            DisplayObject* item = new DisplayObject(c->id,"./resources/items/cavelake_1.png");     
            inventory->push_back(item);

            ability = false;
            c->mined = true;
            return;
        }
        //ability = false;
    }

    if (w && ability){
        vector<DisplayObject*> inv = *inventory;
        vector<DisplayObject*> minerals_to_spend;
        vector<DisplayObject*> cavelakes_to_spend;

        int recipe_minerals_max = 2;
        int recipe_cavelakes_max = 1;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Mineral"){
                minerals_to_spend.push_back(inv[i]);
            }
            if (inv[i]->id == "CaveLake"){
                cavelakes_to_spend.push_back(inv[i]);
            }
        }

        //BUILD THE THING
        if (minerals_to_spend.size() >= recipe_minerals_max && cavelakes_to_spend.size() >= recipe_cavelakes_max){

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
            for (DisplayObject* item : cavelakes_to_spend){
                std::vector<DisplayObject*>::iterator position = std::find(inventory->begin(), inventory->end(), item);
                if (position != inventory->end()){
                    inventory->erase(position);
                    cout << "SPENT CAVELAKE" << endl;
                }
                counter++;
                //exit loop if spent enough
                if (counter == recipe_minerals_max) break;
            }

            ability = false;
            return;
        }

    }

}