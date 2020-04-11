#include "Light.h"

Light::Light(string id, string color) {
  this->id = id + "_LIGHT";

  this->color = color;
  this->loadTexture("./resources/light/" + color + "_light" + direction + ".png");
}

Light::~Light() {
  if(texture != NULL) SDL_DestroyTexture(texture);
}

void Light::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
  DisplayObject::update(pressedKeys,currState);
}

void Light::draw(AffineTransform &at) {
  DisplayObject::draw(at);
}
