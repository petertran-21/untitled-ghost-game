#ifndef PICKEDUPEVENT_H
#define PICKEDUPEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObject.h"

using namespace std;

class PickedUpEvent : public Event {
public:
  PickedUpEvent();
  PickedUpEvent(EventDispatcher* source, DisplayObject* character, DisplayObject* item);
  ~PickedUpEvent();
  void checkCondition();

  DisplayObject* character;
  DisplayObject* item;

  const static string COIN_PICKED_UP;

private:

};

#endif
