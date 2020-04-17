#ifndef LOG_H
#define LOG_H
#define LOG_SUBTYPE 102

#include "Controller.h"
#include "MainNPCObj.h"


using namespace std;

class Log : public MainNPCObj{
    
    public:
        Log();
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        bool sunk = false;
        bool chopped = false;
        int subtype = 102;

        void resolve_collision(DisplayObject *obj);
        void resolve_adjacency(DisplayObject *obj, int status);

};

#endif