#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "MainNPC.h"

using namespace std;

MainNPC::MainNPC() : AnimatedSprite("NPC"){
    this->type = "NPC";
}

// MainNPC::MainNPC(vector<DisplayObject*> passedInventory) : AnimatedSprite("NPC"){
//     this->type = "NPC";
//     this->inventory=passedInventory;
// }

MainNPC::MainNPC(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory) : AnimatedSprite("NPC"){
    this->type = "NPC";
    this->collisionContainer = container;
    this->drawingContainer = allSprites;
    //this->inventory=passedInventory;
}

void MainNPC::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

    if (!is_possessed) state_switch(npc_states::Idle);

    MainNPC::state_execute(pressedKeys, currState);

    //cooldown on ability usage
    if (cooldown_timer > 0) cooldown_timer--;
    if (reverse_controls) {reverse_controls_timer++; if(reverse_controls_timer==reverse_controls_max){ reverse_controls=false; reverse_controls_timer=0;}}

}

void MainNPC::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

//GENERAL NPC STATES
void MainNPC::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    //if (state_new) cout << "STATE: IDLE" << endl;

    if (is_possessed) state_switch(npc_states::Possessed);
}

void MainNPC::state_possessed(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (state_new){
       
    }

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
    //if (state_new) cout << "STATE: MOVING" << endl;

    bool is_moving = false;
    //check for movement on controller
    if (currState.leftStickY < 0){ is_moving = true; dir = N; if(reverse_controls){dir=S;}}
    else if (currState.leftStickX < 0){ is_moving = true; dir = W; if(reverse_controls){dir=E;}}
    else if (currState.leftStickY > 0){ is_moving = true; dir = S; if(reverse_controls){dir=N;}}
    else if (currState.leftStickX > 0){ is_moving = true; dir = E; if(reverse_controls){dir=W;}}

    //check for movement on keyboard
    if(pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end())
    {
        is_moving = true;
        dir = N;
        if(reverse_controls){dir=S;}  
    }
    else if(pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end())
    {
        is_moving = true;
        dir = W;
        if(reverse_controls){dir=E;}  
    }
    else if(pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end())
    {
        is_moving = true;
        dir = S;
        if(reverse_controls){dir=N;}  
    }
    else if(pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end())
    {
        is_moving = true;
        dir = E;
        if(reverse_controls){dir=W;}  
    }

    //move npc along grid
    if (is_moving && can_move){
        switch (dir){
            case N: 
                //check collision @ direction//
                position.y -= grid_size; 
                abilityPt = {0, -100};
                if (this->changeAnim){this->play("back");}
                break;
            case S:
                //check collision @ direction//
                position.y += grid_size;
                abilityPt = {0, 100};
                if (this->changeAnim){this->play("forward");}
                break;
            case E: 
                //check collision @ direction//
                position.x += grid_size; 
                abilityPt = {100, 0};
                if (this->changeAnim){this->play("right");}
                break;
            case W: 
                //check collision @ direction//
                position.x -= grid_size; 
                abilityPt = {-100, 0};
                if (this->changeAnim){this->play("left");}
                break;
            default:
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
            default:
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
            default:
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

    //COLLIDES WITH FALLEN TREE
    FallenTree* ft = dynamic_cast<FallenTree*>(obj);
    if (ft){

        //DO NOTHING 
        if (ft->destroyed) return;
    }

    //COLLIDES WITH DOOR
    if (obj->getSubtype() == DOOR_SUBTYPE){
        Door* d = dynamic_cast<Door*>(d);
    }

    //COLLIDES WITH GEM
    Gem* g = dynamic_cast<Gem*>(obj);
    if (g){
        TextAlert* t = new TextAlert(position.x, position.y, "Gem Collected", this->drawingContainer);
        DisplayObject* gem = new DisplayObject("Gem","./resources/items/gem_1.png");     
        inventory->push_back(gem);
        g->position.x = -100000;
        g->position.y = -100000;
        
    }

    //COLLIDES WITH HORN
    HornFragment* hf = dynamic_cast<HornFragment*>(obj);
    if (hf){
        TextAlert* t = new TextAlert(position.x, position.y, "Horn Fragment Collected", this->drawingContainer);
        DisplayObject* horn = new DisplayObject("HornFragment","./resources/items/horn_fragment_1.png");     
        inventory->push_back(horn);
        hf->position.x = -100000;
        hf->position.y = -100000;
    }

    // DEFAULT FOR COLLIDING WITH SOLIDS

    //cout<<"INVENTORY"<<inventory->size()<<endl;
	if (reverseCollisions){
        if (obj && (obj->type == "Land")){
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
    else if (obj && ((obj->type == "EnvObj" || obj->type == "Wall") || obj->getSubtype() == 127)){
        // cout<<"COLLIDING WITH ENV"<<endl;
        //check that npcs are overlapping
        // cout<<"COLLIDING ENV: "<<obj->type<<" "<<obj->getSubtype()<<endl;
        //cout<<"COLLIDING ENV: "<<obj->type<<" "<<obj->getSubtype()<<endl;
        if (obj->getSubtype() == 127){
            SwampBridge* s = (SwampBridge*) obj;
            if (s->cancross==true){
                return;
            }
        }
        if (((position.y == obj->position.y) && (position.x == obj->position.x)) || (obj->getSubtype() == 120)){ //enter this if poisongas touches
            if (obj->getSubtype() == 120){
                if (this->detox == true){
                    return;
                }
            }
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
            default:
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
    // cout << "TYPE: "<<obj->type<<", subtype:  "<<obj->getSubtype()<<", "<<(obj->type=="Collectible")<<" HERE:"<<obj->imgPath<<endl;
    // cout << "POS: "<<obj->position.x<<" "<<obj->position.y<<" NPC POS: "<<this->position.x<<this->position.y<<endl;
    // cout<<"NUM COLLIDE CHILDREN: "<<collideContainer->children.size()<<endl;
    // cout<<"NUM DRAW CHILDREN: "<<drawContainer->children.size()<<endl;
    if (obj->type == "Collectible"){
        if ((obj->position.x == this->position.x) && (obj->position.y == this->position.y)){
            cout<<"RIGTJ ON TOP EACH OTHER"<<endl;
            switch(obj->getSubtype()){
                case 9:{//item pouch  
                    DisplayObject* item = new DisplayObject(obj->id,obj->imgPath+"item_pouch_1.png");     
                    inventory->push_back(item);
                    
                    // ItemPouch* collect = (ItemPouch*) obj;
                    // //doesn't work in certain rooms (swampIsland)
                    // vector<DisplayObject*>::iterator collideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), collect);
                    // vector<DisplayObject*>::iterator drawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), collect);
                    // if (collideItr != this->collisionContainer->children.end() && drawItr != this->drawingContainer->children.end()){
                    //     cout<<"DELETE IT"<<endl;
                    //     this->collisionContainer->children.erase(collideItr);
                    //     this->drawingContainer->children.erase(drawItr);
                    // } 
                    // break;

                    TextAlert* t = new TextAlert(position.x, position.y, "Collectible Found", this);
                    
                    obj->position.x = -100000;
                    obj->position.y = -100000;
                    break;

                }
                case 122:{ //herb
                    cout<<"COLLECT HERB"<<endl;
                    DisplayObject* herb = new DisplayObject(obj->id,obj->imgPath+"herb_1.png");     
                    inventory->push_back(herb);
                    Herb* herb_collect = (Herb*) obj;
                    // vector<DisplayObject*>::iterator herbcollideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), herb_collect);
                    // vector<DisplayObject*>::iterator herbdrawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), herb_collect);
                    // if (herbcollideItr != this->collisionContainer->children.end() && herbdrawItr != this->drawingContainer->children.end()){
                    //     this->collisionContainer->children.erase(herbcollideItr);
                    //     this->drawingContainer->children.erase(herbdrawItr);
                    // } 
                    obj->position.x = -100000;
                    obj->position.y = -100000;
//                     vector<DisplayObject*>::iterator herbcollideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), herb_collect);
//                     vector<DisplayObject*>::iterator herbdrawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), herb_collect);
//                     if (herbcollideItr != this->collisionContainer->children.end() && herbdrawItr != this->drawingContainer->children.end()){
//                         this->collisionContainer->children.erase(herbcollideItr);
//                         this->drawingContainer->children.erase(herbdrawItr);
//                     } 

                    TextAlert* t = new TextAlert(position.x, position.y, "Herb Collected", this->drawingContainer);
                    break;
                }
                case 305:{ //bucket

                    cout<<"MADE IT"<<endl;
                    DisplayObject* bucket = new DisplayObject(obj->id,obj->imgPath+"bucket_empty_1.png");     
                    inventory->push_back(bucket);
                    Bucket* bucket_collect = (Bucket*) obj;
                    // vector<DisplayObject*>::iterator bucketcollideItr = find(this->collisionContainer->children.begin(), this->collisionContainer->children.end(), bucket_collect);
                    // vector<DisplayObject*>::iterator bucketdrawItr = find(this->drawingContainer->children.begin(), this->drawingContainer->children.end(), bucket_collect);
                    // if (bucketcollideItr != this->collisionContainer->children.end() && bucketdrawItr != this->drawingContainer->children.end()){
                    //     this->collisionContainer->children.erase(bucketcollideItr);
                    //     this->drawingContainer->children.erase(bucketdrawItr);
                    // } 
                    obj->position.x = -100000;
                    obj->position.y = -100000;
                    TextAlert* t = new TextAlert(position.x, position.y, "Bucket Collected", this->drawingContainer);
                    break;
                }
            }
        } 
    }
}

