#ifndef GRID_H
#define GRID_H
#include "DisplayObjectContainer.h"
#include "Game.h"

class Grid : public DisplayObjectContainer{

public:
	Grid(int windowWidth, int windowHeight);
	~Grid();

  virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

  int windowWidth;
	int windowHeight;
  int gridWidth;
	int gridHeight;
	static int cellSize;

private:


};

#endif
