#include "Mouse.h"

Mouse::Mouse() {};
Mouse::~Mouse() {};

void Mouse::setState(SDL_Event event) {
  switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
      startCoords.x = event.motion.x;
      startCoords.y = event.motion.y;
      leftClick = true;
      leftChanged = true;
      break;
    case SDL_MOUSEBUTTONUP:
      leftClick = false;
      break;
    case SDL_MOUSEMOTION:
      curCoords.x = event.motion.x;
      curCoords.y = event.motion.y;
      mouseMoving = true;
      break;
  }
}

Mouse::MouseLocation Mouse::getMouseLocation() {
  return curCoords;
}
void Mouse::drawSelectBox(SDL_Renderer *renderer) {
  if (leftClick && !isDraggingObject) {
    selectBoxW = curCoords.x - startCoords.x;
    selectBoxH = curCoords.y - startCoords.y;
    selectBoxX = startCoords.x;
    selectBoxY = startCoords.y;
    selectBoxX2 = curCoords.x;
    selectBoxY2 = curCoords.y;

    SDL_Rect rect;
    rect.x = selectBoxX;
    rect.y = selectBoxY;
    rect.w = selectBoxW;
    rect.h = selectBoxH;
    SDL_SetRenderDrawColor(renderer,200,155,255,1);
    SDL_RenderDrawRect(renderer, &rect);
  }
}
