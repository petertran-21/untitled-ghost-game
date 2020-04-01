#include <iostream>
#include <cstdlib>
#include "NPCLumberjack.h"

using namespace std;

NPCLumberjack::NPCLumberjack() : MainNPC(){
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
}

void NPCLumberjack::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;

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