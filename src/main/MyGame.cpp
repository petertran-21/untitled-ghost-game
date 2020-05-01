#include "MyGame.h"

MyGame::MyGame() : Game(1000, 1000)
{
	//SFX team work
	camera = new Camera();
	scene_1 = new Scene();
	soundManager = new Sound();
	
	camera->addChild(scene_1);
	this->addChild(camera);

	//Character demo work
	allSprites = new DisplayObjectContainer();
	container = new DisplayObjectContainer();
	instance->addChild(allSprites);

	//uncomment following line to check that collision boxes for objects are identical to drawing
	//allSprites->addChild(container);

	collisionSystem = new CollisionSystem(camera, container, inventory);
	displayTreeDisp = new EventDispatcher();
	DOAdded = new DOAddedEvent(displayTreeDisp, container);
	DORemoved = new DORemovedEvent(displayTreeDisp, container);
	displayTreeDisp->addEventListener(collisionSystem, DOAddedEvent::DO_ADDED);
	displayTreeDisp->addEventListener(collisionSystem, DORemovedEvent::DO_REMOVED);
	

	scene_1->loadScene("./resources/Saves/Slot1/village.json", container, inventory);

	DOAdded->checkCondition();

	/**
	 * SFX MENU STUFF
	 */
	UIContainer = new DisplayObjectContainer();
	inventoryUI = new Inventory(100,100,300,300);
	selectionMenuTest = new SelectionMenu(20, 20, 250, 0);
	selectionMenuTest->addToMenu("Save");
	selectionMenuTest->addToMenu("Quit");
	textboxTest = new TextBox(150, 500, 800, 300);
	line1 = new Text("Press RETURN to select an option.");
	line2 = new Text("Press Q to resume game.");
	line1->width = line1->content.size() * 20;
	line2->width = line2->content.size() * 20;
	textboxTest->addChild(line1);
	textboxTest->children.back()->position.x += 50;
	textboxTest->children.back()->position.y += 50;
	textboxTest->addChild(line2);
	textboxTest->children.back()->position.x += 50;
	textboxTest->children.back()->position.y += 150;
	UIContainer->addChild(selectionMenuTest);
	UIContainer->addChild(textboxTest);

}

MyGame::~MyGame()
{
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
		if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end() && !InvOpen){
			this->addChild(inventoryUI);
			InvOpen = !InvOpen;
		}
		if (pressedKeys.find(SDL_SCANCODE_T) != pressedKeys.end() && InvOpen){
			this->children.erase(std::remove(this->children.begin(), this->children.end(), inventoryUI), this->children.end());
			InvOpen = !InvOpen;
		}
		
		Game::update(pressedKeys, currState);

		if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()){
			camera->getChild(0)->scaleX /= 1.1;
			camera->getChild(0)->scaleY /= 1.1;
		}
		if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()){
			camera->getChild(0)->scaleX *= 1.1;
			camera->getChild(0)->scaleY *= 1.1;
		}
	}
	//cout << "MyGame: Inventory: "<< inventory.size() << endl;
	// cout << "InventoryUI" << inventoryUI->entries.size() << endl;
	if(inventoryUI->entries.size()!=inventory.size()){
		inventoryUI->entries=inventory; 
	}

	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end() && UIOpen){
		selectionMenuTest->incrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() && UIOpen){
		selectionMenuTest->decrementPosition();
	}
	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end() && UIOpen){
		std::string result = selectionMenuTest->getCurrentlySelected();
		if (result == "Save"){
			for (auto child : camera->children){
				if (child->type == "Scene"){
					static_cast<Scene*>(child)->SaveScene();
					soundManager->playSFX("./resources/sfx/pauseOn.ogg");
					this->children.erase(std::remove(this->children.begin(), this->children.end(), UIContainer), this->children.end());
					UIOpen = false;
					break;
				}
			}
		}
		if (result == "Quit"){
			Game::quitGame = true;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end() && !UIOpen){
		this->addChild(UIContainer);
		UIOpen = !UIOpen;
	}
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && UIOpen){
		soundManager->playSFX("./resources/sfx/pauseOff.ogg");
		this->children.erase(std::remove(this->children.begin(), this->children.end(), UIContainer), this->children.end());
		UIOpen = false;
	}
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}