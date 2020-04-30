#include "UIDefs.h"

Map::Map() : AnimatedSprite(){
  this->addAnimation("./resources/map/", "gameMap", 1, 1, true, "plain");
  this->addAnimation("./resources/map/", "forestHighlight", 1, 1, true, "forest");
  this->addAnimation("./resources/map/", "swampHighlight", 1, 1, true, "swamp");
  this->addAnimation("./resources/map/", "beachHighlight", 1, 1, true, "beach");
  this->addAnimation("./resources/map/", "mountainHighlight", 1, 1, true, "mountain");

	this->play("plain");
}

Map::~Map(){
}

void Map::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  
  AnimatedSprite::update(pressedKeys, currState);
}

void Map::draw(AffineTransform &at){
  AnimatedSprite::draw(at);
}
