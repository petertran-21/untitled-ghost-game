#include <iostream>
#include <cstdlib>
#include "MainCollectibles.h"

using namespace std;

MainCollectibles::MainCollectibles() : AnimatedSprite("Collectible"){
    this->type = "Collectible";
}

MainCollectibles::MainCollectibles(DisplayObjectContainer* container) : AnimatedSprite("EnvObj"){
    this->type = "Collectible";
    this->collisionContainer = container;
}

void MainCollectibles::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

    MainCollectibles::state_execute(pressedKeys, currState);
}

void MainCollectibles::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

//GENERAL PURPOSE STATES
void MainCollectibles::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: IDLE" << endl;
}

//STATE MACHINE METHODS
void MainCollectibles::state_switch(collectible_states new_state){
    if (state != new_state){
        state_new = true;
        state = new_state;
        state_updated = true;
    }
}
void MainCollectibles::state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    switch(state){
        case collectible_states::Idle:      MainCollectibles::state_idle(pressedKeys, currState);      break;
    }
    if (state_updated) state_updated = false;
    else state_new = false;
}
