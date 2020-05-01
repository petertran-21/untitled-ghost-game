#include <iostream>
#include <cstdlib>
#include "NPCCroc.h"
#include "Wood.h"

using namespace std;

NPCCroc::NPCCroc(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/animals/", "crocodile", 2, 1, false);
	this->play("crocodile");

    this->inventory = &passedInventory;
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCCROC_SUBTYPE;
}

void NPCCroc::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
        if (state_new){
        cout << "STATE: ABILITY" << endl;

        switch(dir){
            case N: 
                    hitTree = true;
                break;
            case S: 
                    hitTree = true;
                break;
            case E: 
                    hitTree = true;
                break;
            case W: 
                    hitTree = true;
                break;
        }
    }
    state_switch(npc_states::Possessed);
}

void NPCCroc::resolve_collision(DisplayObject * obj){ 
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
    if (obj->getSubtype()==SWAMPTREE_SUBTYPE && hitTree == true){

        //add wood
        // Wood* wood = new Wood(this->collisionContainer, this->drawingContainer, obj->position.x, obj->position.y);
        // wood->position.x = obj->position.x;
        // wood->position.y = obj->position.y+100;
        // this->drawingContainer->addChild(wood);

        SwampTree* tree = (SwampTree*) obj;

        if (!tree->mined){
            //add wood to inventory
            TextAlert* t = new TextAlert(this->position.x, this->position.y, "Driftwood Collected", this->drawingContainer);
            DisplayObject* wood = new DisplayObject("Driftwood","./resources/items/wood_1.png");     
            inventory->push_back(wood);
            tree->mined = true;
        }

        //delete swamp tree
        vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), tree);
        vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), obj);
        if (collideItr != this->collisionContainer->children.end() && drawItr != this->drawingContainer->children.end()){
        // if (collideItr != this->collisionContainer->children.end()){
            this->collisionContainer->children.erase(collideItr);
            this->drawingContainer->children.erase(drawItr);
        }   
        hitTree = false;
    }
}