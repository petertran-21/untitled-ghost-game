#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObjectContainer.h"
#include "Mouse.h"
#include "Scene.h"

using namespace std;

class MouseClickEvent : public Event {
public:
  MouseClickEvent();
  MouseClickEvent(EventDispatcher* source, DisplayObjectContainer* character, Mouse* mouse, Scene* scene);
  ~MouseClickEvent();
  void checkCondition();

  DisplayObjectContainer* character;
  Mouse* mouse;
  Scene* scene;
  bool print = false;
  bool printed = false;

  const static string TILE_SELECTED;

private:

};

#endif
