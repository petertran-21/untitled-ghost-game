#include <iostream>
#include <cstdlib>

#include "Sign.h"

using namespace std;


Sign::Sign(DisplayObjectContainer* container) : MainEnvObj(){
    this->id = "Sign";
    this->addAnimation("./resources/items/", "signpost_hole", 1, 1, false);
    this->addAnimation("./resources/items/", "sign", 1, 1, false);
	this->play("signpost_hole");

    this->collisionContainer = container;
    container->addChild(this);
}

void Sign::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (posted){
        this->play("sign");

        //SPAWN THE EXIT
        if (exit == NULL){
            exit = new SceneTrigger(this->collisionContainer, "./resources/scenes/campsite.json");
            this->collisionContainer->addChild(exit);
            exit->position.x = 200;
            exit->position.y = 100;
        }
    }
}
