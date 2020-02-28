#include "Sprite.h"
#include "Game.h"

using namespace std;

Sprite::Sprite() : DisplayObjectContainer() {
    this->type = "Sprite";
}

Sprite::Sprite(string id, string filepath) : DisplayObjectContainer(id, filepath){
    this->type = "Sprite";
}

Sprite::Sprite(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
    this->type = "Sprite";
}

Sprite* Sprite::copy(){
    Sprite* copy = new Sprite(to_string(rand()), this->imgPath);
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

void Sprite::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void Sprite::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}
