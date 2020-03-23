#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 800){
	camera = new Camera();
	scene_1 = new Scene();

	scene_1->loadScene("./resources/scene_1.json");
	background = static_cast<Layer*>(scene_1->getChild("background"));
	midground = static_cast<Layer*>(scene_1->getChild("midground"));
	foreground = static_cast<Layer*>(scene_1->getChild("foreground"));

	foreground->speedRate=5.0;
	background->speedRate=4.0;
	midground->speedRate=2.0;

	main_character = new AnimatedSprite("Run");
	main_character->addAnimation("./resources/character/","Run",20,1,true);
	main_character->play("Run");
	main_character->layer="foreground";

	this->addChild(camera);
	camera->addChild(scene_1);
	foreground->addChild(main_character);

	main_character->position.x = 600 - (main_character->width / 2);		// 1/2 screenwidth
	main_character->position.y = 400 - (main_character->height / 2);	// 1/2 screenheight

}

MyGame::~MyGame(){
	delete scene_1;
	delete camera;
}

void MyGame::update(set<SDL_Scancode> pressedKeys){
	// std::cout << "Camera: " << camera->position.x << " " << camera->position.y << " | ";
	// std::cout << "Sun Sprite: " << scene_1->getChild("test_sun")->position.x << " " << scene_1->getChild("test_sun")->position.y << " | ";
	// std::cout << "Character: " << main_character->position.x << " " << main_character->position.y << " | ";
	// std::cout << "Scene Pivot: " << scene_1->pivot.x << " " << scene_1->pivot.y << std::endl;

	for (std::set<SDL_Scancode>::iterator it = pressedKeys.begin(); it != pressedKeys.end(); ++it){
		switch(*it){
			// Translation
			// While I could "multiply" the speedRates into the current movement of every layer, they all start at 1.0 so I don't bother multiplying by 1.0
			case SDL_SCANCODE_LEFT:	// Left arrow key
				camera->position.x += foreground->speedRate;
				main_character->position.x -= foreground->speedRate;

				background->position.x -= background->speedRate;
				midground->position.x -= midground->speedRate;
				break;
			case SDL_SCANCODE_RIGHT:	// Right arrow key
				camera->position.x -= foreground->speedRate;
				main_character->position.x += foreground->speedRate;
				
				background->position.x += background->speedRate;
				midground->position.x += midground->speedRate;
				break;
			case SDL_SCANCODE_UP:	// Up arrow key
				break;
			case SDL_SCANCODE_DOWN:	// Down arrow key
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
				break;
			// Pivot Movement
			case SDL_SCANCODE_I:
				break;
			case SDL_SCANCODE_J:
				break;
			case SDL_SCANCODE_K:
				break;
			case SDL_SCANCODE_L:
				break;
			// Rotation
			case SDL_SCANCODE_A:
				break;
			case SDL_SCANCODE_S:
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
