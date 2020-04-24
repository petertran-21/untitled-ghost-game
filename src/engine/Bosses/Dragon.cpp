#include <iostream>
#include <cstdlib>
#include "Dragon.h"

using namespace std;

Dragon::Dragon(DisplayObjectContainer *container, DisplayObjectContainer* drawContainer) : MainBoss(){
	this->addAnimation("./resources/bosses/", "dragon_idle", 1, 1, false);
	this->play("dragon_idle");
    this->collisionContainer = container;
    this->drawingContainer = drawContainer;
    this->subtype = DRAGON_SUBTYPE;
}

void Dragon::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainBoss::update(pressedKeys, currState);

    if (active){
        if (init){
            for (int i=0; i < tile_range; i++){
                FireStream* s = new FireStream(dir, this->collisionContainer);
                s->position.x = position.x;
                s->position.y = position.y;

                int dist = 100*(i+1);
                switch (dir){
                    case N: s->position.y = position.y-dist; break;
                    case S: s->position.y = position.y+dist; break;
                    case E: s->position.x = position.x+dist; break;
                    case W: s->position.x = position.x-dist; break;
                }

                streams.push_back(s);
                this->collisionContainer->addChild(s);
                this->drawingContainer->addChild(s);
                cout<<"STREAMS SIZE: "<<streams.size()<<endl;
                cout<<"CC SIZE: "<<collisionContainer->children.size()<<endl;
            } 
            init = false;
            cout << "STREAM SPAWNED" << endl;
        }
    }
    else{
        if (!init){
            //TODO: not completely deleting
            cout << "WATER JET OFF" << endl;
            for (int i=tile_range-1; i > -1; i--){
                FireStream* s = (FireStream*) streams[i];

                vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), streams[i]);
                if (collideItr != this->collisionContainer->children.end()){
                    this->collisionContainer->children.erase(collideItr);
                }
                vector<DisplayObject*>::iterator collideItr2 = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), streams[i]);
                if (collideItr2 != this->drawingContainer->children.end()){
                    this->drawingContainer->children.erase(collideItr2);
                }
                streams.pop_back();
                //delete stream
            }
            init = true;
                cout << "STREAM DELETED" << endl;
        }
    }
}

void Dragon::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        fire_timer = 0;
    }

    fire_timer++;
    if (fire_timer == fire_timer_max) state_switch(boss_states::Attack);
    
}


void Dragon::state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
        if (active) active = false;
        else active = true;
    }
    state_switch(boss_states::Idle);
}