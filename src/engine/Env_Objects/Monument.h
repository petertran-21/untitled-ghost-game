#ifndef MONUMENT_H
#define MONUMENT_H
#define MONUMENT_SUBTYPE 500

#include "Controller.h"
#include "MainEnvObj.h"
#include "UIDefs.h"


using namespace std;

class Monument : public MainEnvObj{
    
    public:
        Monument(DisplayObjectContainer* container, vector<DisplayObject*> &passedInventory);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool complete = false;
        vector<DisplayObject*> *inventory;
        TextBox *t = NULL;

        void resolve_collision(DisplayObject *obj);

};

#endif