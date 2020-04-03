#include <iostream>
#include <cstdlib>
#include "NPCCollector.h"

using namespace std;

NPCCollector::NPCCollector(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->position.x = 100;
    this->position.y = 100;
	this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCCollector::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;

        // //pick up crab
        // if (crab == NULL){
        //     switch(dir){
        //         case N: 
        //             //if(collision detected @ dir and colliding with crab)
        //                 //crab = get_colliding_object()
        //                 //crab.collected = true;
        //             break;
        //         case S: 
        //             //if(collision detected @ dir and colliding with crab)
        //                 //crab = get_colliding_object()
        //                 //crab.collected = true;
        //             break;
        //         case E: 
        //             //if(collision detected @ dir and colliding with crab)
        //                 //crab = get_colliding_object()
        //                 //crab.collected = true;
        //             break;
        //         case W: 
        //             //if(collision detected @ dir and colliding with crab)
        //                 //crab = get_colliding_object()
        //                 //crab.collected = true;
        //             break;
        //     }
        // }
        // //place crab
        // else{
        //     switch(dir){
        //         case N: 
        //             //if(space @ direction is not a wall)
        //                 //crab.collected = false;
        //                 //crab = NULL;
        //             break;
        //         case S: 
        //             //if(space @ direction is not a wall)
        //                 //crab.collected = false;
        //                 //crab = NULL;
        //             break;
        //         case E: 
        //             //if(space @ direction is not a wall)
        //                 //crab.collected = false;
        //                 //crab = NULL;
        //             break;
        //         case W: 
        //             //if(space @ direction is not a wall)
        //                 //crab.collected = false;
        //                 //crab = NULL;
        //             break;
        //     }
        // }
        
    }
    state_switch(npc_states::Possessed);
}