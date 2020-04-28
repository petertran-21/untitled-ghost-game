#include <iostream>
#include <cstdlib>
#include "NPCStrongman.h"

using namespace std;

NPCStrongman::NPCStrongman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->addAnimation("./resources/npcs/", "npc_base", 2, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
}


void NPCStrongman::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPC::update(pressedKeys, currState);

    if (strongmode_timer > 0) strongmode_timer--;
    else strongmode = false;
}

void NPCStrongman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        cout << "STRONG MODE ACTIVATED" << endl;
        
        if (!strongmode){
            strongmode = true;
            strongmode_timer = strongmode_timer_max;
        }
    }
    state_switch(npc_states::Possessed);
}
