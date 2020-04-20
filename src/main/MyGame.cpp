#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <algorithm>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1000, 1000)
{

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


	character = new AnimatedSprite("character");
	character->addSpriteSheet("./resources/grendel/Grendel_Idle_Sheet.png", "./resources/grendel/grendel_idle.xml", "idle", 3, 12, true);
	character->addSpriteSheet("./resources/grendel/Grendel_Move_Sheet.png", "./resources/grendel/grendel_move.xml", "move", 4, 12, true);
	//character->drawBox = true;
	container->addChild(character);
	character->play("idle");

	light = new Light("WHITE", "white");
	character->addChild(light);

	DOAdded->addChildCalled(character);


	npc = new AnimatedSprite("NPC");
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Backward_Sheet.png", "./resources/npcs/NPC_Sheets/npc_backward.xml", "back", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Forward_Sheet.png", "./resources/npcs/NPC_Sheets/npc_forward.xml", "front", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Left_Sheet.png", "./resources/npcs/NPC_Sheets/npc_left.xml", "left", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Right_Sheet.png", "./resources/npcs/NPC_Sheets/npc_right.xml", "right", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Backward_Sheet.png", "./resources/npcs/NPC_Sheets/npc_idle.xml", "idle_back", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Forward_Sheet.png", "./resources/npcs/NPC_Sheets/npc_idle.xml", "idle_front", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Left_Sheet.png", "./resources/npcs/NPC_Sheets/npc_idle.xml", "idle_left", 6, 12, true);
	npc->addSpriteSheet("./resources/npcs/NPC_Sheets/NPC_Right_Sheet.png", "./resources/npcs/NPC_Sheets/npc_idle.xml", "idle_right", 6, 12, true);
	container->addChild(npc);

	shadow = new Shadow("CIRCLE", "circle", 0);
	npc->addChild(shadow);
	shadow->position.y = 50;

	DOAdded->addChildCalled(npc);

}

MyGame::~MyGame(){

}

void MyGame::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	int origPosX = character->position.x;
	int origPosXNPC = npc->position.x;
	int origPosYNPC = npc->position.y;

	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		character->position.x += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		character->position.x -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		character->position.y += 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		character->position.y -= 1;
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		npc->position.x += 1;
		if(!npcWalking) {
			npc->play("right");
			npcWalking = true;
			lastMoved = 2;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		npc->position.x -= 1;
		if(!npcWalking) {
			npc->play("left");
			npcWalking = true;
			lastMoved = 4;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		npc->position.y += 1;
		if(!npcWalking) {
			npc->play("front");
			npcWalking = true;
			lastMoved = 3;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		npc->position.y -= 1;
		if(!npcWalking) {
			npc->play("back");
			npcWalking = true;
			lastMoved = 1;
		}
	}

	if(!(npc->position.x != origPosXNPC || npc->position.y != origPosYNPC)) {
		if(npcWalking) {
			npcWalking = false;
		}
		if(!npcWalking) {
			if(lastMoved == 1) {
				npc->play("idle_back");
			} else if(lastMoved == 2) {
				npc->play("idle_right");
			} else if(lastMoved == 3) {
				npc->play("idle_front");
			} else if(lastMoved == 4) {
				npc->play("idle_left");
			}
		}
	}


	if (character->position.x != origPosX){
		if (!charWalking){
			character->play("move");
			charWalking = true;
		}
	} else {
		if (charWalking){
			character->play("idle");
			charWalking = false;
		}
	}


	DORemoved->checkCondition();
	DOAdded->checkCondition();
	collisionSystem->update();

	Game::update(pressedKeys, currState);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);
}
