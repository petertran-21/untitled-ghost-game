#include <iostream>
#include <cstdlib>

#include "WaterJet.h"

using namespace std;


WaterJet::WaterJet(DisplayObjectContainer *container, DisplayObjectContainer* drawContainer) : MainEnvObj(){

    this->addAnimation("./resources/items/", "water_jet", 1, 1, false);
	this->play("water_jet");
    this->collisionContainer = container;
    this->drawingContainer = drawContainer;
}

void WaterJet::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (active){
        if (init){
            cout << "WATER JET ON" << endl;
            for (int i=0; i < tile_range; i++){
                WaterStream* s = new WaterStream(dir, this->collisionContainer);
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
                cout<<"STREAMS SIZE: "<<streams.size()<<endl;
                cout<<"CC SIZE: "<<collisionContainer->children.size()<<endl;
            } 
            init = false;
            cout << "STREAM SPAWNED" << endl;
            for (int i =0; i <this->collisionContainer->children.size(); i++){
                DisplayObject* child = this->collisionContainer->children[i];
                if ((child->type == "EnvObj") && (child->subtype == 14)){ // 14 == WaterStream
                    WaterStream* ws = (WaterStream*) child;
                    cout<<"POSITION CC: "<<ws->position.x<<", "<<ws->position.y<<endl;
                }
            }
        }
    }
    else{
        if (!init){
            //TODO: not completely deleting
            cout << "WATER JET OFF" << endl;
            for (int i=tile_range-1; i > -1; i--){
                WaterStream* s = (WaterStream*) streams[i];
                s ->push_timer = s ->push_time_max + 10;
                vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), streams[i]);
                if (collideItr != this->collisionContainer->children.end()){
                    this->collisionContainer->children.erase(collideItr);
                }
                streams.pop_back();
                //delete stream
            }
            init = true;
                cout << "STREAM DELETED" << endl;
        }
    }
}

void WaterJet::resolve_collision(DisplayObject* obj){
    //do nothing
}