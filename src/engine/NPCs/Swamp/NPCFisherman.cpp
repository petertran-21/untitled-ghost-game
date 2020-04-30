#include <iostream>
#include <cstdlib>
#include "NPCFisherman.h"

using namespace std;

NPCFisherman::NPCFisherman(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : MainNPC(){
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_idle", 1, 1, true, "idle");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_forward", 6, 10, true, "forward");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_left", 6, 10, true, "left'");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_right", 6, 10, true, "right");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_back", 6, 10, true, "back");
    this->addAnimation("./resources/npcs/fisherman/", "fisherman_boat", 1, 1, false, "onboat");

	this->play("idle");

    this->inventory = &passedInventory;
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    this->subtype = NPCFISHERMAN_SUBTYPE;
}

void NPCFisherman::state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
        if (state_new){
        cout << "STATE: ABILITY" << endl;
        switch(dir){
            case N: 
                hitBoat = true;
                break;
            case S: 
                hitBoat = true;
                break;
            case E: 
                hitBoat = true;
                break;
            case W: 
                 hitBoat = true;
                break;
        }
    }
    state_switch(npc_states::Possessed);
}

void NPCFisherman::resolve_collision(DisplayObject * obj){ 
    MainNPC::resolve_collectible_collision(obj, this->collisionContainer, this->drawingContainer);
    MainNPC::resolve_collision(obj);   
    // cout<<" offboat: "<<(offBoat)<< " hasboat: "<<
    //     hasBoat<<" hitboat: "<<(hitBoat == true)<<"land? "<<(obj->type == "Land")<<endl;
    // cout<<"THIS: "<<((obj->type == "Land") && (offBoat == false) && (hasBoat == true) && (hitBoat == true))<<endl;

    if (obj->getSubtype() == 121 && hasBoat==false && hitBoat == true){
        //get on boat
        this->position.x = obj->position.x;
        this->position.y = obj->position.y;
        Boat* b  = (Boat*) obj;
        //TODO: fix boat bug: make boat disappear (play diff animation) and then bring it back --> prob add boat as child to this npc
        vector<DisplayObject*>::iterator bcollideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), b);
        vector<DisplayObject*>::iterator bdrawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), b);
        if (bcollideItr != this->collisionContainer->children.end() && bdrawItr != this->drawingContainer->children.end()){
            this->collisionContainer->children.erase(bcollideItr);
            this->drawingContainer->children.erase(bdrawItr);
        } 
        this->changeAnim = false;
        this->play("onboat");
        this->reverseCollisions = true;
        this->offBoat = false;
        this->hasBoat=true;
        this->hitBoat = false;
    }
}

void NPCFisherman::resolve_adjacency(DisplayObject * obj, int status){
    cout << "ADJACENCY STATUS :" << status << endl;
    cout<<" offboat: "<<(offBoat)<< " hasboat: "<<
        hasBoat<<" hitboat: "<<(hitBoat == true)<<"land? "<<(obj->type == "Land")<<endl;
    
    if (status && (hasBoat == true) && (hitBoat == true)){        
        //get off boat
        this->changeAnim = true;
        this->reverseCollisions = false;
        this->offBoat = true;
        this->hasBoat = false;

        Boat* boat = new Boat(this->collisionContainer);
        this->drawingContainer->addChild(boat);
        boat->position.x = this->position.x;
        boat->position.y = this->position.y;

        //physically get back onto land
        this->position.x = obj->position.x;
        this->position.y = obj->position.y;
        this->play("idle"); 
        this->hitBoat = false;

    }
}