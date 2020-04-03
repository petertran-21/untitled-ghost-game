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
                streams.push_back(s);
                this->drawingContainer->addChild(s);  
                s->position = position;
                this->collisionContainer->addChild(s);

                int dist = 100*(i+1);
                switch (dir){
                    case N: s->position.y = position.y-dist; break;
                    case S: s->position.y = position.y+dist; break;
                    case E: s->position.x = position.x+dist; break;
                    case W: s->position.x = position.x-dist; break;
                }
                init = false;
                cout << "STREAM SPAWNED" << endl;
            }
        }
    }
    else{
        if (!init){
            //TODO: not completely deleting
            cout << "WATER JET OFF" << endl;
            for (int i=tile_range-1; i > -1; i--){
                // TODO: BUG FIX --> Reappearing
                vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), streams[i]);
                vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), streams[i]);
                if (collideItr != this->collisionContainer->children.end() && drawItr != this->drawingContainer->children.end()){
                    this->collisionContainer->children.erase(collideItr);
                    // cout<<"REMOVING CHILD"<<endl;
                    this->drawingContainer->children.erase(drawItr);
                }
                // cout<<"DRAWING CONT SIZE: "<< this->drawingContainer->children.size()<<endl;
                // cout<<"COLLISION CONT SIZE: "<< this->collisionContainer->children.size()<<endl;
                streams.pop_back();
                //delete stream
                init = true;
                cout << "STREAM DELETED" << endl;
                
            }
        }
    }
}

void WaterJet::resolve_collision(DisplayObject* obj){
    //do nothing
}