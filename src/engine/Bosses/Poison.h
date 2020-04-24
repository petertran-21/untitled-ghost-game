#ifndef POISON_H
#define POISON_H
#define POISON_SUBTYPE 109

#include "MainNPCObj.h"
#include "MainNPC.h"
#include "Ghost.h"

using namespace std;

class Poison : public MainNPCObj{
    
    public:
        Poison(SDL_Point pos, int angle, DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;

        int movespeed = 5;

        void resolve_collision(DisplayObject* obj);
   
};


#endif