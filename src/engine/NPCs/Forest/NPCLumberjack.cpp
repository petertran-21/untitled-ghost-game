#include <iostream>
#include <cstdlib>
#include "NPCLumberjack.h"

using namespace std;

NPCLumberjack::NPCLumberjack(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
	this->addAnimation("../resources/npcs/", "npc_base", 1, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCLUMBERJACK_SUBTYPE;
}

void NPCLumberjack::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;

        chopping = true;

        switch(dir){
            case N: 
                //if(collision detected @ dir and colliding with tree)
                    //tree.cut();
                    cout << "Chopped North" << endl;
                break;
            case S: 
                //if(collision detected @ dir and colliding with tree)
                    //tree.cut();
                    cout << "Chopped South" << endl;
                break;
            case E: 
                //if(collision detected @ dir and colliding with tree)
                    //tree.cut();
                    cout << "Chopped East" << endl;
                break;
            case W: 
                //if(collision detected @ dir and colliding with tree)
                    //tree.cut();
                    cout << "Chopping West" << endl;
                break;
        }
    }
    state_switch(npc_states::Possessed);
}

void NPCLumberjack::resolve_adjacency(DisplayObject *obj, int status){
    //if (status != 0) cout << "HELLO" << endl;
    
    if (obj->getSubtype()==102 && chopping == true){

        if (status != 0){
            chopping = false;
            Log* l = (Log*) obj;
            l->chopped = true;
            return;
        }
        
    }

    if (obj->getSubtype()==101 && chopping == true){

        if (status != 0){
            chopping = false;
            Bridge* b = (Bridge*) obj;
            b->open = true;
            return;
        }
        
    }
}