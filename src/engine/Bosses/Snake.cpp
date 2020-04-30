#include <iostream>
#include <cstdlib>
#include "Snake.h"

using namespace std;

Snake::Snake(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainBoss(){
    this->subtype = SNAKE_SUBTYPE;
    this->id = "snakeBoss";

    this->collisionContainer = container;
    this->drawingContainer = allSprites;
    this->scaleX = 0.5;
    this->scaleY = 0.5;

    this->addAnimation("./resources/bosses/", "snake_idle", 1, 1, false);

    this->play("snake_idle");
}

void Snake::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
		//anything that should happen once, right at the start of the state
        cout << "SNAKE STATE: IDLE" << endl;
        // this->play("snake_attack");
    }
    if (poison_timer==0){
        state_switch(boss_states::Attack);
    }
}
void Snake::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        cout << "SNAKE STATE: ATTACK" << endl;
        for (int i=0; i < 8; i++){
            Poison *b = new Poison(position, (M_PI/4 + poison_angle)*i, collisionContainer, drawingContainer);
        }
        poison_angle += M_PI/16;
    }
	//anything that should always run while in this state
    poison_timer++;

    if (poison_timer == poison_timer_max+20){
        //delete Poison
        // for (DisplayObject* poison: this->collisionContainer->children){
        //     if (poison->getSubtype() == POISON_SUBTYPE){
        //         this->collisionContainer->removeImmediateChild(poison);
        //     }
        // }
        // for (DisplayObject* poison: this->drawingContainer->children){
        //     if (poison->getSubtype() == POISON_SUBTYPE){
        //         this->drawingContainer->removeImmediateChild(poison);
        //     }
        // }
        poison_timer=0;
        state_switch(boss_states::Idle);
    }
}