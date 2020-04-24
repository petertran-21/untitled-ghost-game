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
        float velocity = this->ghost->movespeed / 4;
        if( this->ghost != NULL )
        {
            if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()){
            	scene->position.x -= velocity;
            }
            if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()){
            	scene->position.x += velocity;
            }
            if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()){
            	scene->position.y += velocity;
            }
            if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()){
            	scene->position.y -= velocity;
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