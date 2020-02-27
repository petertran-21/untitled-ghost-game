#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

class Mouse {
public:
  Mouse();
  ~Mouse();

  struct MouseLocation {
    int x = -1;
    int y = -1;
  };

  MouseLocation curCoords;
  MouseLocation startCoords;

  void setState(SDL_Event event);
  MouseLocation getMouseLocation();
  void drawSelectBox(SDL_Renderer *renderer);

  bool leftClick = false;
  bool leftChanged = false;

  int selectBoxW = 0;
  int selectBoxH = 0;
  int selectBoxX = 0;
  int selectBoxY = 0;
  int selectBoxX2 = 0;
  int selectBoxY2 = 0;
};

#endif
