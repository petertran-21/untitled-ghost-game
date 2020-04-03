#ifndef NPCCOLLECTOR_H
#define NPCCOLLECTOR_H

#include "MainNPC.h"
//#include "HermitCrab.h"

using namespace std;

class NPCCollector : public MainNPC{
    
    public:
        NPCCollector(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        //HermitCrab crab;
   
};


#endif