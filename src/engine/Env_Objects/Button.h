#ifndef BUTTON_H
#define BUTTON_H
#define BUTTON_SUBTYPE 104

#include "Controller.h"
#include "MainEnvObj.h"
#include "Door.h"


using namespace std;

class Button : public MainEnvObj{
    
    public:
        Button(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void add_door(Door* d);
        bool pressed = false;
        vector<Door*> doors;

        void resolve_collision(DisplayObject *obj);

};

#endif