#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Grid.h"
#include <algorithm>
#include <string>

using namespace std;

int Grid::cellSize = 20;

Grid::Grid(int windowWidth, int windowHeight){
  this->windowWidth = windowWidth;
  this->windowHeight = windowHeight;
  this->gridWidth = (windowWidth / cellSize) * 2;
	this->gridHeight = (windowHeight / cellSize) * 2;
}

Grid::~Grid(){}

void Grid::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void Grid::draw(AffineTransform &at) {
  SDL_SetRenderDrawColor(Game::renderer, 120, 120, 120, 1);
  SDL_RenderClear(Game::renderer);

  SDL_SetRenderDrawColor(Game::renderer, 200, 200, 200, 1);
  for (int x = 0; x < 1 + this->gridWidth * cellSize; x += cellSize) {
      SDL_RenderDrawLine(Game::renderer, x, 0, x, windowHeight);
  }
	for (int y = 0; y < 1 + this->gridHeight * cellSize; y += cellSize) {
      SDL_RenderDrawLine(Game::renderer, 0, y, windowWidth, y);
  }
  DisplayObjectContainer::draw(at);
}
