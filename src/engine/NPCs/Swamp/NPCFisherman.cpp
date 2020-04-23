#include <iostream>
#include <cstdlib>
#include "NPCFisherman.h"

using namespace std;

NPCFisherman::NPCFisherman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_back", 6, 10, true, "back");

	this->play("idle");
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

void NPCFisherman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
    }
    state_switch(npc_states::Possessed);
}