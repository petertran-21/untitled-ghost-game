#ifndef WATERJET_H
#define WATERJET_H
#define WATERJET_SUBTYPE 13

#include "Controller.h"
#include "MainEnvObj.h"
#include <vector>
#include "WaterStream.h"


using namespace std;

class WaterJet : public MainEnvObj{
    
    public:
        WaterJet(DisplayObjectContainer *container, DisplayObjectContainer* drawContainer);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool active = false;
        bool init = true;
        directions dir = S;
        int tile_range = 12;

        vector<WaterStream*> streams;
        // vector<DisplayObject*> streams;
        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;

        void resolve_collision(DisplayObject *obj);

};

#endif