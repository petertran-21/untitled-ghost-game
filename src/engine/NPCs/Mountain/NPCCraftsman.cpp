#include <iostream>
#include <cstdlib>
#include "NPCCraftsman.h"

using namespace std;

NPCCraftsman::NPCCraftsman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPC(){
    this->addAnimation("./resources/npcs/", "npc_base", 1, 1, true);
	this->play("npc_base");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
}

void NPCCraftsman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "STATE: ABILITY" << endl;
        ability = true;
    }
    state_switch(npc_states::Possessed);
}

void NPCCraftsman::resolve_adjacency(DisplayObject *obj, int status){
    Mineral * m = dynamic_cast<Mineral*>(obj);
    
    if (m && ability == true){

        if (status != 0 && !m->mined){
            //ADD MINERAL TO INVENTORY
            ability = false;
            m->mined = true;
            return;
        }
        ability = false;
    }

}