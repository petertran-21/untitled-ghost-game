#include <iostream>
#include <cstdlib>
#include "NPCOperator.h"

using namespace std;

NPCOperator::NPCOperator(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
	this->addAnimation("./resources/npcs/operator/", "operator_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/operator/", "operator_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/operator/", "operator_left", 6, 10, true, "left");
    this->addAnimation("./resources/npcs/operator/", "operator_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/operator/", "operator_back", 6, 10, true, "back");

    this->inventory = &passedInventory;
	this->play("idle");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCOPERATOR_SUBTYPE;
}

void NPCOperator::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        
        operated = true;

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
    if (obj->getSubtype()==12 && operated == true){
        cout<<"OPERATOR RESOLVE HIT IF STATEMENT"<<endl;
        operated = false;
        Valve* v = (Valve*) obj;
        v->toggle();
        return;
	}

}

void NPCOperator::resolve_adjacency(DisplayObject *obj, int status){

    if (obj->getSubtype()==12 && operated == true){
        cout<<"OPERATOR RESOLVE HIT: "<<status<<endl;
        if (status != 0){
            cout<<"OPERATOR RESOLVE HIT IF STATEMENT"<<endl;
            operated = false;
            Valve* v = (Valve*) obj;
            v->toggle();
            return;
        }
        else operated = false;
	}
}
