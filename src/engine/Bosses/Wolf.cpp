#include <iostream>
// #include <chrono>
// #include <thread>
// #include <functional>

#include <cstdlib>
#include "Wolf.h"
#include "Ghost.h"

using namespace std;

Wolf::Wolf() : MainBoss(){
    this->subtype = "wolf";
    this->position.x = 100;
    this->position.y = 100;

	this->addAnimation("./resources/bosses/", "wolf_idle", 1, 1, false);
    this->addAnimation("./resources/bosses/", "wolf_attack", 1, 1, false);
}

void Wolf::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    AnimatedSprite::update(pressedKeys, currState);

    Wolf::state_execute(pressedKeys, currState);

    if (this->state == boss_states::Attack){
        cout << "WOLF STATE: ATTACK" << endl;
        int i = 0;
        while(i < 9000000){
            i++;
        }
        this->play("wolf_attack");
        //EJECT GHOST FROM NPC
        //extern state_switch(ghost_states::Idle);
        this->state = boss_states::Idle;
    }

    if (this->state == boss_states::Idle){
        cout << "WOLF STATE: IDLE" << endl;

        this->play("wolf_idle");
        this->state = boss_states::Attack;
    }
}

void Wolf::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    // cout <<"state_attack is called"<<endl;
    cout << "in idle state" << endl;
    // this->play("wolf_attack");
    // state_switch(boss_states::Idle);
    if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "WOLF STATE: IDLE" << endl;
	}
	//anything that should always run while in this state
	this->play("wolf_idle");
    
    for(int i = 1; i <= 1000000; i++){
        cout << "this is iteraton " << i << endl;
        if(i%1000000 == 0){
            cout << "we are changing the state...hopefully" << endl;
            state_switch(boss_states::Attack);
        }
    }

}

void Wolf::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    // cout <<"state_attack is called"<<endl;
    cout << "in attack state" << endl;
    // this->play("wolf_attack");
    // state_switch(boss_states::Idle);
    if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "WOLF STATE: ATTACK" << endl;
	}
	//anything that should always run while in this state
	this->play("wolf_attack");

}