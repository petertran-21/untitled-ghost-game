#include <iostream>
#include <cstdlib>
#include "NPCExcavator.h"

using namespace std;

NPCExcavator::NPCExcavator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCExcavator::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;

        switch(dir){
            case N: 
                    cout << "Excavated North" << endl;
                    excavate = true;
                break;
            case S: 
                    cout << "Excavated South" << endl;
                    excavate = true;
                break;
            case E: 
                    cout << "Excavated East" << endl;
                    excavate = true;
                break;
            case W: 
                    cout << "Excavated West" << endl;
                    excavate = true;
                break;
        }
    }
    state_switch(npc_states::Possessed);
}

void NPCExcavator::resolve_collision(DisplayObject * obj){
    MainNPC::resolve_collision(obj);
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
    
}

void NPCExcavator::resolve_adjacency(DisplayObject * obj, int status){

    if (obj->subtype=="breakable wall" && excavate == true){

        if (status != 0){
            excavate = false;
            BreakableWall* b = (BreakableWall*) obj;
            b->broken = true;

            
            //TODO: if there's more than one breakable there might be a problem-->need to test
            vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), obj);
            vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), obj);
            if (collideItr != this->collisionContainer->children.end() && drawItr != this->drawingContainer->children.end()){
                this->collisionContainer->children.erase(collideItr);
                this->drawingContainer->children.erase(drawItr);
            }   
        
            return;
        }
        else excavate = false;
        
	}
}
