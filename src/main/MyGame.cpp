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
	instance = this;

	allSprites = new DisplayObjectContainer();
	instance->addChild(allSprites);
	container = new DisplayObjectContainer();

	// uncomment following line to check that collision boxes for objects are identical to drawing
	allSprites->addChild(container);
	
	collisionSystem = new CollisionSystem();
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);

	Shrub* s = new Shrub(container);
	allSprites->addChild(s);
	container->addChild(s);

	npc = new NPCPyromancer(container); 
	npc->position.x += 300;
	allSprites->addChild(npc);
	container->addChild(npc);

	NPCArcher* npc2 = new NPCArcher(container);
	allSprites->addChild(npc2);
	container->addChild(npc2);

	player = new Ghost();
	allSprites->addChild(player);
	container->addChild(player);

	DOAdded->addChildCalled(container);
	DOAdded->checkCondition();
	
	//-----------------------------------------

}

MyGame::~MyGame(){
	delete scene_1;
	delete camera;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	collisionSystem->update();
	DORemoved->checkCondition();
	DOAdded->checkCondition();
	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	//SDL_RenderClear(Game::renderer);
	Game::draw(at);
	//SDL_RenderPresent(Game::renderer);
}