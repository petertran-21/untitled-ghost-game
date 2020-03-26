#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(){
  this->type = "CollisionSystem";
}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){
  watchForCollisions("player", "platform");
  // watchForCollisions("player", "enemy");
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){

}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){
  DisplayObject* first = this->getChild(type1);
  DisplayObject* second = this->getChild(type2);

  // if (collidesWith(first, second)) {
  //    resolveCollision(first, second, firstDistanceMovedX, firstDistanceMovedY, secondDistanceMovedX, secondDistanceMovedY);
  // }
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
  // obj1->getGlobalHitbox();
  // obj2->getGlobalHitbox();
  // if(obj1->hitbox.x < obj2->hitbox.x + obj2->hitbox.width &&
  //  obj2->hitbox.x < obj1->hitbox.x + obj1->hitbox.width &&
  //  obj1->hitbox.y + obj1->hitbox.height > obj2->hitbox.y &&
  //  obj2->hitbox.y + obj2->hitbox.height > obj1->hitbox.y) {
  //        return true;
    return false;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2){

}
