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

	// Shrub* s = new Shrub(container);
	// allSprites->addChild(s);
	// container->addChild(s);

	ItemPouch* p = new ItemPouch(container);
	p->position.x = 900;
	p->position.y = 900;
	allSprites->addChild(p);
	container->addChild(p);

	// npc = new NPCPyromancer(container, allSprites); 
	// npc->position.x += 300;
	// allSprites->addChild(npc);
	// container->addChild(npc);

	// NPCArcher* npc2 = new NPCArcher(container, allSprites);
	// allSprites->addChild(npc2);
	// container->addChild(npc2);

	// player = new Ghost();
	// allSprites->addChild(player);
	// container->addChild(player);

	// DOAdded->addChildCalled(container);
	// DOAdded->checkCondition();

	Shrub* s = new Shrub(container);
	allSprites->addChild(s);
	container->addChild(s);

	BreakableWall *b = new BreakableWall(container);
	allSprites->addChild(b);
	container->addChild(b);
	b->position.x += 200;
	b->position.y += 200;

	Valve * v = new Valve(container);
	allSprites->addChild(v);
	container->addChild(v);
	v->position.x += 500;
	v->position.y += 300;

	WaterJet * w = new WaterJet(container, allSprites);
	allSprites->addChild(w);
	container->addChild(w);
	v->add_jet(w);
	w->position.x += 700;
	w->position.y += 100;
	w->dir = S;

	Crab * c = new Crab();
	allSprites->addChild(c);
	container->addChild(c);
	c->position.y += 600;
	c->position.x += 600;

	npc = new NPCPyromancer(container, allSprites); 
	npc->position.x += 300;
	allSprites->addChild(npc);
	container->addChild(npc);

	NPCOperator* npc2 = new NPCOperator(container, allSprites);
	npc2->position.y += 500;
	allSprites->addChild(npc2);
	container->addChild(npc2);

	NPCExcavator* npc3 = new NPCExcavator(container, allSprites);
	allSprites->addChild(npc3);
	container->addChild(npc3);

	NPCCollector* npc4 = new NPCCollector(container, allSprites);
	npc4->position.x += 300;
	npc4->position.y += 500;
	allSprites->addChild(npc4);
	container->addChild(npc4);

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