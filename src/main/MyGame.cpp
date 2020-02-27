#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 800){
	camera = new Camera();
	sound_manager = new Sound();
	scene_1 = new Scene();
	scene_2 = new Scene();

	sound_manager->playSFX("./resources/coin.wav");

	scene_1->loadScene("./resources/scene_1.json");
	main_character = new DisplayObjectContainer("main_character", "./resources/character/Idle_1.png");

	this->addChild(camera);
	camera->addChild(scene_1);
	scene_1->addChild(main_character);

	main_character->position.x = 600 - (main_character->width / 2);		// 1/2 screenwidth
	main_character->position.y = 400 - (main_character->height / 2);	// 1/2 screenheight

}

MyGame::~MyGame(){
	delete scene_1;
	delete scene_2;
	delete sound_manager;
	delete camera;
}

void MyGame::update(set<SDL_Scancode> pressedKeys){
	std::cout << "Camera: " << camera->position.x << " " << camera->position.y << " | ";
	std::cout << "Sun Sprite: " << scene_1->getChild("test_sun")->position.x << " " << scene_1->getChild("test_sun")->position.y << " | ";
	std::cout << "Character: " << main_character->position.x << " " << main_character->position.y << " | ";
	std::cout << "Scene Pivot: " << scene_1->pivot.x << " " << scene_1->pivot.y << std::endl;

	if (main_character->position.y <= 300){
		scene_1->scaleX = 2.0;
		scene_1->scaleY = 2.0;

		// Janky solution to zoom in on camera
		camera->position = {-main_character->position.x, -main_character->position.y};
	} else {
		scene_1->scaleX = 1.0;
		scene_1->scaleY = 1.0;

		// Janky solution to keep camera centered on character
		camera->position.x = -(main_character->position.x - (600 - (main_character->width / 2)));
		camera->position.y = -(main_character->position.y - (400 - (main_character->height / 2)));
	}
	for (std::set<SDL_Scancode>::iterator it = pressedKeys.begin(); it != pressedKeys.end(); ++it){
		switch(*it){
			// Translation
			case SDL_SCANCODE_LEFT:	// Left arrow key
				if (main_character->position.x > 100){		// hardcoded boundaries...
					camera->position.x += 5;
					main_character->position.x -= 5;
				}
				// this->position.x -= 10;
				// main_character->position.x -= 5;
				break;
			case SDL_SCANCODE_RIGHT:	// Right arrow key
				if (main_character->position.y < 900 && main_character->position.x < 700 || main_character->position.y >= 900 && main_character->position.x < 1290){
					camera->position.x -= 5;
					main_character->position.x += 5;
				}
				// this->position.x += 10;
				// main_character->position.x += 5;
				break;
			case SDL_SCANCODE_UP:	// Up arrow key
				if (main_character->position.y > 95 && main_character->position.x <= 700 || main_character->position.x > 700 && main_character->position.y > 900){
					camera->position.y += 5;
					main_character->position.y -= 5;
				}
				// this->position.y -= 10;
				// main_character->position.y -= 5;
				break;
			case SDL_SCANCODE_DOWN:	// Down arrow key
				if (main_character->position.y < 1340){
					camera->position.y -= 5;
					main_character->position.y += 5;
				}
				// this->position.y += 10;
				// main_character->position.y += 5;
				break;
			// Scaling
			case SDL_SCANCODE_Q:
				// camera->scaleX -= 0.1;
				// camera->scaleY -= 0.1;
				// if (this->scaleX > 0.2 && this->scaleY > 0.2){	// max size 0.1
				// 	this->scaleX -= 0.1;
				// 	this->scaleY -= 0.1;
				// }
				break;
			case SDL_SCANCODE_W:
				// camera->scaleX += 0.1;
				// camera->scaleY += 0.1;
				// this->scaleX += 0.1;
				// this->scaleY += 0.1;
				break;
			// Pivot Movement
			case SDL_SCANCODE_I:
				// this->pivot.y-= 5;
				break;
			case SDL_SCANCODE_J:
				// this->pivot.x-= 5;
				break;
			case SDL_SCANCODE_K:
				// this->pivot.y+= 5;
				break;
			case SDL_SCANCODE_L:
				// this->pivot.x+= 5;
				break;
			// Rotation
			case SDL_SCANCODE_A:
				// this->rotation++;
				break;
			case SDL_SCANCODE_S:
				// this->rotation-=2;		// To future me: since at the start of update we're rotating++, we need -= to counteract more than normal.
				break;
			// Visibility
			case SDL_SCANCODE_P:
				// if (using_scene_1){		// We were using Scene 1, so switch to Scene 2 now.
				// 	this->addChild(scene_2);
				// 	this->children.erase(std::remove(this->children.begin(), this->children.end(), scene_1), this->children.end());
				// } else {
				// 	this->addChild(scene_1);
				// 	this->children.erase(std::remove(this->children.begin(), this->children.end(), scene_2), this->children.end());
				// }
				// using_scene_1 = !using_scene_1;
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
	//SDL_RenderClear(Game::renderer);
	Game::draw(at);
	//SDL_RenderPresent(Game::renderer);
}
