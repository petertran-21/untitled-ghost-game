#include "MyGame.h"

MyGame::MyGame() : Game(1000, 1000)
{
	//SFX team work
	camera = new Camera();
	scene_1 = new Scene();
	scene_1->loadScene("./resources/scenes/beachEntrance.json");
	camera->addChild(scene_1);
	this->addChild(camera);

	//Character demo work
	allSprites = new DisplayObjectContainer();
	container = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem(camera);
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
	p->position.y = 500;
	allSprites->addChild(p);
	container->addChild(p);

	Gem* g = new Gem(container);
	g->position.x = 900;
	g->position.y = 400;
	allSprites->addChild(g);
	container->addChild(g);

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

	Shrub* s1 = new Shrub(container);
	allSprites->addChild(s1);
	container->addChild(s1);
	s1->position.x = 100;

	Shrub* s2 = new Shrub(container);
	allSprites->addChild(s2);
	container->addChild(s2);
	s2->position.x = 200;

	Bridge *b = new Bridge(container);
	allSprites->addChild(b);
	container->addChild(b);
	b->position.x += 200;
	b->position.y += 200;

	Valve * v = new Valve(container, S);
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

	Log * c = new Log();
	allSprites->addChild(c);
	container->addChild(c);
	c->position.y += 600;
	c->position.x += 600;

	Log * c1 = new Log();
	allSprites->addChild(c1);
	container->addChild(c1);
	c1->position.y += 800;
	c1->position.x += 600;

	npc = new NPCPyromancer(container, allSprites);
	npc->position.x += 300;
	allSprites->addChild(npc);
	container->addChild(npc);

	NPCArcher* npc2 = new NPCArcher(container, allSprites);
	npc2->position.y += 500;
	allSprites->addChild(npc2);
	container->addChild(npc2);


	NPCLumberjack* npc4 = new NPCLumberjack(container, allSprites);
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
	// TODO, SFX will add later

	// selectionMenuTest = new SelectionMenu();
	// selectionMenuTest->addToMenu("Save");
	// selectionMenuTest->addToMenu("Load");
	// selectionMenuTest->addToMenu("Quit");
	// container->addChild(selectionMenuTest);

	// checklistTest = new Checklist();
	// checklistTest->addEntry("Change Scene");
	// container->addChild(checklistTest);
}

MyGame::~MyGame()
{
	/**
	 * Don't delete children of "this"
	 * because it's handled automatically through
	 * Game's superclass, DisplayObjectContainer.
	 */

	delete displayTreeDisp;
	delete collisionSystem;
	delete DOAdded;
	delete DORemoved;
}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	DORemoved->checkCondition();
	DOAdded->checkCondition();
	collisionSystem->update();
	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
