#include "Sprite.h"

using namespace std;

Sprite::Sprite() : DisplayObjectContainer() {
    this->type = "Sprite";
    this->subtype = SPRITE_SUBTYPE;
}

Sprite::Sprite(string id, string filepath) : DisplayObjectContainer(id, filepath){
    this->type = "Sprite";
    this->subtype = SPRITE_SUBTYPE;
}

Sprite::Sprite(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
    this->type = "Sprite";
}

void Sprite::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
    DisplayObjectContainer::update(pressedKeys, currState);
}

void Sprite::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}
