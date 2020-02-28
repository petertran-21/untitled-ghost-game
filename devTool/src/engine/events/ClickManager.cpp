#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "ClickManager.h"
#include "MouseClickEvent.h"
#include "AnimatedSprite.h"

ClickManager::ClickManager() {

}
ClickManager::~ClickManager() {

}
void ClickManager::handleEvent(Event* e) {
  if (e->getType() == MouseClickEvent::TILE_SELECTED) {
    MouseClickEvent* event = (MouseClickEvent*) e;
    for(DisplayObject* child : event->character->children) {
      if(child->selected) {
        std::cout << child->id << std::endl;
        if (child->type == "AnimatedSprite"){
          AnimatedSprite* duplicate = dynamic_cast<AnimatedSprite*>(child)->copy();
          duplicate->parent = event->scene;

          //event->scene->addChild(duplicate);
          cout << duplicate->imgPath << endl;
        }
        if (child->type == "Sprite"){
          Sprite* duplicate = dynamic_cast<Sprite*>(child)->copy();
          duplicate->parent = event->scene;
          duplicate->position.x += child->parent->position.x;
          duplicate->position.y = child->parent->position.y - duplicate->height;
          event->scene->addChild(duplicate);
        }
      }
  }
  }
}
