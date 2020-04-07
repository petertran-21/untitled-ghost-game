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
  watchForCollisions("character", "crocodile");
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
        if (inView[j]->id == type2) {
          if(collidesWith(inView[i], inView[j])){
            resolveCollision(inView[i], inView[j],
            inView[i]->position.x - inView[i]->lastNonCollidedPos.x + inView[i]->parent->position.x,
            inView[i]->position.y - inView[i]->lastNonCollidedPos.y + inView[i]->parent->position.y,
            inView[j]->position.x - inView[j]->lastNonCollidedPos.x + inView[j]->parent->position.x,
            inView[j]->position.y - inView[j]->lastNonCollidedPos.y + inView[j]->parent->position.y);
            } else {
              //Save deltas
              vector<SDL_Point> iHitbox = inView[i]->getHitbox();
              vector<SDL_Point> jHitbox = inView[j]->getHitbox();
              inView[i]->lastNonCollidedPos.x = iHitbox[0].x;
              inView[i]->lastNonCollidedPos.y = iHitbox[0].y;
              inView[i]->lastNonCollidedHB = iHitbox;
              inView[j]->lastNonCollidedPos.x = jHitbox[0].x;
              inView[j]->lastNonCollidedPos.y = jHitbox[0].y;
              inView[j]->lastNonCollidedHB = jHitbox;
            }
          }
        }
      }
    }
  }

void CollisionSystem::watchForAdjacency(string type1, string type2) {
  for(int i = 0; i < inView.size(); i++) {
    if (inView[i]->id == type1){
      for(int j = 0; j < inView.size(); j++) {
        if (inView[j]->id == type2) {
          std::cout << isAdjacentTo(inView[i], inView[j]) << std::endl;
          // resolve adjacency goes here;
        }
      }
    }
  }
}

vector<int> CollisionSystem::findXYProjections(vector<SDL_Point> hitbox) {
  //find min and max points in hitboxes
  vector<int> projections;

  int minX = 9999;
  int maxX = 0;
  for(int k = 0; k < 4; k++) {
    if(hitbox.at(k).x < minX) {
      minX = hitbox.at(k).x;
    }
    if(hitbox.at(k).x > maxX) {
      maxX = hitbox.at(k).x;
    }
  }
  projections.push_back(minX);
  projections.push_back(maxX);
  int minY = 9999;
  int maxY = 0;
  for(int k = 0; k < 4; k++) {
    if(hitbox.at(k).y < minY) {
      minY = hitbox.at(k).y;
    }
    if(hitbox.at(k).y > maxY) {
      maxY = hitbox.at(k).y;
    }
  }
  projections.push_back(minY);
  projections.push_back(maxY);

  return projections;
}


int CollisionSystem::projectionsOverlap(vector<int> projections1, vector<int> projections2) {

  int minX1 = projections1[0];
  int maxX1 = projections1[1];
  int minY1 = projections1[2];
  int maxY1 = projections1[3];

  int minX2 = projections2[0];
  int maxX2 = projections2[1];
  int minY2 = projections2[2];
  int maxY2 = projections2[3];

  if (((minX1 <= minX2 && minX2 <= maxX1) ||
      (minX2 <= minX1 && minX1 <= maxX2)) &&
      ((minY1 <= minY2 && minY2 <= maxY1) ||
      (minY2 <= minY1 && minY1 <= maxY2))) {
        return 3;
  } else if(((minX1 <= minX2 && minX2 <= maxX1) ||
      (minX2 <= minX1 && minX1 <= maxX2))) {
        return 2;
  } else if(((minY1 <= minY2 && minY2 <= maxY1) ||
  (minY2 <= minY1 && minY1 <= maxY2))) {
        return 1;
  } else return 0;
}

// returns 1 - obj1 is directly right of obj2;
// returns 2 - obj1 is directly left of obj2;
// returns 3 - obj1 is directly above obj2;
// returns 4 - obj1 is directly below obj2;
// returns 0 - not adjacent
int CollisionSystem::isAdjacentTo(DisplayObject* obj1, DisplayObject* obj2) {
  int xDif = obj1->position.x - obj2->position.x;
  int yDif = obj1->position.y - obj2->position.y;

  if(xDif > 0 && xDif < 101 && yDif == 0) {
    return 1;
  }
  else if(xDif < 0 && xDif > -101 && yDif == 0) {
    return 2;
  }
  else if(xDif == 0 && yDif < 0 && yDif > -101) {
    return 3;
  }
  else if(xDif == 0 && yDif > 0 && yDif < 101) {
    return 4;
  }
  return 0;
}
//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
  vector<SDL_Point> hitbox1 = obj1->getHitbox();
  vector<SDL_Point> hitbox2 = obj2->getHitbox();

  // if the two hitboxes have overlapping x and y ranges, check for overlap
  if (projectionsOverlap(findXYProjections(hitbox1),findXYProjections(hitbox2)) == 3) {

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


int CollisionSystem::calculateOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4) {
  // first point test
  int firstTurn = 0;
  int secondTurn = 0;
  int val1 = (p2.y - p1.y) * (p3.x - p2.x) -
              (p2.x - p1.x) * (p3.y - p2.y);
  int val2 = (p2.y - p1.y) * (p4.x - p2.x) -
              (p2.x - p1.x) * (p4.y - p2.y);

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

  // if collision caused by Y value
  if (projectionsOverlap(findXYProjections(d->lastNonCollidedHB),findXYProjections(other->lastNonCollidedHB)) == 2) {
    d->position.y = d->position.y - yDelta1;
    other->position.y = other->position.y - yDelta2;
  }

  // if collision caused by X value
  else if (projectionsOverlap(findXYProjections(d->lastNonCollidedHB),findXYProjections(other->lastNonCollidedHB)) == 1) {
    d->position.x = d->position.x - xDelta1;
    other->position.x = other->position.x - xDelta2;
  }

  // if collision on corner value
  else if (projectionsOverlap(findXYProjections(d->lastNonCollidedHB),findXYProjections(other->lastNonCollidedHB)) == 0) {
    d->position.y = d->position.y - yDelta1;
    other->position.y = other->position.y - yDelta2;
    d->position.x = d->position.x - xDelta1;
    other->position.x = other->position.x - xDelta2;
  }

  // if collision on rotated sprites
  else if (projectionsOverlap(findXYProjections(d->lastNonCollidedHB),findXYProjections(other->lastNonCollidedHB)) == 3) {

    // movement left/right ONLY
    if(yDelta1 == 0 && yDelta2 == 0) {
      d->position.y = d->position.y - xDelta1;
      other->position.y = other->position.y - xDelta2;
      d->createHitbox();
      other->createHitbox();
      if(collidesWith(d,other)) {
        d->position.y = d->position.y + 2*xDelta1;
        other->position.y = other->position.y + 2*xDelta2;
        while(collidesWith(d,other)) {
          d->position.y = d->position.y + xDelta1;
          other->position.y = other->position.y + xDelta2;
          d->createHitbox();
          other->createHitbox();
        }
      }
    }
    // movement up/down ONLY
    else if(xDelta1 == 0 && xDelta2 == 0) {
      d->position.x = d->position.x + yDelta1;
      other->position.x = other->position.x + yDelta2;
      d->createHitbox();
      other->createHitbox();
      if(collidesWith(d,other)) {
        d->position.x = d->position.x - 2*yDelta1;
        other->position.x = other->position.x - 2*yDelta2;
        while(collidesWith(d,other)) {
          d->position.x = d->position.x - yDelta1;
          other->position.x = other->position.x - yDelta2;
          d->createHitbox();
          other->createHitbox();
        }
      }
    }
    // movement in two directions
    else {
      int iter1 = 0;
      int iter2 = 0;
      int origD = d->position.x;
      int origO = other->position.x;
      while(collidesWith(d,other)) {
        d->position.x = d->position.x + xDelta1;
        other->position.x = other->position.x + xDelta2;
        d->createHitbox();
        other->createHitbox();
        iter1++;
      }
      d->position.x = origD;
      other->position.x = origO;
      d->createHitbox();
      other->createHitbox();
      while(collidesWith(d,other)) {
        d->position.x = d->position.x - xDelta1;
        other->position.x = other->position.x - xDelta2;
        d->createHitbox();
        other->createHitbox();
        iter2++;
      }
      d->position.x = origD;
      other->position.x = origO;
      d->createHitbox();
      other->createHitbox();

      // collision is to the right of the sprite
      if(iter1 > iter2) {
        // keep y, reset x
        while(collidesWith(d,other)) {
          d->position.x = d->position.x - xDelta1;
          other->position.x = other->position.x - xDelta2;
          d->createHitbox();
          other->createHitbox();
        }
      } else { // collision is to the left
        // keep x, reset y
        while(collidesWith(d,other)) {
          d->position.y = d->position.y - yDelta1;
          other->position.y = other->position.y - yDelta2;
          d->createHitbox();
          other->createHitbox();
        }
      }
    }
  }
}
