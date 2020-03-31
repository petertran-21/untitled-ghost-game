#include <iostream>
#include <cstdlib>
#include "MainEnvObj.h"

using namespace std;

MainEnvObj::MainEnvObj() : AnimatedSprite("EnvObj"){
    this->type = "EnvObj";
}

void MainEnvObj::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

    MainEnvObj::state_execute(pressedKeys, currState);

    if (flammable){
        //catching fire
        if (fire_timer == fire_threshold) on_fire = true;

        //burning
        if (on_fire){
            spread_fire();
            burn_timer++;
            
            //burned
            if (burn_timer == burn_time_max){
                on_fire = false;
                process_fire();
            }
        }
    }
}

void MainEnvObj::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

//GENERAL PURPOSE STATES
void MainEnvObj::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: IDLE" << endl;
}

//STATE MACHINE METHODS
void MainEnvObj::state_switch(obj_states new_state){
    if (state != new_state){
        state_new = true;
        state = new_state;
        state_updated = true;
    }
}
void MainEnvObj::state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    switch(state){
        case obj_states::Idle:      MainEnvObj::state_idle(pressedKeys, currState);      break;
    }
    if (state_updated) state_updated = false;
    else state_new = false;
}

void MainEnvObj::spread_fire(){
    //check surrounding flammable objects 
}

void MainEnvObj::process_fire(){
    //check surrounding flammable objects 
}