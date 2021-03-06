#include "UIDefs.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory(int posX, int posY, int width, int height) : DisplayObjectContainer(){
    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;
    this->label = new TextBox("Inventory", 0, -65, width, 65);
    this->label->children.back()->position.x += (width / 2) - 50;
    this->label->children.back()->position.y -= 20;
    this->addChild(this->label);
    // DisplayObject* a = new DisplayObject();
    // this->entries.push_back(a);

}

Inventory::~Inventory(){
    DisplayObjectContainer::removeThis();
}


void Inventory::draw(AffineTransform &at){
    for(int i = 0; i < this->entries.size(); i++){
        if(this->entries[i]->type == "TextBox"){
            continue;
        }
        if(i > 8){
            break;
        }
        DisplayObject* temp=new DisplayObject(this->entries[i]->id,this->entries[i]->imgPath);
        temp->width=50;
        temp->height=50;
        temp->position.x=i*50;
        if(i>3){
            temp->position.x=((i-1)%4)*50;
            temp->position.y=50; //another row, so it's 2 rows x 4 columns ideally
        }
        this->addChild(temp);
    }
    DisplayObjectContainer::draw(at);
}