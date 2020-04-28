#include <iostream>
#include <cstdlib>
#include "NPCLumberjack.h"

using namespace std;

NPCLumberjack::NPCLumberjack(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
	this->addAnimation("./resources/npcs/lumberjack/", "lumberjack_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/lumberjack/", "lumberjack_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/lumberjack/", "lumberjack_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/lumberjack/", "lumberjack_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/lumberjack/", "lumberjack_back", 6, 10, true, "back");

    this->inventory = &passedInventory;
	this->play("idle");
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
    Log * l = dynamic_cast<Log*>(obj);
    Bridge *b = dynamic_cast<Bridge*>(obj);
    
    if (l && chopping == true){

        if (status != 0){
            chopping = false;
            l->chopped = true;
            return;
        }
        
    }

    if (b && chopping == true){

        if (status != 0){
            chopping = false;
            b->open = true;
            return;
        }
        
    }
}