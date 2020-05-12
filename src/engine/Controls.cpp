#include "Controls.h"
#include "Sound.h"

bool Controls::pressing_possess = false;
bool Controls::pressing_boo = false;
bool Controls::pressing_ability = false;

bool Controls::holdRight(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  //need to add controller check to if statement
  if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end() || currState.leftStickX > 0) {
    return true;
  }
  return false;
}

bool Controls::holdLeft(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  //need to add controller check to if statement
  if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end() || currState.leftStickX < 0) {
    return true;
  }
  return false;
}

bool Controls::holdUp(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  //need to add controller check to if statement
  if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end() || currState.leftStickY < 0) {
    return true;
  }
  return false;
}

bool Controls::holdDown(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  //need to add controller check to if statement
  if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end() || currState.leftStickY > 0) {
		return true;
  }
  return false;
}

bool Controls::pressPossess(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){

  if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end() || currState.buttonA){

    if (pressing_possess == false){
      Sound* soundManager = new Sound();
      soundManager->playSFX("./resources/sfx/possession.wav");
      pressing_possess = true;
      return true;
    }
    return false;

  }
  else {
    pressing_possess = false;
  }
  return false;
    
}

bool Controls::pressBoo(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){

  if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end() || currState.buttonY){

    if (pressing_boo == false){
      pressing_boo = true;
      return true;
    }
    return false;

  }
  else {
    pressing_boo = false;
  }
  return false;
}

bool Controls::pressAbility(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  if (pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.end() || currState.buttonX){

    if (pressing_ability == false){
      pressing_ability = true;
      return true;
    }
    return false;

  }
  else {
    pressing_ability = false;
  }
  return false;
}
    
bool Controls::reverse_controls(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  return false;
}

