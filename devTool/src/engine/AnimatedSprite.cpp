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

        //KEEP NULL, set in AnimatedSprite::update() when needed
        f->texture = NULL;

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
	copy->position.y = this->position.y;
	copy->position.x = this->position.x;
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
        cout << copy->imgPath << an->animName << endl;
        copy->play(an->animName);
        
    }
	
	return copy;
}

void AnimatedSprite::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer ) 
{
    Sprite::update( pressedKeys, currState, renderer );
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

            /**
             * IMPORTANT
             * 
             * This is where at run-time the correct renderer is supplied to AnimatedSprites
             */
            SDL_Surface* currFrameSurface = current->frames[current->curFrame]->image;
            SDL_Texture* currFrameTexture = current->frames[current->curFrame]->texture;
            if( currFrameTexture == NULL )
            {
                currFrameTexture = SDL_CreateTextureFromSurface( renderer, currFrameSurface );
            }
            DisplayObject::setTexture(currFrameTexture);
        }

    }

}

void AnimatedSprite::draw( AffineTransform &at, SDL_Renderer* renderer ) 
{
    Sprite::draw( at, renderer );
}
