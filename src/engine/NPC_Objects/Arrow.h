#ifndef ARROW_H
#define ARROW_H

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class Arrow : public MainNPCObj{
    
    public:
        Arrow(SDL_Point pos, directions direction, DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        
        int movespeed = 4;
        directions dir = S;
        int subtype = 15;

        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;

        int timer = 0;

        void fly();
        virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void resolve_collision(DisplayObject *obj);

};
#endif