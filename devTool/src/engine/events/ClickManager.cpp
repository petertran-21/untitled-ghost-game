#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "ClickManager.h"
#include "MouseClickEvent.h"

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
      }
  }
  }
}
