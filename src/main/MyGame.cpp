#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1000, 1000){
	//------------Work from the SFX/Level Team
	camera = new Camera();
	scene_1 = new Scene();

	scene_1->loadScene("./resources/scenes/beachEntrance.json");

	this->addChild(camera);
	camera->addChild(scene_1);
	//-----------------------------------------

	//-------------Character Programming Demo 
	// instance = this;

	// environment = new DisplayObjectContainer();
	// instance->addChild(environment);

	// allSprites = new DisplayObjectContainer();
	// instance->addChild(allSprites);

	// collisionSystem = new CollisionSystem();
	// displayTreeDisp = new EventDispatcher();
	// DOAdded = new DOAddedEvent(displayTreeDisp, environment);
	// DORemoved = new DORemovedEvent(displayTreeDisp, environment);

	instance = this;

	allSprites = new DisplayObjectContainer();
	instance->addChild(allSprites);

	container = new DisplayObjectContainer();
	allSprites->addChild(container);

	collisionSystem = new CollisionSystem();
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);

	player = new Ghost();
	allSprites->addChild(player);
	
	npc = new NPCPyromancer();
	npc->position.x += 300;
	container->addChild(npc);
	npc->drawHitbox();
	DOAdded->addChildCalled(npc);
	DOAdded->checkCondition();

	NPCArcher* npc2 = new NPCArcher();
	container->addChild(npc2);
	npc2->drawHitbox();
	DOAdded->addChildCalled(npc2);
	DOAdded->checkCondition();

	npc->createHitbox();
	npc2->createHitbox();

	//uncomment following line to possess pyromancer
	// player->npc = npc;

	//run following line to possess archer
	player->npc = npc2;
	//-----------------------------------------


	// instance = this;

	// allSprites = new DisplayObjectContainer();
	// instance->addChild(allSprites);

	// container = new DisplayObjectContainer();
	// allSprites->addChild(container);

	// collisionSystem = new CollisionSystem();
	// displayTreeDisp = new EventDispatcher();
	// DOAdded = new DOAddedEvent(displayTreeDisp, container);
	// DORemoved = new DORemovedEvent(displayTreeDisp, container);
	// displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	// displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);
	

	// character = new AnimatedSprite("character");
	// character->addSpriteSheet("./resources/character/character_idle.png", "./resources/character/character_animations.xml", "idle", 16, 2, true);
	// character->addSpriteSheet("./resources/character/character_walk.png", "./resources/character/character_animations2.xml", "walk", 16, 2, true);
	// container->addChild(character);
	// character->drawHitbox();
	// character->play("idle");
	// DOAdded->addChildCalled(character);
	// DOAdded->checkCondition();

	// crocodile = new Sprite("crocodile", "./resources/enemies/crocodile.png");
	// container->addChild(crocodile);
	// crocodile->drawHitbox();
	// crocodile->position.x = 300;
	// DOAdded->addChildCalled(crocodile);
	// DOAdded->checkCondition();

	// character->createHitbox();
	// crocodile->createHitbox();

}

MyGame::~MyGame(){
	delete scene_1;
	delete camera;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){

	// if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
	// 	character->position.x += 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
	// 	character->position.x -= 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
	// 	character->position.y += 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
	// 	character->position.y -= 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
	// 	character->scaleX *= 1.1;
	// 	character->scaleY *= 1.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
	// 	character->scaleX /= 1.1;
	// 	character->scaleY /= 1.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
	// 	character->rotation += 0.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
	// 	character->rotation -= 0.1;
	// }
	
	// if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
	// 	container->position.x += 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
	// 	container->position.x -= 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
	// 	container->position.y += 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
	// 	container->position.y -= 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {
	// 	container->scaleX *= 1.1;
	// 	container->scaleY *= 1.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {
	// 	container->scaleX /= 1.1;
	// 	container->scaleY /= 1.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
	// 	container->rotation += 0.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
	// 	container->rotation -= 0.1;
	// }

	// if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
	// 	crocodile->position.x += 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
	// 	crocodile->position.x -= 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
	// 	crocodile->position.y += 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
	// 	crocodile->position.y -= 1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {
	// 	crocodile->scaleX *= 1.1;
	// 	crocodile->scaleY *= 1.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
	// 	crocodile->scaleX /= 1.1;
	// 	crocodile->scaleY /= 1.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
	// 	crocodile->rotation += 0.1;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
	// 	crocodile->rotation -= 0.1;
	// }
	collisionSystem->update();
	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	//SDL_RenderClear(Game::renderer);
	Game::draw(at);
	//SDL_RenderPresent(Game::renderer);
}