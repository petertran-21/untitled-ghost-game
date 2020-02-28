#include "DisplayObjectContainer.h"
#include "AffineTransform.h"
#include <vector>
#include <string>
#include "Game.h"

using namespace std;


DisplayObjectContainer::DisplayObjectContainer() : DisplayObject() {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id, filepath) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::~DisplayObjectContainer() {
    children.clear();
}

void DisplayObjectContainer::addChild(DisplayObject* child) {
    children.push_back(child);
    child->parent = this; // make sure to include reverse reference also
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            delete child;
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeImmediateChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            // delete the child
            delete children[i];
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeChild(int index) {
    if (index < children.size()) {
        delete children[index];
        children.erase(children.begin() + index);
    }
}

void DisplayObjectContainer::removeThis() {
    if (this->parent != NULL) {
        ((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
    }
}

int DisplayObjectContainer::numChildren() {
    return this->children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index) {
    if (index < 0 || index > numChildren()) {
        return NULL;
    }
    else return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            return children[i];
        }
        // check recursively?
    }
    return NULL;
}

DisplayObjectContainer* DisplayObjectContainer::copy(){
    DisplayObjectContainer* copy = new DisplayObjectContainer(to_string(rand()), this->imgPath);
	copy->parent = this->parent;
	copy->pivot = this->pivot;
	int posY = (this->position.y) - ((this->position.y) % Game::cellSize);
	copy->position.y = posY + 2 * Game::cellSize;
	copy->position.x = this->position.y;
	copy->width = this->width;
	copy->height = this->height;
	copy->visible = this->visible;
	copy->alpha = this->alpha;
	copy->rotation = this->rotation;
	copy->scaleX = this->scaleX;
	copy->scaleY = this->scaleY;

    for (auto child : children){
        copy->addChild(child->copy());
    }
	
	return copy;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys) {
    DisplayObject::update(pressedKeys);
    for (int i = 0; i < children.size(); i++) {
        children[i]->update(pressedKeys);
    }
}

void DisplayObjectContainer::draw(AffineTransform &at) {
    DisplayObject::draw(at);
    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (int i = 0; i < children.size(); i++) {
        children[i]->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}
