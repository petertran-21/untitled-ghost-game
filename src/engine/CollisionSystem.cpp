#include "CollisionSystem.h"
#include "DOAddedEvent.h"
#include "DORemovedEvent.h"

#include <cmath>

CollisionSystem::CollisionSystem(){

}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){
  watchForCollisions("NPC", "NPC");
  watchForCollisions("Ghost", "NPC");
  watchForCollisions("NPCObj", "EnvObj");
  watchForCollisions("NPC", "NPCObj");
  watchForCollisions("NPC", "EnvObj");
  watchForCollisions("NPC", "Collectible");
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){
  if (e->getType() == DOAddedEvent::DO_ADDED) {
    DOAddedEvent* event = (DOAddedEvent*) e;
    inView.push_back(event->recentlyAdded);
    // std::cout << "DO added to the game." << event->recentlyAdded->type << std::endl;
  }
  if (e->getType() == DORemovedEvent::DO_REMOVED) {
    DORemovedEvent* event = (DORemovedEvent*) e;
    for (int i = 0; i < inView.size(); i++) {
        if (inView[i] == event->recentlyRemoved) {
          delete inView[i];
          inView.erase(inView.begin() + i);
        }
    }
    std::cout << "DO removed from the game." << std::endl;
  }
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2){
  for(int i = 0; i < inView.size(); i++) {
    if (inView[i]->id == type1){
      for(int j = 0; j < inView.size(); j++) {
        //cout << j << endl;
        if (inView[j]->id == type2) {
          if(collidesWith(inView[i], inView[j])){
            // cout<< "TYPE 1: "<< type1 <<" ----- TYPE 2: "<<type2 <<endl;
            if (type1 == "Ghost" && type2 == "NPC"){
              resolveCollision_Ghost_NPC(inView[i], inView[j]);
            }
            else if ((type1 == "NPC" && type2 == "NPC") && (inView[i] != inView[j])){
              resolveCollision_NPC_NPC(inView[i], inView[j]);
            }
            else if ((type1 == "NPC" && type2 == "EnvObj")){
              resolveCollision_NPC_EnvObj(inView[i], inView[j]);
            }
            else if ((type1 == "NPC") && (type2 == "NPCObj")){
              resolveCollision_NPC_NPCObj(inView[i], inView[j]);
            }
            else if ((type1 == "NPC" && type2 == "Collectible")){
              resolveCollision_NPC_Collectible(inView[i], inView[j]);
            }
            else if ((type1 == "NPCObj" && type2 == "EnvObj")){
              resolveCollision_NPCObj_EnvObj(inView[i], inView[j]);
            }
            else{
              //nothing happens :)
            }

            // if (inView[i]) inView[i]->resolve_collision(inView[j]);
            // if (inView[j]) inView[j]->resolve_collision(inView[i]);

            } else {
              //Save deltas
              vector<SDL_Point> iHitbox = inView[i]->getHitbox();
              vector<SDL_Point> jHitbox = inView[j]->getHitbox();
              inView[i]->lastNonCollidedPos.x = iHitbox[0].x;
              inView[i]->lastNonCollidedPos.y = iHitbox[0].y;
              inView[j]->lastNonCollidedPos.x = jHitbox[0].x;
              inView[j]->lastNonCollidedPos.y = jHitbox[0].y;
            }
          }
        }
      }
    }
  }

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
  vector<SDL_Point> hitbox1 = obj1->getHitbox();
  vector<SDL_Point> hitbox2 = obj2->getHitbox();

  // std::cout << "obj1:" << std::endl;
	// std::cout << obj1->getHitbox()[0].x << ", " << obj1->getHitbox()[0].y << std::endl;
	// std::cout << obj1->getHitbox()[1].x << ", " << obj1->getHitbox()[1].y << std::endl;
	// std::cout << obj1->getHitbox()[2].x << ", " << obj1->getHitbox()[2].y << std::endl;
	// std::cout << obj1->getHitbox()[3].x << ", " << obj1->getHitbox()[3].y << std::endl;
  //
	// std::cout << "obj2:" << std::endl;
	// std::cout << obj2->getHitbox()[0].x << ", " << obj2->getHitbox()[0].y << std::endl;
	// std::cout << obj2->getHitbox()[1].x << ", " << obj2->getHitbox()[1].y << std::endl;
	// std::cout << obj2->getHitbox()[2].x << ", " << obj2->getHitbox()[2].y << std::endl;
	// std::cout << obj2->getHitbox()[3].x << ", " << obj2->getHitbox()[3].y << std::endl;

  //find min and max points in hitboxes
  int minX1 = 9999;
  int maxX1 = 0;
  for(int k = 0; k < 4; k++) {
    if(hitbox1.at(k).x < minX1) {
      minX1 = hitbox1.at(k).x;
    }
    if(hitbox1.at(k).x > maxX1) {
      maxX1 = hitbox1.at(k).x;
    }
  }
  int minY1 = 9999;
  int maxY1 = 0;
  for(int k = 0; k < 4; k++) {
    if(hitbox1.at(k).y < minY1) {
      minY1 = hitbox1.at(k).y;
    }
    if(hitbox1.at(k).y > maxY1) {
      maxY1 = hitbox1.at(k).y;
    }
  }
  int minX2 = 9999;
  int maxX2 = 0;
  for(int k = 0; k < 4; k++) {
    if(hitbox2.at(k).x < minX2) {
      minX2 = hitbox2.at(k).x;
    }
    if(hitbox2.at(k).x > maxX2) {
      maxX2 = hitbox2.at(k).x;
    }
  }
  int minY2 = 9999;
  int maxY2 = 0;
  for(int k = 0; k < 4; k++) {
    if(hitbox2.at(k).y < minY2) {
      minY2 = hitbox2.at(k).y;
    }

    if(hitbox2.at(k).y > maxY2) {
      maxY2 = hitbox2.at(k).y;
    }
  }

  // if the two hitboxes have overlapping x and y ranges, check for overlap
  if (((minX1 <= minX2 && minX2 <= maxX1) || // first on left, second on right
      (minX2 <= minX1 && minX1 <= maxX2)) &&
      ((minY1 <= minY2 && minY2 <= maxY1) ||
      (minY2 <= minY1 && minY1 <= maxY2))) {

    // for each edge for hitbox1 and each edge in hitbox2
    if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(1),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(0),hitbox1.at(1)) == 3) {
         // std::cout << "general collision1" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(1),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(0),hitbox1.at(1)) == 3) {
         // std::cout << "general collision2" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(3),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(0),hitbox1.at(1)) == 3) {
         // std::cout << "general collision3" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(3),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(0),hitbox1.at(1)) == 3) {
         // std::cout << "general collision4" << std::endl;
      return true;
    }
    //
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(1),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(1),hitbox1.at(2)) == 3) {
         // std::cout << "general collision5" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(1),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(1),hitbox1.at(2)) == 3) {
         // std::cout << "general collision6" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(3),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(1),hitbox1.at(2)) == 3) {
         // std::cout << "general collision7" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(3),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(1),hitbox1.at(2)) == 3) {
         // std::cout << "general collision8" << std::endl;
      return true;
    }
    //
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(1),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(2),hitbox1.at(3)) == 3) {
         // std::cout << "general collision9" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(1),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(2),hitbox1.at(3)) == 3) {
         // std::cout << "general collision10" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(3),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(2),hitbox1.at(3)) == 3) {
         // std::cout << "general collision11" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(3),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(2),hitbox1.at(3)) == 3) {
         // std::cout << "general collision12" << std::endl;
      return true;
    }
    //
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(1),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(3),hitbox1.at(0)) == 3) {
         // std::cout << "general collision13" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(1),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(3),hitbox1.at(0)) == 3) {
         // std::cout << "general collision14" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(3),hitbox2.at(2)) == 3 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(3),hitbox1.at(0)) == 3) {
         // std::cout << "general collision15" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(3),hitbox2.at(0)) == 3 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(3),hitbox1.at(0)) == 3) {
         // std::cout << "general collision16" << std::endl;
      return true;
    }

    // 0 - colinear lines: special case is met
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(0),hitbox2.at(1)) == 0 &&
            calculateOrientation(hitbox2.at(0),hitbox1.at(1),hitbox1.at(0),hitbox2.at(1)) == 0) {
      // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(1),hitbox2.at(2)) == 0 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(0),hitbox1.at(1)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(2),hitbox2.at(3)) == 0 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(0),hitbox1.at(1)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(0),hitbox1.at(1),hitbox2.at(3),hitbox2.at(0)) == 0 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(0),hitbox1.at(1)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    //
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(0),hitbox2.at(1)) == 0 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(1),hitbox1.at(2)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(1),hitbox2.at(2)) == 0 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(1),hitbox1.at(2)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(2),hitbox2.at(3)) == 0 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(1),hitbox1.at(2)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(1),hitbox1.at(2),hitbox2.at(3),hitbox2.at(0)) == 0 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(1),hitbox1.at(2)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    //
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(0),hitbox2.at(1)) == 0 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(2),hitbox1.at(3)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(1),hitbox2.at(2)) == 0 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(2),hitbox1.at(3)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(2),hitbox2.at(3)) == 0 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(2),hitbox1.at(3)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(2),hitbox1.at(3),hitbox2.at(3),hitbox2.at(0)) == 0 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(2),hitbox1.at(3)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    //
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(0),hitbox2.at(1)) == 0 &&
       calculateOrientation(hitbox2.at(0),hitbox2.at(1),hitbox1.at(3),hitbox1.at(0)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(1),hitbox2.at(2)) == 0 &&
       calculateOrientation(hitbox2.at(1),hitbox2.at(2),hitbox1.at(3),hitbox1.at(0)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(2),hitbox2.at(3)) == 0 &&
       calculateOrientation(hitbox2.at(2),hitbox2.at(3),hitbox1.at(3),hitbox1.at(0)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }
    else if(calculateOrientation(hitbox1.at(3),hitbox1.at(0),hitbox2.at(3),hitbox2.at(0)) == 0 &&
       calculateOrientation(hitbox2.at(3),hitbox2.at(0),hitbox1.at(3),hitbox1.at(0)) == 0) {
         // std::cout << "colinear collision" << std::endl;
      return true;
    }

    // check if a corner of hb1 is in hb2
    if (isLocatedInRect(hitbox1.at(0), hitbox2) ||
        isLocatedInRect(hitbox1.at(1), hitbox2) ||
        isLocatedInRect(hitbox1.at(2), hitbox2) ||
        isLocatedInRect(hitbox1.at(3), hitbox2)) {
      // std::cout << "corner of hb1 in hb2" << std::endl;
      return true;
    }
    // check if a corner of hb2 is in hb1
    if (isLocatedInRect(hitbox2.at(0), hitbox1) ||
        isLocatedInRect(hitbox2.at(1), hitbox1) ||
        isLocatedInRect(hitbox2.at(2), hitbox1) ||
        isLocatedInRect(hitbox2.at(3), hitbox1)) {
      // std::cout << "corner of hb2 in hb1" << std::endl;
      return true;
    }

  }

  return false;
}

// float CollisionSystem::slope(SDL_Point p1, SDL_Point p2) {
//   float slope = 0.0;
//   if (p2.x - p1.x != 0){
//     slope = float(p2.y - p1.y) / float(p2.x - p1.x);
//   }
//   if (slope == -0) {
//     slope = 0.0;
//   }
//   return slope;
// }

int CollisionSystem::calculateOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4) {
  // first point test
  int firstTurn = 0;
  int secondTurn = 0;
  int val1 = (p2.y - p1.y) * (p3.x - p2.x) -
              (p2.x - p1.x) * (p3.y - p2.y);
  int val2 = (p2.y - p1.y) * (p4.x - p2.x) -
              (p2.x - p1.x) * (p4.y - p2.y);
  // std::cout << "---" << std::endl;
  // std::cout << "val1" << val1 << std::endl;
  // std::cout << "val2" << val2 << std::endl;
  if (val1 > 0) {
    // left turn detected, set to 1
    firstTurn = 1;
  } else if (val1 < 0) {
    // right turn detected, set to 2
    firstTurn = 2;
  }

  // second point test
  if (val2 > 0) {
    // left turn detected, set to 1
    secondTurn = 1;
  } else if (val2 < 0) {
    // right turn detected, set to 2
    secondTurn = 2;
  }

  // 0 - colinear; 2 - two left turns; 4 - two right turns; 3 - intersection;
  return firstTurn + secondTurn;
}

bool CollisionSystem::isLocatedInRect(SDL_Point hb1_point, vector<SDL_Point> hb2) {
  // area = 1/2[x1(y2-y3) + x2(y3-y1) + x3(y1-y2)]
  float rectArea = float(distance(hb2.at(0), hb2.at(1)) * distance(hb2.at(1), hb2.at(2)));
  float area1 = calculateArea(distance(hb1_point,hb2.at(0)), distance(hb1_point,hb2.at(1)), distance(hb2.at(0),hb2.at(1)));
  float area2 = calculateArea(distance(hb1_point,hb2.at(1)), distance(hb1_point,hb2.at(2)), distance(hb2.at(1),hb2.at(2)));
  float area3 = calculateArea(distance(hb1_point,hb2.at(2)), distance(hb1_point,hb2.at(3)), distance(hb2.at(2),hb2.at(3)));
  float area4 = calculateArea(distance(hb1_point,hb2.at(3)), distance(hb1_point,hb2.at(0)), distance(hb2.at(3),hb2.at(0)));
  if (area1 + area2 + area3 + area4 == rectArea) {
    return true;
  }
  return false;
}

float CollisionSystem::calculateArea(float a, float b, float c) {
  float p = (a+b+c)/2;
  float ans = sqrt(p*(p-a)*(p-b)*(p-c));
  return ans;
}

double CollisionSystem::distance(SDL_Point p1, SDL_Point p2) {
	return sqrt(((p2.y - p1.y)*(p2.y - p1.y)) + ((p2.x - p1.x)*(p2.x - p1.x)));
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
  //std::cout << "Collision" << std::endl;
  //d->position = d->lastNonCollidedPos;
  //other->position = other->lastNonCollidedPos;

  // For now just do 5 iterations to get closer -- Should this be recursive? ¯\_(ツ)_/¯
  int i = 0;
  bool lastIterartionCollided = true;
  while(i < 5){

    if (collidesWith(d, other)){
      // Move further away
      if (!lastIterartionCollided){
        xDelta1 = -xDelta1;
        yDelta1 = - yDelta1;

        xDelta2 = -xDelta2;
        yDelta2 = -yDelta2;
      }
      lastIterartionCollided = true;
    } else {
      // Move closer
      if (lastIterartionCollided){
        xDelta1 = -xDelta1;
        yDelta1 = - yDelta1;

        xDelta2 = -xDelta2;
        yDelta2 = -yDelta2;
      }
      lastIterartionCollided = false;
    }

    // Find midpoints
    d->position.x = d->position.x - 100;
    d->position.y = d->position.y - 100;
    // d->position.x = (d->position.x + (d->position.x - xDelta1))/2;
    // d->position.y = (d->position.y + (d->position.y - yDelta1))/2;

    other->position.x = (other->position.x + (other->position.x - xDelta2))/2;
    other->position.y = (other->position.y + (other->position.y - yDelta2))/2;
    //cout << other->position.x << endl;
    // Shorten move distance
    xDelta1 = xDelta1/2;
    yDelta1 = yDelta1/2;

    xDelta2 = xDelta2/2;
    yDelta2 = yDelta2/2;
    i++;
  }



}

void CollisionSystem::resolveCollision_Ghost_NPC(DisplayObject* ghost, DisplayObject* npc) {
  Ghost* g = dynamic_cast<Ghost*>(ghost);

  g->npc = (MainNPC*)npc;
}

void CollisionSystem::resolveCollision_NPC_NPC(DisplayObject* npc, DisplayObject* npc1){
  MainNPC* npc2 = (MainNPC*) npc;
  MainNPC* npc3 = (MainNPC*) npc1;
  MainNPC* pNPC = npc3;
  MainNPC* npNPC = npc2;
  //check which npc is possessed
  if (npc2->is_possessed){
    pNPC = npc2;
    npNPC = npc3;
  }
  //check that npcs are overlapping
  if ((pNPC->position.y == npNPC->position.y) && (pNPC->position.x == npNPC->position.x)){
    switch (pNPC->dir){
      //reset possessed npc's location to previous based on location it came from
      case N:
        pNPC->position.y = pNPC->position.y + 100;
        pNPC->dir = None;
        break;
      case E:
        pNPC->position.x = pNPC->position.x - 100;
        pNPC->dir = None;
        break;
      case S: 
        pNPC->position.y = pNPC->position.y - 100;
        pNPC->dir = None;
        break;
      case W:
        pNPC->position.x = pNPC->position.x + 100;
        pNPC->dir = None;
        break;
    }
  }

}

void CollisionSystem::resolveCollision_NPC_EnvObj(DisplayObject* npc, DisplayObject* envObj){
  npc->resolve_collision(envObj);
  envObj->resolve_collision(npc);
}
void CollisionSystem::resolveCollision_NPC_NPCObj(DisplayObject* npc, DisplayObject* npcObj){
  npc->resolve_collision(npcObj);
  npcObj->resolve_collision(npc);
}

void CollisionSystem::resolveCollision_NPC_Collectible(DisplayObject* npc, DisplayObject* collectible){
  npc->resolve_collision(collectible);
  collectible->resolve_collision(npc);
}

void CollisionSystem::resolveCollision_NPCObj_EnvObj(DisplayObject* NPCObj, DisplayObject* envObj){
  NPCObj->resolve_collision(envObj);
  envObj->resolve_collision(NPCObj);
}