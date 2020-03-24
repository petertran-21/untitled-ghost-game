#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "EnemyCollisionEvent.h"

const string EnemyCollisionEvent::TAKE_DAMAGE = "TAKE_DAMAGE";

EnemyCollisionEvent::EnemyCollisionEvent() : Event() {
  this->character = NULL;
  this->enemy = NULL;
}

EnemyCollisionEvent::EnemyCollisionEvent(EventDispatcher* source, DisplayObject* character, DisplayObject* enemy) : Event(EnemyCollisionEvent::TAKE_DAMAGE, source) {
  this->character = character;
  this->enemy = item;
}

EnemyCollisionEvent::~EnemyCollisionEvent(){

}

void EnemyCollisionEvent::checkCondition(){
    int xDist = this->enemy->position.x - this->character->position.x;
    int yDist = this->enemy->position.y - this->character->position.y;


    if (xDist == 0 && yDist == 0){
        this->getSource()->dispatchEvent(this);
    }
}
