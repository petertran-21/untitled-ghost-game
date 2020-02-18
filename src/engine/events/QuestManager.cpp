#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "QuestManager.h"
#include "PickedUpEvent.h"

QuestManager::QuestManager() {

}
QuestManager::~QuestManager() {

}
void QuestManager::handleEvent(Event* e) {
  if (e->getType() == PickedUpEvent::COIN_PICKED_UP) {
    PickedUpEvent* event = (PickedUpEvent*) e;
    if (event->item->alpha != 0) {
      event->item->alpha = 0;
      std::cout << "You picked up a coin!" << std::endl;
    }
  }
}
