#include <iostream>
#include <cstdlib>

#include "ForestDoor.h"

using namespace std;


ForestDoor::ForestDoor(DisplayObjectContainer* container, vector<DisplayObject*> &passedInventory) : MainEnvObj(){
    this->id = "ForestDoor";
    this->addAnimation("./resources/items/", "forest_door_open", 1, 1, false);
    this->addAnimation("./resources/items/", "forest_door_closed", 1, 1, false);
	this->play("forest_door_closed");
    this->collisionContainer = container;
    container->addChild(this);

    this->inventory= &passedInventory;
}

void ForestDoor::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainEnvObj::update(pressedKeys, currState);

    if (!open){
        vector<DisplayObject*> inv = *inventory;

        int recipe_gems_max = 2;
        int counter = 0;

        //CHECK THAT YOU HAVE ENOUGH SUPPLIES
        for (int i = 0; i < inv.size(); i++){
            if (inv[i]->id == "Gem"){
                counter++;
            }
        }

        //HAVE ENOUGH GEMS
        if (counter >= recipe_gems_max){
            open = true;
            counter = 0;
        }

    }
    if (open){
        this->play("forest_door_open");

        //SPAWN THE EXIT
        if (exit == NULL){
            exit = new SceneTrigger(this->collisionContainer, "./resources/scenes/campsite.json");
            this->collisionContainer->addChild(exit);
            exit->position.x = 500;
            exit->position.y = 200;
        }
    }
}
