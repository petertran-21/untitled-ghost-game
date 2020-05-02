#include "UIDefs.h"

Map::Map() : AnimatedSprite(){
  this->width = 1000;
  this->height = 750;
  this->position.y = 50;
  this->addAnimation("./resources/map/", "gameMap", 1, 1, true, "plain");
  this->addAnimation("./resources/map/", "forestHighlight", 1, 1, true, "forest");
  this->addAnimation("./resources/map/", "swampHighlight", 1, 1, true, "swamp");
  this->addAnimation("./resources/map/", "beachHighlight", 1, 1, true, "beach");
  this->addAnimation("./resources/map/", "mountainsHighlight", 1, 1, true, "mountain");
  this->addAnimation("./resources/map/", "townHighlight", 1, 1, true, "town");

	this->play("plain");
}

Map::~Map(){
}

void Map::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
  if(active) {
    if(pressedKeys.find(SDL_SCANCODE_1) != pressedKeys.end()) {
      this->play("mountain");
      mountainHighlighted = true;
      swampHighlighted = false;
      forestHighlighted = false;
      beachHighlighted = false;
      townHighlighted = false;
    }
    else if(pressedKeys.find(SDL_SCANCODE_2) != pressedKeys.end()) {
      this->play("swamp");
      mountainHighlighted = false;
      swampHighlighted = true;
      forestHighlighted = false;
      beachHighlighted = false;
      townHighlighted = false;
    }
    else if(pressedKeys.find(SDL_SCANCODE_3) != pressedKeys.end()) {
      this->play("forest");
      mountainHighlighted = false;
      swampHighlighted = false;
      forestHighlighted = true;
      beachHighlighted = false;
      townHighlighted = false;
    }
    else if(pressedKeys.find(SDL_SCANCODE_4) != pressedKeys.end()) {
      this->play("beach");
      mountainHighlighted = false;
      swampHighlighted = false;
      forestHighlighted = false;
      beachHighlighted = true;
      townHighlighted = false;
    }
    else if(pressedKeys.find(SDL_SCANCODE_5) != pressedKeys.end()) {
      this->play("town");
      mountainHighlighted = false;
      swampHighlighted = false;
      forestHighlighted = false;
      beachHighlighted = false;
      townHighlighted = true;
    }

    if(pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
      if(mountainHighlighted) {
        // LOAD MOUNTAIN SCENE 1
      } else if(swampHighlighted) {
        // LOAD SWAMP SCENE 1
      } else if(forestHighlighted) {
        // LOAD FOREST SCENE 1
      } else if(beachHighlighted) {
        // LOAD BEACH SCENE 1
      } else if(townHighlighted) {
        // LOAD TOWN SCENE 1
      }
    }

    if(pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
      this->active = false;
    }
    AnimatedSprite::update(pressedKeys, currState);
  }
  else {
    this->play("plain");
    AnimatedSprite::update(pressedKeys, currState);
  }
}

void Map::draw(AffineTransform &at){
  AnimatedSprite::draw(at);
}
