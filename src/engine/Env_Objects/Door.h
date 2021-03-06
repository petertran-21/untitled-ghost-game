#ifndef DOOR_H
#define DOOR_H
#define DOOR_SUBTYPE 105

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Door : public MainEnvObj{
    
    public:
        Door(DisplayObjectContainer* container, DisplayObjectContainer* drawContainer);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        bool open = false;

        void resolve_collision(DisplayObject *obj);
        DisplayObjectContainer* drawingContainer;
        DisplayObjectContainer* collisionContainer;

};

#endif