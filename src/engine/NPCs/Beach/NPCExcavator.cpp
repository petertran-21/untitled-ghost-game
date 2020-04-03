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
                //if(collision detected @ dir and colliding with breakable wall)
                    //breakable_wall.destroy = true;
                    cout << "Excavated North" << endl;
                break;
            case S: 
                //if(collision detected @ dir and colliding with breakable wall)
                    //breakable_wall.destroy = true;
                    cout << "Excavated South" << endl;
                break;
            case E: 
                //if(collision detected @ dir and colliding with breakable wall)
                    //breakable_wall.destroy = true;
                    cout << "Excavated East" << endl;
                break;
            case W: 
                //if(collision detected @ dir and colliding with breakable wall)
                    //breakable_wall.destroy = true;
                    cout << "Excavated West" << endl;
                break;
        }
    }
    state_switch(npc_states::Possessed);
}
