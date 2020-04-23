#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "MainNPC.h"

using namespace std;

MainNPC::MainNPC() : AnimatedSprite("NPC"){
    this->type = "NPC";
}

MainNPC::MainNPC(DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : AnimatedSprite("NPC"){
    this->type = "NPC";
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
}

MainNPC::MainNPC(Scene* currScene) : AnimatedSprite("NPC"){
    this->type = "NPC";
    this->currScene = currScene;
}

void MainNPC::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

    MainNPC::state_execute(pressedKeys, currState);

    //cooldown on ability usage
    if (cooldown_timer > 0) cooldown_timer--;

}

void MainNPC::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

//GENERAL NPC STATES
void MainNPC::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: IDLE" << endl;

    if (is_possessed) state_switch(npc_states::Possessed);
}

void MainNPC::state_possessed(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: POSSESSED" << endl;

    if (Controls::holdLeft(pressedKeys, currState))state_switch(npc_states::Moving);
    if (Controls::holdRight(pressedKeys, currState)) state_switch(npc_states::Moving);
    if (Controls::holdUp(pressedKeys, currState)) state_switch(npc_states::Moving);
    if (Controls::holdDown(pressedKeys, currState)) state_switch(npc_states::Moving);

    //exit NPC
    if (Controls::pressPossess(pressedKeys, currState)){
        state_switch(npc_states::Idle);
        is_possessed = false;
    }

    //ability
    if (Controls::pressAbility(pressedKeys, currState)){
        if (cooldown_timer == 0){
            state_switch(npc_states::Ability); 
            cooldown_timer = cooldown_max;
        }
    }

}

void MainNPC::state_moving(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new) cout << "STATE: MOVING" << endl;

    bool is_moving = false;
    //check for movement on controller
    if (currState.leftStickY < 0){ is_moving = true; dir = N;}
    else if (currState.leftStickX < 0){ is_moving = true; dir = W;}
    else if (currState.leftStickY > 0){ is_moving = true; dir = S;}
    else if (currState.leftStickX > 0){ is_moving = true; dir = E;}

    //check for movement on keyboard
    for(int code:pressedKeys){
        if      (code == SDL_SCANCODE_W || currState.leftStickY < 0){ is_moving = true; dir = N;}
        else if (code == SDL_SCANCODE_A || currState.leftStickX < 0){ is_moving = true; dir = W;}
        else if (code == SDL_SCANCODE_S || currState.leftStickY > 0){ is_moving = true; dir = S;}
        else if (code == SDL_SCANCODE_D || currState.leftStickY > 0){ is_moving = true; dir = E;}
    }

    //move npc along grid
    if (is_moving && can_move){
        switch (dir){
            case N: 
                //check collision @ direction//
                position.y -= grid_size; 
                abilityPt = {0, -100};
                this->play("back");
                break;
            case S:
                //check collision @ direction//
                position.y += grid_size;
                abilityPt = {0, 100};
                this->play("forward");
                break;
            case E: 
                //check collision @ direction//
                position.x += grid_size; 
                abilityPt = {100, 0};
                this->facingRight = true;
                this->play("right");
                break;
            case W: 
                //check collision @ direction//
                position.x -= grid_size; 
                abilityPt = {-100, 0};
                this->facingRight = false;
                this->play("left");
                break;
        }
        // this->play("idle");

        for (DisplayObject* child:children){
                    switch (dir){
            case N: 
                //check collision @ direction//
                child->position.y += grid_size; 
                break;
            case S:
                //check collision @ direction//
                child->position.y -= grid_size;
                break;
            case E: 
                //check collision @ direction//
                child->position.x -= grid_size; 
                break;
            case W: 
                //check collision @ direction//
                child->position.x += grid_size; 
                break;
            }
        }        
        can_move = false;
    }

    //leave state on key release
    if (!is_moving){
        can_move = true;
        state_switch(npc_states::Possessed);
    }
}


//STATE MACHINE METHODS
void MainNPC::state_switch(npc_states new_state){
    if (state != new_state){
        state_new = true;
        state = new_state;
        state_updated = true;
    }
}
void MainNPC::state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    switch(state){
        case npc_states::Idle:      MainNPC::state_idle(pressedKeys, currState);      break;
        case npc_states::Possessed: MainNPC::state_possessed(pressedKeys, currState); break;
        case npc_states::Moving:    MainNPC::state_moving(pressedKeys, currState);    break;
        case npc_states::Ability:   state_ability(pressedKeys, currState);            break;
    }
    if (state_updated) state_updated = false;
    else state_new = false;
}

void MainNPC::resolve_collision(DisplayObject *obj){

    //COLLIDES WITH WATER STREAM
    WaterStream* s = dynamic_cast<WaterStream*>(obj);
    if (s){
        //DO NOTHING 
        return;
    }

    //COLLIDES WITH BROKEN WALL
    BreakableWall* b = dynamic_cast<BreakableWall*>(obj);
    if (b){

        //DO NOTHING 
        if (b->broken) return;
    }

    //COLLIDES WITH SUNKEN LOG
    Log* l = dynamic_cast<Log*>(obj);
    if (l){

        //DO NOTHING 
        if (l->sunk && l->chopped) return;

         //check that npcs are overlapping
        if ((position.y == obj->position.y) && (position.x == obj->position.x)){
            switch (dir){
            //reset possessed npc's location to previous based on location it came from
            case N:
                position.y = position.y + 100;
                dir = None;
                break;
            case E:
                position.x = position.x - 100;
                dir = None;
                break;
            case S: 
                position.y = position.y - 100;
                dir = None;
                break;
            case W:
                position.x = position.x + 100;
                dir = None;
                break;
            }
        }
    }

    //COLLIDES WITH BURNT SHRUB
    Shrub* sh = dynamic_cast<Shrub*>(obj);
    if (sh){

        //DO NOTHING 
        if (sh->burned) return;
    }

    //COLLIDES WITH BRIDGE
    Bridge* br = dynamic_cast<Bridge*>(obj);
    if (br){

        //DO NOTHING 
        if (br->open) return;
    }

    //COLLIDES WITH DOOR
    if (obj->getSubtype() == DOOR_SUBTYPE){
        Door* d = dynamic_cast<Door*>(d);
        cout<<"DORR EXISTS: "<<d->position.x<<" "<<d->position.y<<endl;
        cout<<"NPC AT: "<<position.x<<" "<<position.y<<endl;
        if (d->open) cout<<"IS OPEN"<<endl;
    }

    // DEFAULT FOR COLLIDING WITH SOLIDS
    // cout<<"Colliing wiht envObj"<<(obj&&(obj->type == "EnvObj"))<< " "<<(obj->type == "EnvObj")<<endl;
	if (obj && (obj->type == "EnvObj" || obj->type == "Wall")){
        // cout<<"COLLIDING WITH ENV"<<endl;
        //check that npcs are overlapping
        if ((position.y == obj->position.y) && (position.x == obj->position.x)){
            switch (dir){
            //reset possessed npc's location to previous based on location it came from
            case N:
                position.y = position.y + 100;
                dir = None;
                break;
            case E:
                position.x = position.x - 100;
                dir = None;
                break;
            case S: 
                position.y = position.y - 100;
                dir = None;
                break;
            case W:
                position.x = position.x + 100;
                dir = None;
                break;
            }
        }
	}
}

void MainNPC::resolve_adjacency(DisplayObject *obj, int status){
    //cout << "ADJACENCY STATUS :" << status << endl;
}

void MainNPC::resolve_collectible_collision(DisplayObject *obj, DisplayObjectContainer* collideContainer, DisplayObjectContainer* drawContainer){
    //COLLISIONS WITH COLLECTIBLES
    // cout<<"foreground NPC address: "<<drawingContainer<<endl;
    // cout << "TYPE: "<<obj->type<<", subtype:  "<<obj->subtype<<", "<<(obj->type=="Collectible")<<endl;
    // cout<<"NUM COLLIDE CHILDREN: "<<collideContainer->children.size()<<endl;
    // cout<<"NUM DRAW CHILDREN: "<<drawContainer->children.size()<<endl;
    if (obj->type == "Collectible"){
        if ((obj->position.x == this->position.x) && (obj->position.y == this->position.y)){
            switch(obj->getSubtype()){
                case 9: //item pouch
                    ItemPouch* collect = (ItemPouch*) obj;
                    vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), collect);
                    vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), collect);
                    if (collideItr != this->collisionContainer->children.end() && collideItr != this->drawingContainer->children.end()){
                        this->collisionContainer->children.erase(collideItr);
                        this->drawingContainer->children.erase(drawItr);
                    } 
            }
        } 
    }
}

