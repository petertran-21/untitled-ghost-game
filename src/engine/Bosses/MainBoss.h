#ifndef MAINBOSS_H
#define MAINBOSS_H

#include "AnimatedSprite.h"
#include "Controls.h"

using namespace std;

enum class boss_states {Idle, Attack, Death};

class MainBoss : public AnimatedSprite{
    
    public:

        MainBoss();

	    virtual void draw(AffineTransform &at);
        
        boss_states state = boss_states::Idle;
        bool state_new = true;
        bool state_updated = false;

        void state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_switch(boss_states new_state);
        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_death(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        virtual void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

};

#endif