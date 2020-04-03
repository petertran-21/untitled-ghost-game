#include <iostream>
#include <cstdlib>
#include "NPCOperator.h"

using namespace std;

NPCOperator::NPCOperator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCOperator::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        if (current_valve != NULL){
            current_valve->toggle();
        }
        switch(dir){
            case N: 
                    cout << "Operated North" << endl;
                break;
            case S: 
                    cout << "Operated South" << endl;
                break;
            case E: 
                    cout << "Operated East" << endl;
                break;
            case W: 
                    cout << "Operated West" << endl;
                break;
        }
    }
    state_switch(npc_states::Possessed);
}

void NPCOperator::resolve_collision(DisplayObject *obj){
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
    MainNPC::resolve_collision(obj);
    Valve *v = dynamic_cast<Valve*>(obj);
    if (v){
        v->dir = this->dir;
        current_valve = v;
    }
}
