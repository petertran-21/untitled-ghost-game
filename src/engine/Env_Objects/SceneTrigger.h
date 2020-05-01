#ifndef SCENE_TRIGGER_H
#define SCENE_TRIGGER_H

#include "Controller.h"
#include "AnimatedSprite.h"
#include "DisplayObjectContainer.h"
#include <string>


using namespace std;

class SceneTrigger : public AnimatedSprite{
    
    public:
        SceneTrigger(DisplayObjectContainer *container, string scene_path);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        string scene_path = "";
        bool active = true;
        DisplayObjectContainer *collisionContainer;
        SDL_Point ghost_pos;

        void resolve_collision(DisplayObject *obj);

};

#endif