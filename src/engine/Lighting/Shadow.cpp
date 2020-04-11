#include "Shadow.h"

Shadow::Shadow(string id, string color) {
  this->id = id + "_SHADOW";

  this->shape = shape;
  this->loadTexture("./resources/light/" + shape + "_shadow.png");
}

Shadow::~Shadow() {
  if(texture != NULL) SDL_DestroyTexture(texture);
}

void Shadow::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
  DisplayObject::update(pressedKeys,currState);
}

void Shadow::draw(AffineTransform &at) {
  DisplayObject::draw(at);
}
