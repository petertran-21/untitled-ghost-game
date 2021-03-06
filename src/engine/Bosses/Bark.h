#ifndef BARK_H
#define BARK_H
#define BARK_SUBTYPE 109

#include "MainNPCObj.h"
#include "MainNPC.h"

using namespace std;

class Bark : public MainNPCObj{
    
    public:
        Bark(int width, int height, int angle, DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        
        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;

        int movespeed = 6;

        void resolve_collision(DisplayObject* obj);
   
};


#endif