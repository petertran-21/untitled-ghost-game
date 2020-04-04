#include "UIDefs.h"
#include <iostream>
#include <algorithm>

Checklist::Checklist(int posX, int posY, int width, int height) : DisplayObjectContainer(){
    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;
}

Checklist::~Checklist(){
    DisplayObjectContainer::removeThis();
}


// Ideally, I'd like the height of this UI element to dynamically scale based on how many entries were added to it.
// That's a feature for another time, though.
void Checklist::addEntry(std::string entry){
    this->entries.push_back(entry);
    Text* newTextObject = new Text(entry);
    this->addChild(newTextObject);

    // Offset menu options.                                         // remember indexed at 0
    this->children.back()->position.y += (100 * (this->entries.size() - 1));
}

void Checklist::removeEntry(std::string entry){
    std::vector<std::string> entries = this->entries;
    entries.erase(std::remove(entries.begin(), entries.end(), entry), entries.end());

    Text* removeThis = new Text(entry);
    this->removeImmediateChild(removeThis);        // Remove from the 'children' vector, which SelectionMenu inherits from DOC.
    delete removeThis;
}

void Checklist::completeEntry(std::string entry){
    for(int i=0;i<this->entries.size();i++){
        if(this->entries[i]==entry){
            static_cast<Text*>(this->children[i])->setColor(this->completedColor);
            static_cast<Text*>(this->children[i])->reloadFont();
        }
    }
}

void Checklist::completeEntry(int index){
    if(index<this->entries.size() && index >= 0){
        static_cast<Text*>(this->children[index])->setColor(this->completedColor);
        static_cast<Text*>(this->children[index])->reloadFont();
    }
}

void Checklist::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}