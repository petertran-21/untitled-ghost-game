#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000){
	scene_1 = new Scene();
	scene_2 = new Scene();

	scene_1->loadScene("./resources/scene_1.json");		// PLACEHOLDER! REPLACE WITH ACTUAL SCENE FILE FOR SUBMISSION
	scene_2->loadScene("./resources/scene_2.json");		// PLACEHOLDER! REPLACE WITH ACTUAL SCENE FILE FOR SUBMISSION
	using_scene_1 = true;	// If true, scene_1 should be the child of MyGame. If false, scene_2 should be the child.
	this->addChild(scene_1);
}

MyGame::~MyGame(){
	delete scene_1;
	delete scene_2;
}

void MyGame::update(set<SDL_Scancode> pressedKeys){
	for (std::set<SDL_Scancode>::iterator it = pressedKeys.begin(); it != pressedKeys.end(); ++it){
		switch(*it){
			// Translation
			case SDL_SCANCODE_LEFT:	// Left arrow key
				this->position.x -= 5;
				break;
			case SDL_SCANCODE_RIGHT:	// Right arrow key
				this->position.x += 5;
				break;
			case SDL_SCANCODE_UP:	// Up arrow key
				this->position.y -= 5;
				break;
			case SDL_SCANCODE_DOWN:	// Down arrow key
				this->position.y += 5;
				break;
			// Scaling
			case SDL_SCANCODE_Q:
				if (this->scaleX > 0.2 && this->scaleY > 0.2){	// max size 0.1
					this->scaleX -= 0.1;
					this->scaleY -= 0.1;
				}
				break;
			case SDL_SCANCODE_W:
				this->scaleX += 0.1;
				this->scaleY += 0.1;
				break;
			// Pivot Movement
			case SDL_SCANCODE_I:
				this->pivot.y-= 5;
				break;
			case SDL_SCANCODE_J:
				this->pivot.x-= 5;
				break;
			case SDL_SCANCODE_K:
				this->pivot.y+= 5;
				break;
			case SDL_SCANCODE_L:
				this->pivot.x+= 5;
				break;
			// Rotation
			case SDL_SCANCODE_A:
				this->rotation++;
				break;
			case SDL_SCANCODE_S:
				this->rotation-=2;		// To future me: since at the start of update we're rotating++, we need -= to counteract more than normal.
				break;
			// Visibility
			case SDL_SCANCODE_P:
				if (using_scene_1){		// We were using Scene 1, so switch to Scene 2 now.
					this->addChild(scene_2);
					this->children.erase(std::remove(this->children.begin(), this->children.end(), scene_1), this->children.end());
				} else {
					this->addChild(scene_1);
					this->children.erase(std::remove(this->children.begin(), this->children.end(), scene_2), this->children.end());
				}
				using_scene_1 = !using_scene_1;
				break;
			// Transparency
			case SDL_SCANCODE_Z:	// Fade in
				if (alpha < 250) { alpha += 5; }
				break;
			case SDL_SCANCODE_X:	// Fade out
				if (alpha > 5){ alpha -= 5; }
				break;
		}

	}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	SDL_RenderClear(Game::renderer);
	Game::draw(at);
	SDL_RenderPresent(Game::renderer);
}