#include "MyGame.h"

MyGame::MyGame() : Game(1000, 1000)
{
	//SFX team work
	camera = new Camera();
	scene_1 = new Scene();
	
	camera->addChild(scene_1);
	this->addChild(camera);

	//Character demo work
	allSprites = new DisplayObjectContainer();
	container = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem(camera, container);
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);

	scene_1->loadScene("./resources/scenes/beachRoom5.json", container);

	//---------------SCENE TRIGGER-------------------------
	// SceneTrigger* beachTrigger = new SceneTrigger(container);
	// beachTrigger->position.x = 200;
	// beachTrigger->position.y = 900;
	// cout<<"scene trigger location: "<<beachTrigger->position.x << " "<<beachTrigger->position.y<<endl;
	// container->addChild(beachTrigger);

	//-----------------------------------------------------

	// Shrub* s = new Shrub(container);
	// allSprites->addChild(s);
	// container->addChild(s);


	// Gem* g = new Gem(container);
	// g->position.x = 900;
	// g->position.y = 400;
	// allSprites->addChild(g);
	// container->addChild(g);

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


	// BreakableWall *b = new BreakableWall(container);
	// allSprites->addChild(b);
	// container->addChild(b);
	// b->position.x += 200;
	// b->position.y += 200;

	// Crab * c = new Crab();
	// allSprites->addChild(c);
	// container->addChild(c);
	// c->position.y += 600;
	// c->position.x += 600;

	// npc = new NPCPyromancer(container, allSprites);
	// npc->position.x += 300;
	// allSprites->addChild(npc);
	// container->addChild(npc);

	// NPCOperator* npc2 = new NPCOperator(container, scene_1);
	// npc2->position.y += 500;
	// scene_1->addChild(npc2);
	// container->addChild(npc2);

	// NPCExcavator* npc3 = new NPCExcavator(container, allSprites);
	// allSprites->addChild(npc3);
	// container->addChild(npc3);

	// NPCCollector* npc4 = new NPCCollector(container, allSprites);
	// npc4->position.x += 300;
	// npc4->position.y += 500;
	// allSprites->addChild(npc4);
	// container->addChild(npc4);

	// // player = new Ghost();
	// // player->addChild( new ParticleEmitter() );
	// // container->addChild(player);
	// // scene_1->addChild(player);
	//DOAdded->addChildCalled(container);
	DOAdded->checkCondition();
	//-----------------------------------------
	// TODO, SFX will add later

	UIContainer = new DisplayObjectContainer();

	selectionMenuTest = new SelectionMenu(0, 0);
	selectionMenuTest->addToMenu("Save");
	selectionMenuTest->addToMenu("Load");
	selectionMenuTest->addToMenu("Quit");

	textboxTest = new TextBox(0, 400);
	UIContainer->addChild(selectionMenuTest);
	UIContainer->addChild(textboxTest);
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
	if (!UIOpen){
		DORemoved->checkCondition();
		DOAdded->checkCondition();
		collisionSystem->update();
		Game::update(pressedKeys, currState);

		if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()){
			camera->getChild(0)->scaleX /= 1.1;
			camera->getChild(0)->scaleY /= 1.1;
		}
		if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
			camera->getChild(0)->scaleX *= 1.1;
			camera->getChild(0)->scaleY *= 1.1;
		}
		if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()){
			camera->getChild(0)->position.x += 10;
		}
		if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()){
			camera->getChild(0)->position.x -= 10;
		}
		if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()){
			camera->getChild(0)->position.y += 10;
		}
		if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()){
			camera->getChild(0)->position.y -= 10;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end() && UIOpen){
		selectionMenuTest->incrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() && UIOpen){
		selectionMenuTest->decrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end() && UIOpen){
		std::cout << selectionMenuTest->getCurrentlySelected() << std::endl;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !UIOpen){
		this->addChild(UIContainer);
		textboxTest->setText("X-pos: " + std::to_string(player->position.x));
		UIOpen = !UIOpen;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && UIOpen){
		this->children.erase(std::remove(this->children.begin(), this->children.end(), UIContainer), this->children.end());
		UIOpen = false;
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}