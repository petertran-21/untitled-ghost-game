#ifndef NPCArcher_H
#define NPCArcher_H

#include "MainNPC.h"
#include "Arrow.h"

using namespace std;

class NPCCraftsman : public MainNPC{
    
    public:
        NPCCraftsman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        int subtype = 25;
};


#endif