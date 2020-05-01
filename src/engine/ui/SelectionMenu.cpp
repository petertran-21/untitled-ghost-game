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

SelectionMenu::~SelectionMenu(){}       // Calls parent destructor already.

void SelectionMenu::addToMenu(std::string entry){
    this->entries.push_back(entry);
    Text* newTextObject = new Text(entry);
    newTextObject->width = entry.size() * 20;        // Fixes scaling issue.
    this->addChild(newTextObject);

    // Offset menu options.                                         // remember indexed at 0
    this->children.back()->position.x += (width / 2) - 40;    // margins
    this->children.back()->position.y += (100 * (this->entries.size() - 1)) - 10;

    // Automatically scale the height of the SelectionMenu equal to number of options on it.
    this->height += 100;

}

void SelectionMenu::removeFromMenu(std::string entry){
    std::vector<std::string> entries = this->entries;
    entries.erase(std::remove(entries.begin(), entries.end(), entry), entries.end());

    Text* removeThis = new Text(entry);     // Create a text entry that matches the one we want to delete for easy removal using below line.
    this->removeImmediateChild(removeThis);        // Remove from the 'children' vector, which SelectionMenu inherits from DOC.
    delete removeThis;
    this->height -= 100;
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
    // When the selection menu is rendered/opened, thanks to selectedIndex being -1. automatically "select" the first option when we open the menu.
    // When the menu is closed/removed from render, the selectedIndex should be set back to -1 so the first option can automatically be selected when we reopen it.
    if (this->selectedIndex == -1 && this->entries.size() > 0){
        this->selectedIndex = 0;
        static_cast<Text*>(this->children[this->selectedIndex])->setColor(this->highlightedColor);
        static_cast<Text*>(this->children[this->selectedIndex])->reloadFont();
    }
    DisplayObjectContainer::draw(at);
}