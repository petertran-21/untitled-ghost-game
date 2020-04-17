#include <iostream>
#include <cstdlib>
#include "MainBoss.h"

using namespace std;

MainBoss::MainBoss() : AnimatedSprite("Boss"){
    this->type = "boss";
}

void MainBoss::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void MainBoss::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

    MainBoss::state_execute(pressedKeys, currState);
}

void MainBoss::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: IDLE" << endl;
}

void MainBoss::state_switch(boss_states new_state){
    if (state != new_state){
        state_new = true;
        state = new_state;
        state_updated = true;
    }
}
void MainBoss::state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    switch(state){
        case boss_states::Idle:      MainBoss::state_idle(pressedKeys, currState);      break;
        case boss_states::Attack: MainBoss::state_attack(pressedKeys, currState); break;
        case boss_states::Death:    MainBoss::state_death(pressedKeys, currState);    break;
    }
    if (state_updated) state_updated = false;
    else state_new = false;
}

void MainBoss::state_death(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    cout<<"Boss is dead"<<endl;
}

void MainBoss::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
}