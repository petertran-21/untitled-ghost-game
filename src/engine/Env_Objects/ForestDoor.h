#ifndef FORESTDOOR_H
#define FORESTDOOR_H
#define FORESTDOOR_SUBTYPE 400

#include "Controller.h"
#include "MainEnvObj.h"
#include "SceneTrigger.h"

using namespace std;

class ForestDoor : public MainEnvObj{
    
    public:
        ForestDoor(DisplayObjectContainer* container, vector<DisplayObject*> &passedInventory);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        vector<DisplayObject*> *inventory;
        bool open = false;
        SceneTrigger * exit = NULL;
};

#endif