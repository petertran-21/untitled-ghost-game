#include "UIDefs.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory(int posX, int posY, int width, int height) : DisplayObjectContainer(){
    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;

}

Inventory::~Inventory(){
    DisplayObjectContainer::removeThis();
}

void Inventory::draw(AffineTransform &at){
    for(int i = 0; i < this->entries.size(); i++){
        if(i > 8){
            break;
        }
        DisplayObject* temp=new DisplayObject(this->entries[i]->id,this->entries[i]->imgPath);
        
        temp->position.x=i*100;
        this->addChild(temp);
    }
    DisplayObjectContainer::draw(at);
}