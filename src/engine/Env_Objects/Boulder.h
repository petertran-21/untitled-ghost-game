#ifndef BOULDER_H
#define BOULDER_H
#define BOULDER_SUBTYPE 300

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Boulder : public MainEnvObj{
    
    public:
        Boulder(DisplayObjectContainer* container);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool pushed = false;

        void resolve_adjacency(DisplayObject* obj, int status);

};

#endif