#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "MyGame.h"
#include "Scene.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;

	allSprites = new Scene();
	// move that point to the middle
	instance->addChild(allSprites);

	character = new AnimatedSprite("character");
	character->addAnimation("./resources/character/", "Idle", 16, 3, true);

	character->play("Idle");

	character->width = character->height = 100 - (100 % Game::cellSize);
	allSprites->addChild(character);


}

MyGame::~MyGame(){
}


void MyGame::update(set<SDL_Scancode> pressedKeys){

	for(DisplayObject * character : allSprites->children) {
	// X, Y is location of start, X2, Y2 is location of current
		if (Game::mouse->leftClick) {
			if(character->position.x < Game::mouse->selectBoxX && Game::mouse->selectBoxX < character->position.x + character->width
			&& character->position.y < Game::mouse->selectBoxY && Game::mouse->selectBoxY < character->position.y + character->height
			&& Game::mouse->selectBoxX2 == Game::mouse->selectBoxX && Game::mouse->selectBoxY2 == Game::mouse->selectBoxY) {
				character->selected = true;
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
					topRX = Game::mouse->selectBoxX;
					topRY = Game::mouse->selectBoxY;
					botLX = Game::mouse->selectBoxX2;
					botLY = Game::mouse->selectBoxY2;
				} else if(Game::mouse->selectBoxX > Game::mouse->selectBoxX2 && Game::mouse->selectBoxY > Game::mouse->selectBoxY2) { // is the current mouse location the topR of the rect ?
					// start is bottom right, , current is top left
					topRX = Game::mouse->selectBoxX;
					topRY = Game::mouse->selectBoxY2;
					botLX = Game::mouse->selectBoxX2;
					botLY = Game::mouse->selectBoxY;
				}

				if(character->position.x < topRX &&
					 botLX < character->position.x + character->width &&
					 character->position.y + character->height > topRY &&
					 botLY > character->position.y) {
								character->selected = true;
				}
			} else {
					character->selected = false;
				}
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
			}
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

	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
