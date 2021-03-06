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
        if( this->ghost != NULL )
        {
            float velocity = this->ghost->movespeed;
            bool reversed = this->ghost->reverse_controls;
            int windowWidth = 1000;
            int windowHeight = 1000;
            int minDistWidth = windowWidth / 2;
            int minDistHeight = windowHeight / 2;

            int xDiff = abs(scene->position.x + this->ghost->position.x);
            int xTotal = abs(abs(scene->position.x + this->ghost->position.x) - windowWidth);

            if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end() || currState.leftStickX == -1)
            {
                if(reversed)
                {
                    if(xTotal <= minDistWidth + 100)
                    {
                        scene->position.x -= velocity;
                    }
                }
                else
                {
                    if(xDiff <= minDistWidth)
                    {
                        scene->position.x += velocity;
                    }
                }
            }
            if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end() || currState.leftStickX == 1)
            {
                if(reversed)
                {
                    if(xDiff <= minDistWidth)
                    {
                        scene->position.x += velocity;
                    }
                }
                else
                {
                    if(xTotal <= minDistWidth + 100)
                    {
                        scene->position.x -= velocity;
                    }
                }
            }

            int yDiff = abs(scene->position.y + this->ghost->position.y);
            int yTotal = abs(abs(scene->position.y + this->ghost->position.y) - windowHeight);
            
            if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end() || currState.leftStickY == -1)
            {
                if(reversed)
                {
                    if(yTotal <= minDistHeight + 200)
                    {
                        scene->position.y -= velocity;
                    }
                }
                else
                {
                    if(yDiff <= minDistHeight)
                    {
                        scene->position.y += velocity;
                    }
                }
            }
            if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end() || currState.leftStickY == 1)
            {
                if(reversed)
                {
                    if(yDiff <= minDistHeight)
                    {
                        scene->position.y += velocity;
                    }
                }
                else
                {
                    if (yTotal <= minDistHeight + 200)
                    {
                        scene->position.y -= velocity;
                    }
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