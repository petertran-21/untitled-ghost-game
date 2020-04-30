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

        cout<<"TREE IS NOW HIT"<<endl; 
        cout<<this->drawingContainer->children.size()<<endl;
        Wood* wood = new Wood(this->collisionContainer, this->drawingContainer);
        wood->position.x = obj->position.x;
        wood->position.y = obj->position.y+100;
        this->drawingContainer->addChild(wood);
        cout<<this->drawingContainer->children.size()<<endl;
        vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), wood);
        vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), wood);
        if (collideItr != this->collisionContainer->children.end() && drawItr != this->drawingContainer->children.end()){
            this->collisionContainer->children.erase(collideItr);
            this->drawingContainer->children.erase(drawItr);
        }   
        hitTree = false;
    }
}