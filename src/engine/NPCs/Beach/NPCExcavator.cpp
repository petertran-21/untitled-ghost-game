#include <iostream>
#include <cstdlib>
#include "NPCExcavator.h"

using namespace std;

NPCExcavator::NPCExcavator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    container->addChild(this);
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
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
    if (obj->subtype==10 && excavate == true){ // 10 == BreakableWall
        BreakableWall* b = (BreakableWall*) obj;
        b->broken = true;
        //TODO: if there's more than one breakable there might be a problem-->need to test
        vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), obj);
        vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), obj);
        if (collideItr != this->collisionContainer->children.end() && drawItr != this->drawingContainer->children.end()){
            this->collisionContainer->children.erase(collideItr);
            this->drawingContainer->children.erase(drawItr);
        }   
        excavate = false;
	}
}
