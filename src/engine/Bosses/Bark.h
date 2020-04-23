#ifndef BARK_H
#define BARK_H
#define BARK_SUBTYPE 109

#include "MainNPCObj.h"
#include "MainNPC.h"

using namespace std;

class Bark : public MainNPCObj{
    
    public:
        Bark(SDL_Point pos, int angle, DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;

        int movespeed = 16;

        void resolve_collision(DisplayObject* obj);
   
};


#endif