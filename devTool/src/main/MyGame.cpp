#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"
#include "Scene.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

MyGame::MyGame() : Game(1200, 700) {
	instance = this;

	camera = new Camera();
	this->addChild(camera);
	allSprites = new Scene();
	camera->addChild(allSprites);

	character = new AnimatedSprite("character");
	character->addAnimation("./resources/character/", "Idle", 16, 3, true);

	character->play("Idle");

	character->width = character->height = 100 - (100 % Game::cellSize);
	character->position.x = character->position.y = 0;
	allSprites->addChild(character);

	character1 = new AnimatedSprite("character1");
	character1->addAnimation("./resources/character/", "Idle", 16, 3, true);

	character1->play("Idle");

	character1->width = character1->height = 100 - (100 % Game::cellSize);
	character1->position.x = character1->position.y = Game::cellSize;
	allSprites->addChild(character1);

	templateBar = new TemplateBar("templateBar", 64, 224, 208);


	instance->addChild(templateBar);
	templateBar->loadTemplateBar();

	mouseDisp = new EventDispatcher();
	mouseClick = new MouseClickEvent(mouseDisp, templateBar, Game::mouse, allSprites);
	clickManager = new ClickManager();
	mouseDisp->addEventListener(clickManager, MouseClickEvent::TILE_SELECTED);

}

MyGame::~MyGame(){
	delete camera;
}


void MyGame::update(set<SDL_Scancode> pressedKeys){
	for(DisplayObject * character : allSprites->children) {
	// X, Y is location of start, X2, Y2 is location of current
		if (Game::mouse->leftClick) {
			if(character->position.x + camera->position.x < Game::mouse->selectBoxX && Game::mouse->selectBoxX < character->position.x + character->width + camera->position.x
			&& character->position.y + camera->position.y < Game::mouse->selectBoxY && Game::mouse->selectBoxY < character->position.y + character->height + camera->position.y
			&& Game::mouse->selectBoxX2 == Game::mouse->selectBoxX && Game::mouse->selectBoxY2 == Game::mouse->selectBoxY) {
				character->selected = true;
				character->isBeingDragged = true;
				this->noSpritesSelected = false;
			} else if (!(Game::mouse->selectBoxX2 == Game::mouse->selectBoxX) && !(Game::mouse->selectBoxY2 == Game::mouse->selectBoxY)) {
				int topRX, topRY,botLX,botLY;
				topRX = topRY = botLX = botLY = -1;
				if(Game::mouse->selectBoxX < Game::mouse->selectBoxX2 && Game::mouse->selectBoxY < Game::mouse->selectBoxY2) { // is the current mouse location the topR of the rect ?
					// start is top left, current is bottom right
					topRX = Game::mouse->selectBoxX2;
					topRY = Game::mouse->selectBoxY;
					botLX = Game::mouse->selectBoxX;
					botLY = Game::mouse->selectBoxY2;
				} else if(Game::mouse->selectBoxX > Game::mouse->selectBoxX2 && Game::mouse->selectBoxY < Game::mouse->selectBoxY2) { // is the current mouse location the topR of the rect ?
					// start is top right, current is bottom left
					topRX = Game::mouse->selectBoxX;
					topRY = Game::mouse->selectBoxY;
					botLX = Game::mouse->selectBoxX2;
					botLY = Game::mouse->selectBoxY2;
				} else if(Game::mouse->selectBoxX < Game::mouse->selectBoxX2 && Game::mouse->selectBoxY > Game::mouse->selectBoxY2) { // is the current mouse location the topR of the rect ?
					// start is bottom left, , current is top right
					topRX = Game::mouse->selectBoxX2;
					topRY = Game::mouse->selectBoxY2;
					botLX = Game::mouse->selectBoxX;
					botLY = Game::mouse->selectBoxY;
				} else if(Game::mouse->selectBoxX > Game::mouse->selectBoxX2 && Game::mouse->selectBoxY > Game::mouse->selectBoxY2) { // is the current mouse location the topR of the rect ?
					// start is bottom right, , current is top left
					topRX = Game::mouse->selectBoxX;
					topRY = Game::mouse->selectBoxY2;
					botLX = Game::mouse->selectBoxX2;
					botLY = Game::mouse->selectBoxY;
				}

				if(character->position.x + camera->position.x < topRX &&
					 botLX < character->position.x + character->width  + camera->position.x &&
					 character->position.y + character->height + camera->position.y > topRY &&
					 botLY > character->position.y + camera->position.y) {
								character->selected = true;
								this->noSpritesSelected = false;
				}
			} else {
					character->selected = false;
				}

			if(character->isBeingDragged) {
				Game::mouse->isDraggingObject = true;
				character->position.x = (Game::mouse->curCoords.x - camera->position.x) - character->width/2;
				character->position.y = (Game::mouse->curCoords.y - camera->position.y) - character->height/2;
			}
		} else {
			Game::mouse->isDraggingObject = false;
			character->position.x = character->position.x - (character->position.x % Game::cellSize);
			character->position.y = character->position.y - (character->position.y % Game::cellSize);
			character->isBeingDragged = false;
		}


		if (character->selected) {
			if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
				character->position.x += Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
				character->position.x -= Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
				character->position.y += Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
				character->position.y -= Game::cellSize;
			}
			if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
				character->width = ceil(1.1*character->width/Game::cellSize) * Game::cellSize;
				character->height =  ceil(1.1*character->height/Game::cellSize) * Game::cellSize;

			}
			if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
				if (floor((character->width/1.1)/Game::cellSize) == 0 || floor((character->height/1.1)/Game::cellSize) == 0) {
					character->width = 1 * Game::cellSize;
					character->height = 1 * Game::cellSize;
				} else {
					character->width = floor((character->width/1.1)/Game::cellSize) * Game::cellSize;
					character->height = floor((character->height/1.1)/Game::cellSize) * Game::cellSize;
				}
			} else {
				this->noSpritesSelected = true;
			}

			if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
				// handle copy paste
			}
		}

	}


	if(noSpritesSelected) {
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			camera->position.x += Game::cellSize;
		}
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
			camera->position.x -= Game::cellSize;
		}
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			camera->position.y += Game::cellSize;
		}
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			camera->position.y -= Game::cellSize;
		}
	}


  if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()){
      cout << "Load Scene: ";
      string scenePath = "./resources/scenes/";
      string sceneName;
      cin >> sceneName;
      cout << scenePath + sceneName << endl;
      try{
          allSprites->loadScene(scenePath + sceneName + ".json");
      } catch(exception& e) {
          cout << "Error: " << e.what() << endl;
      }
  }

	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()){
		cout << "Save Scene: ";
		string scenePath = "./resources/scenes/";
		string sceneName;
		cin >> sceneName;
		cout << scenePath + sceneName << endl;
		allSprites->saveScene(scenePath + sceneName);
	}

	if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()){
		if (templateBar->position.x < Game::windowWidth){
			templateBar->position.x += Game::cellSize;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
		if (templateBar->position.x + templateBar->width > 0){
			templateBar->position.x -= Game::cellSize;
		}
	}

	mouseClick->checkCondition();
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
