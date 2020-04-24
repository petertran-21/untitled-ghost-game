#ifndef DRAGON_H
#define DRAGON_H
#define DRAGON_SUBTYPE 5

#include "MainBoss.h"
#include "FireStream.h"

using namespace std;

class Dragon : public MainBoss{
    
    public:
        Dragon(DisplayObjectContainer *container, DisplayObjectContainer* drawContainer);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool active = false;
        bool init = true;
        directions dir = S;
        int tile_range = 8;

        int fire_timer = 0;
        int fire_timer_max = 150;

        vector<FireStream*> streams;
        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;
   
};


#endif