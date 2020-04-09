#include "Light.h"

Light::Light(DisplayObject* parent, string id, int red, int green, int blue) {
  this->parent = parent;
  this->id = id + "_LIGHT";

  this->red = red;
  this->green = green;
  this->blue = blue;

  this->loadRGBLight(red, green, blue);

}

Light::~Light() {
  if(texture != NULL) SDL_DestroyTexture(texture);
}

void Light::loadRGBTexture(int red, int green, int blue) {
  image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void Light::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
  DisplayObject::update(pressedKeys,currState);
}

void Light::draw(AffineTransform &at) {
  DisplayObject::draw(at);
}
