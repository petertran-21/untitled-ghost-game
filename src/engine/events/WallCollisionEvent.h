#ifndef WALLCOLLISIONEVENT_H
#define WALLCOLLISIONEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObject.h"

using namespace std;

class WallCollisionEvent : public Event {
public:
  WallCollisionEvent();
  WallCollisionEvent(EventDispatcher* source, DisplayObject* character, DisplayObject* enemy);
  ~WallCollisionEvent();
  void checkCondition();

  DisplayObject* character;
  DisplayObject* wall;

  const static string BLOCK_MOVEMENT;

private:

};

#endif
