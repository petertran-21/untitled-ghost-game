#include "UIDefs.h"
#include <iostream>
#include <algorithm>

SelectionMenu::SelectionMenu(int posX, int posY, int width, int height) : DisplayObjectContainer(){
    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;
}

SelectionMenu::~SelectionMenu(){
    DisplayObjectContainer::removeThis();
}


// Ideally, I'd like the height of this UI element to dynamically scale based on how many entries were added to it.
// That's a feature for another time, though.
void SelectionMenu::addToMenu(std::string entry){
    this->entries.push_back(entry);
    Text* newTextObject = new Text(entry);
    this->addChild(newTextObject);

    // Offset menu options.                                         // remember indexed at 0
    this->children.back()->position.y += (100 * (this->entries.size() - 1));
}

void SelectionMenu::removeFromMenu(std::string entry){
    std::vector<std::string> entries = this->entries;
    entries.erase(std::remove(entries.begin(), entries.end(), entry), entries.end());

    Text* removeThis = new Text(entry);
    this->removeImmediateChild(removeThis);        // Remove from the 'children' vector, which SelectionMenu inherits from DOC.
    delete removeThis;
}

std::string SelectionMenu::getCurrentlySelected(){
    return this->entries[this->selectedIndex];
}

void SelectionMenu::incrementPosition(){
    if (this->selectedIndex < this->entries.size() - 1){
        static_cast<Text*>(this->children[this->selectedIndex])->setColor(255, 255, 255);
        static_cast<Text*>(this->children[this->selectedIndex])->reloadFont();
        this->selectedIndex++;
        static_cast<Text*>(this->children[this->selectedIndex])->setColor(this->highlightedColor);
        static_cast<Text*>(this->children[this->selectedIndex])->reloadFont();
    } else {
        std::cout << "Note: You tried to exceed the boundaries of SelectionMenu when calling incrementPosition()" << std::endl;
    }
}

void SelectionMenu::decrementPosition(){
    if (this->selectedIndex > 0){
        static_cast<Text*>(this->children[this->selectedIndex])->setColor(255, 255, 255);
        static_cast<Text*>(this->children[this->selectedIndex])->reloadFont();
        this->selectedIndex--;
        static_cast<Text*>(this->children[this->selectedIndex])->setColor(this->highlightedColor);
        static_cast<Text*>(this->children[this->selectedIndex])->reloadFont();
    } else {
        std::cout << "Note: You tried to exceed the boundaries of SelectionMenu when calling decrementPosition()" << std::endl;
    }
}

void SelectionMenu::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}