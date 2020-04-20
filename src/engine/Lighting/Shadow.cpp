#include "Shadow.h"

Shadow::Shadow(string id, string shape, int direction) {
  this->id = id + "_SHADOW";

  this->shape = shape;
  this->loadTexture("./resources/lighting/" + shape + "_shadow" + to_string(direction) + ".png");
}

Shadow::~Shadow() { }

void Shadow::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
  DisplayObject::update(pressedKeys,currState);
}

void Shadow::draw(AffineTransform &at) {
  DisplayObject::draw(at);
}
