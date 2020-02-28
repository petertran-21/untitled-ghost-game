#include "AnimatedSprite.h"
#include "Game.h"
#include <string>

using namespace std;

AnimatedSprite::AnimatedSprite() : Sprite() {
    this->type = "AnimatedSprite";
}

AnimatedSprite::AnimatedSprite(string id) : Sprite(id, 0, 0, 0) {
    this->type = "AnimatedSprite";
}

AnimatedSprite::~AnimatedSprite() {
    for (Animation* an : animations) {
        for (int i = 0; i < an->numFrames; i++) {// this needs to be an iterator loop
            if(an->frames[i]->image != NULL) SDL_FreeSurface(an->frames[i]->image);
	        if(an->frames[i]->texture != NULL) SDL_DestroyTexture(an->frames[i]->texture);
            delete an->frames[i];
        }
        delete an->frames;
        delete an;
    }
}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop) {
    Animation* anim = new Animation();
    anim->animName = animName;
    anim->numFrames = numFrames;
    anim->frameRate = frameRate;
    anim->loop = loop;
    anim->curFrame = 0;
    anim->frames = new Frame*[numFrames]; // new frame pointer array of size numFrames;
    for (int i = 0; i < numFrames; i++ ) {
        Frame* f = new Frame();
        string path = basepath + animName + "_" + to_string(i+1) + ".png";
        f->image = IMG_Load(path.c_str());
        f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
        anim->frames[i] = f;
    }
    animations.push_back(anim);
}

Animation* AnimatedSprite::getAnimation(string animName) {
    for (int i = 0; i < animations.size(); i++) {
        if (animations[i]->animName == animName) {
            return animations[i];
        }
    }
    return NULL;
}

vector<Animation*> AnimatedSprite::getAnimations(){
    return this->animations;
}

void AnimatedSprite::play(string animName) {
    Animation* anim = getAnimation(animName);
    if (anim != NULL) {
        this->current = anim;
        this->current->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::replay() {
    if (this->current != NULL) {
        current->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::stop() {
    this->playing = false;
}

AnimatedSprite* AnimatedSprite::copy(){
    AnimatedSprite* copy = new AnimatedSprite();
    copy->id = to_string(rand());
    copy->imgPath = this->imgPath;
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

    for (Animation* an : this->animations){
        copy->addAnimation(copy->imgPath, an->animName, an->numFrames, an->frameRate, an->loop);
    }
	
	return copy;
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys) {
    Sprite::update(pressedKeys);
    if (playing) {
        frameCount++;
        if (frameCount % current->frameRate == 0) {
            // increment local frame counter
            current->curFrame++;
            // check for array out of bounds
            if (current->curFrame == current->numFrames) {
                // reset the animation
                current->curFrame = 0;
                // check for looping
                if (!current->loop) {
                    stop();
                }
            }
            DisplayObject::setTexture(current->frames[current->curFrame]->texture);
        }

    }

}

void AnimatedSprite::draw(AffineTransform &at) {
    Sprite::draw(at);
}
