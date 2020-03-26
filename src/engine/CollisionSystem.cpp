#include "CollisionSystem.h"
#include "DOAddedEvent.h"
#include "DORemovedEvent.h"

CollisionSystem::CollisionSystem(){

}

CollisionSystem::~CollisionSystem(){

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update(){
  // watchForCollisions("player", "wall");
  // watchForCollisions("player", "enemy");
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e){
  if (e->getType() == DOAddedEvent::DO_ADDED) {
    DOAddedEvent* event = (DOAddedEvent*) e;
    inView.push_back(event->recentlyAdded);
    std::cout << "DO added to the game." << std::endl;
  }
  if (e->getType() == DORemovedEvent::DO_REMOVED) {
    DORemovedEvent* event = (DORemovedEvent*) e;
    for (int i = 0; i < inView.size(); i++) {
        if (inView[i] == event->recentlyRemoved) {
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

}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
  vector<SDL_Point> hitbox1 = obj1->getHitbox();
  vector<SDL_Point> hitbox2 = obj2->getHitbox();

  //find min and max points in hitboxes
  int min1 = 0;
  int max1 = 0;
  for(int k = 1; k < 4; k++) {
    if(hitbox1.at(k-1).x < hitbox1.at(k).x) {
      min1 = hitbox1.at(k-1).x;
    } else {
      min1 = hitbox1.at(k).x;
    }

    if(hitbox1.at(k-1).x > hitbox1.at(k).x) {
      max1 = hitbox1.at(k-1).x;
    } else {
      max1 = hitbox1.at(k).x;
    }
  }

  int min2 = 0;
  int max2 = 0;
  for(int k = 1; k < 4; k++) {
    if(hitbox2.at(k-1).x < hitbox2.at(k).x) {
      min2 = hitbox2.at(k-1).x;
    } else {
      min2 = hitbox2.at(k).x;
    }

    if(hitbox2.at(k-1).x > hitbox2.at(k).x) {
      max2 = hitbox2.at(k-1).x;
    } else {
      max2 = hitbox2.at(k).x;
    }
  }

  // if the two hitboxes have overlapping x ranges, check for overlap
  if ((min1 <= min2 && min2 <= max1) || // first on left, second on right
      (min2 <= min1 && min1 <= max2)) { // first on right, second on left
    // for each edge for hitbox1 and each edge in hitbox2
    for(int i = 1; i < 4; i++) {
      for(int j = 1; j < 4; j++) {
        // 3 - intersection: general rule is met
        if(calculateOrientation(hitbox1.at(i-1),hitbox1.at(i),hitbox2.at(j-1),hitbox2.at(j)) == 3 &&
           calculateOrientation(hitbox2.at(i-1),hitbox2.at(i),hitbox1.at(j-1),hitbox1.at(j)) == 3) {
          return true;
        }
        // 0 - colinear lines: special case is met
        else if(calculateOrientation(hitbox1.at(i-1),hitbox1.at(i),hitbox2.at(j-1),hitbox2.at(j)) == 0) {
          return true;
        }
      }
    }
    // check if a corner of hb1 is in hb2
    if (isLocatedInRect(hitbox1.at(0), hitbox2) ||
        isLocatedInRect(hitbox1.at(1), hitbox2) ||
        isLocatedInRect(hitbox1.at(2), hitbox2) ||
        isLocatedInRect(hitbox1.at(3), hitbox2)) {
      return true;
    }
    // check if a corner of hb2 is in hb1
    if (isLocatedInRect(hitbox2.at(0), hitbox1) ||
        isLocatedInRect(hitbox2.at(1), hitbox1) ||
        isLocatedInRect(hitbox2.at(2), hitbox1) ||
        isLocatedInRect(hitbox2.at(3), hitbox1)) {
      return true;
    }

  }

  return false;
}

float CollisionSystem::slope(SDL_Point p1, SDL_Point p2) {
  float slope = (p2.y - p1.y) / (p2.x - p1.x);
  return slope;
}

int CollisionSystem::calculateOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4) {
  // first point test
  int firstTurn = 0;
  if (slope(p1,p2) < slope(p2,p3)) {
    // left turn detected, set to 1
    firstTurn = 1;
  } else if (slope(p2,p3) < slope(p1,p2)) {
    // right turn detected, set to 2
    firstTurn = 2;
  }

  // second point test
  int secondTurn = 0;
  if (slope(p1,p2) < slope(p2,p4)) {
    // left turn detected, set to 1
    secondTurn = 1;
  } else if (slope(p2,p4) < slope(p1,p2)) {
    // right turn detected, set to 2
    secondTurn = 2;
  }

  // 0 - colinear; 2 - two left turns; 4 - two right turns; 3 - intersection;
  return firstTurn + secondTurn;
}

bool CollisionSystem::isLocatedInRect(SDL_Point hb1_point, vector<SDL_Point> hb2) {
  // area = 1/2[x1(y2-y3) + x2(y3-y1) + x3(y1-y2)]
  float rectArea = distance(hb2.at(0), hb2.at(1)) * distance(hb2.at(1), hb2.at(2));
  float area1 = 1/2 * (hb1_point.x * (hb2.at(0).y - hb2.at(1).y) + hb1_point.x * (hb2.at(1).y - hb1_point.y) + hb1_point.x * (hb1_point.y - hb2.at(0).y));
  float area2 = 1/2 * (hb1_point.x * (hb2.at(1).y - hb2.at(2).y) + hb1_point.x * (hb2.at(2).y - hb1_point.y) + hb1_point.x * (hb1_point.y - hb2.at(1).y));
  float area3 = 1/2 * (hb1_point.x * (hb2.at(2).y - hb2.at(3).y) + hb1_point.x * (hb2.at(3).y - hb1_point.y) + hb1_point.x * (hb1_point.y - hb2.at(2).y));
  float area4 = 1/2 * (hb1_point.x * (hb2.at(3).y - hb2.at(0).y) + hb1_point.x * (hb2.at(0).y - hb1_point.y) + hb1_point.x * (hb1_point.y - hb2.at(3).y));
  if (area1 + area2 + area3 + area4 == rectArea) {
    return true;
  }
  return false;
}

double CollisionSystem::distance(SDL_Point p1, SDL_Point p2) {
	return sqrt(((p2.y - p1.y)*(p2.y - p1.y)) + ((p2.x - p1.x)*(p2.x - p1.x)));
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
  std::cout << "Collision" << std::endl;
}
