#include <iostream>
#include <cstdlib>

#include "Monument.h"

using namespace std;


Monument::Monument(DisplayObjectContainer* container, vector<DisplayObject*> &passedInventory) : MainEnvObj(){
    this->id = "Monument";
    this->type = "Monument";
    this->addAnimation("./resources/items/", "monument_empty", 1, 1, false);
    this->addAnimation("./resources/items/", "monument_complete", 1, 1, false);
	this->play("monument_empty");
    this->collisionContainer = container;
    container->addChild(this);
    this->inventory = &passedInventory;
}

void Monument::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (!complete){
        vector<DisplayObject*> inv = *inventory;

        int horns_max = 4;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "HornFragment"){
                counter++;
            }
        }

        //HAVE ENOUGH HORNS
        if (counter >= horns_max){
            complete = true;
            counter = 0;
        }

    }
    if (complete){
        this->play("monument_complete");

    }
}

void Monument::resolve_collision(DisplayObject *obj){
    if (obj->getSubtype()==4){
        if (complete){
            if (this->t == NULL){
                t = new TextBox(position.x - 550, position.y + 800);
                t->setText("You did it!");
                this->addChild(t);
            }
        }
        else{
            if (this->t == NULL){
                t = new TextBox(position.x - 550, position.y + 800);
                t->setText("Return when the Horn is complete...");
                this->addChild(t);
            }
        }
    }
}