#include <iostream>
#include <cstdlib>
#include "MainNPC.h"

using namespace std;

MainNPC::MainNPC() : AnimatedSprite("NPC"){
    
}

void MainNPC::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

    MainNPC::state_execute(pressedKeys, currState);

    //cooldown on ability usage
    if (cooldown_timer > 0) cooldown_timer--;

}

void MainNPC::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

//GENERAL NPC STATES
void MainNPC::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: IDLE" << endl;

    ///////////////////////////////////////////////REMOVE THIS, TESTING PURPOSES ONLY
    //check for possession
    // for(int code:pressedKeys){
	// 	switch (code) {
	// 		case SDL_SCANCODE_E: 
    //             is_possessed = true;
    //             break;
    //     }
    // }
    ///////////////////////////////////////////////

    if (is_possessed) state_switch(npc_states::Possessed);
}

void MainNPC::state_possessed(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: POSSESSED" << endl;

    if (Controls::holdLeft(pressedKeys, currState))state_switch(npc_states::Moving);
    if (Controls::holdRight(pressedKeys, currState)) state_switch(npc_states::Moving);
    if (Controls::holdUp(pressedKeys, currState)) state_switch(npc_states::Moving);
    if (Controls::holdDown(pressedKeys, currState)) state_switch(npc_states::Moving);

    //exit NPC
    if (Controls::pressPossess(pressedKeys, currState)){
        state_switch(npc_states::Idle);
        is_possessed = false;
    }

    //ability
    if (Controls::pressAbility(pressedKeys, currState)){
        if (cooldown_timer == 0){
            state_switch(npc_states::Ability); 
            cooldown_timer = cooldown_max;
        }
    }

    
    // for(int code:pressedKeys){
	// 	switch (code) {
    //         //check for movement
	// 		case SDL_SCANCODE_W: 
    //         case SDL_SCANCODE_A: 
    //         case SDL_SCANCODE_S: 
    //         case SDL_SCANCODE_D: state_switch(Moving); break;
    //         //activate ability
    //         case SDL_SCANCODE_SPACE: 
    //             if (cooldown_timer == 0){
    //                 state_switch(Ability); 
    //                 cooldown_timer = cooldown_max;
    //             }
    //             break;
    //         //exit NPC
    //         case SDL_SCANCODE_E: 
    //             state_switch(Idle);
    //             is_possessed = false;
    //             break;
    //     }
    // }
}

void MainNPC::state_moving(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: MOVING" << endl;

    bool is_moving = false;
    //check for movement on controller
    if (currState.leftStickY < 0){ is_moving = true; dir = N;}
    else if (currState.leftStickX < 0){ is_moving = true; dir = W;}
    else if (currState.leftStickY > 0){ is_moving = true; dir = S;}
    else if (currState.leftStickX > 0){ is_moving = true; dir = E;}

    //check for movement on keyboard
    for(int code:pressedKeys){
        if      (code == SDL_SCANCODE_W || currState.leftStickY < 0){ is_moving = true; dir = N;}
        else if (code == SDL_SCANCODE_A || currState.leftStickX < 0){ is_moving = true; dir = W;}
        else if (code == SDL_SCANCODE_S || currState.leftStickY > 0){ is_moving = true; dir = S;}
        else if (code == SDL_SCANCODE_D || currState.leftStickY > 0){ is_moving = true; dir = E;}
    }

    //move npc along grid
    if (is_moving && can_move){
        switch (dir){
            case N: 
                //check collision @ direction//
                position.y -= grid_size; 
                abilityPt = {0, -100};
                break;
            case S:
                //check collision @ direction//
                position.y += grid_size;
                abilityPt = {0, 100};
                break;
            case E: 
                //check collision @ direction//
                position.x += grid_size; 
                abilityPt = {100, 0};
                break;
            case W: 
                //check collision @ direction//
                position.x -= grid_size; 
                abilityPt = {-100, 0};
                break;
        }

        for (DisplayObject* child:children){
                    switch (dir){
            case N: 
                //check collision @ direction//
                child->position.y += grid_size; 
                break;
            case S:
                //check collision @ direction//
                child->position.y -= grid_size;
                break;
            case E: 
                //check collision @ direction//
                child->position.x -= grid_size; 
                break;
            case W: 
                //check collision @ direction//
                child->position.x += grid_size; 
                break;
            }
        }

        cout << "abilityPt: "<<abilityPt.x << ", "<<abilityPt.y <<endl;
        cout << "position: "<<position.x << ", "<<position.y <<endl;
        
        can_move = false;
    }

    //leave state on key release
    if (!is_moving){
        can_move = true;
        state_switch(npc_states::Possessed);
    }
}


//STATE MACHINE METHODS
void MainNPC::state_switch(npc_states new_state){
    if (state != new_state){
        state_new = true;
        state = new_state;
        state_updated = true;
    }
}
void MainNPC::state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    switch(state){
        case npc_states::Idle:      MainNPC::state_idle(pressedKeys, currState);      break;
        case npc_states::Possessed: MainNPC::state_possessed(pressedKeys, currState); break;
        case npc_states::Moving:    MainNPC::state_moving(pressedKeys, currState);    break;
        case npc_states::Ability:   state_ability(pressedKeys, currState);            break;
    }
    if (state_updated) state_updated = false;
    else state_new = false;
}