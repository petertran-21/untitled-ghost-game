#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "Event.h"
#include "DisplayObjectContainer.h"
#include "EventListener.h"
#include "Camera.h"
#include "SceneTrigger.h"

#include <iostream>

using namespace std;

class CollisionSystem : public EventListener{

public:

	CollisionSystem();
	CollisionSystem(Camera *maincam, DisplayObjectContainer *collisionContainer);
	~CollisionSystem();

	Camera *maincam;

	//checks collisions between pairs of DOs where the corresponding types have been requested
	//to be checked (via a single call to watchForCollisions) below.
	void update();

	//This system watches the game's display tree and is notified whenever a display object is placed onto
	//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
	void handleEvent(Event* e);

	//This function asks the collision system to start checking for collisions between all pairs
	//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
	//against all platform objects that are in the current scene.
	void watchForCollisions(string type1, string type2);
	void watchForAdjacency(string type1, string type2);

	vector<int> findXYProjections(vector<SDL_Point> hitbox);

	int projectionsOverlap(vector<int> projections1, vector<int> projections2);


	int isAdjacentTo(DisplayObject* obj1, DisplayObject* obj2);
	//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
	//	SDL_Point* DisplayObject::getGlobalHitbox();
	bool collidesWith(DisplayObject* obj1, DisplayObject* obj2);
	// float slope(SDL_Point p1, SDL_Point p2);
	float calculateArea(float a, float b, float c);
	double distance(SDL_Point p1, SDL_Point p2);
	int calculateOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4);
	bool isLocatedInRect(SDL_Point hb1_point, vector<SDL_Point> hb2);

	//Resolves the collision that occurred between d and other
	//xDelta1 and yDelta1 are the amount d moved before causing the collision.
	//xDelta2 and yDelta2 are the amount other moved before causing the collision.
	void resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2);
	void resolveCollision_Ghost_NPC(DisplayObject* ghost, DisplayObject* npc);
	void resolveCollision_NPC_NPC(DisplayObject* npc, DisplayObject* npc1);
	void resolveCollision_NPC_EnvObj(DisplayObject* npc, DisplayObject* envObj);
	void resolveCollision_NPC_NPCObj(DisplayObject* npc, DisplayObject* npcObj);
	void resolveCollision_NPC_Collectible(DisplayObject* npc, DisplayObject* collectible);
	void resolveCollision_NPCObj_EnvObj(DisplayObject* NPCObj, DisplayObject* envObj);
	void resolveCollision_SceneTrigger(DisplayObject* triggerObj, DisplayObject* ghostObj);
	void resolveCollision_Boss_NPCObj(DisplayObject* bossObj, DisplayObject* npcObj);
	void resolveCollision_NPC_Wall(DisplayObject* npc, DisplayObject* wall);

	void resolveAdjacency_NPC_EnvObj(DisplayObject* npc, DisplayObject* envObj, int status);
	void resolveAdjacency_NPC_NPCObj(DisplayObject* npc, DisplayObject* npcObj, int status);
	void resolveAdjacency_NPCObj_EnvObj(DisplayObject* NPCObj, DisplayObject* envObj, int status);
	void resolveAdjacency_EnvObj_EnvObj(DisplayObject* envObj1, DisplayObject* envObj2, int status);

private:
	vector<DisplayObject*> inView;
	DisplayObjectContainer* collisionContainer;

};

#endif
