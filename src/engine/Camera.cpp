#include "Camera.h"

Camera::Camera() : DisplayObjectContainer() 
{
    this->type = "Camera";
    this->ghost = NULL;
}

Camera::~Camera()
{
    this->type = "Camera";
    this->ghost = NULL;
}

// Do not draw scenes that are "inactive."
void Camera::draw(AffineTransform &at){
    for (int i = 0; i < children.size(); i++){
        if (static_cast<Scene*>(children[i])->isActive) {
            children[i]->draw(at);
        }
    }
}

void Camera::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState)
{
    if( this->getChild(0)->type == "Scene" )
    {
        Scene* scene = (Scene*) this->getChild(0);
        float velocity = this->ghost->movespeed;
        int windowWidth = 1000;
        int windowHeight = 1000;
        int minDist = 200;
        if( this->ghost != NULL )
        {
            int xDiff = abs(abs(scene->position.x)-abs(this->ghost->position.x));
            int xTotal = abs(abs(scene->position.x + this->ghost->position.x) - windowWidth);

            if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end())
            {
                if(xDiff <= minDist)
                {
                    scene->position.x += velocity;
                }
            }
            if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end())
            {
                if (xTotal <= minDist + 100)
                {
                    scene->position.x -= velocity;
                }
            }

            int yDiff = abs(abs(scene->position.y)-abs(this->ghost->position.y));
            int yTotal = abs(abs(scene->position.y + this->ghost->position.y) - windowHeight);
            
            if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end())
            {
                if(yDiff <= minDist)
                {
                    scene->position.y += velocity;
                }
            }
            if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end())
            {
                if (yTotal <= minDist + 250)
                {
                    scene->position.y -= velocity;
                }
            }
        }
    }
    DisplayObjectContainer::update(pressedKeys, currState);
}

void Camera::changeScene(Scene* old_scene, Scene* new_scene){
    old_scene->isActive = false;
    new_scene->isActive = true;
}

void Camera::setGhost(Ghost* newGhost)
{
    this->ghost = newGhost;
}