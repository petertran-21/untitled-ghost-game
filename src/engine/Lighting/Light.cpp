#include "Light.h"
#include <string>

Light::Light(string id, string color) {
  this->id = id + "_LIGHT";

  this->color = color;
  this->loadTexture("./resources/lighting/" + color + "_light" + to_string(direction) + ".png");
}

Light::~Light() { }

void Light::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
  DisplayObject::update(pressedKeys,currState);
}

void Light::draw(AffineTransform &at) {
  DisplayObject::draw(at);
}
