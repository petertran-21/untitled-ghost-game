#ifndef NPCSKELETON_H
#define NPCSKELETON_H

#include "MainNPC.h"
#include "DisplayObjectContainer.h"

using namespace std;

class NPCSkeleton : public MainNPC{
    
    public:
        NPCSkeleton(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        void resolve_collision(DisplayObject *obj);
};


#endif