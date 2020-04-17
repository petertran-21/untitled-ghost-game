#include "Camera.h"

Camera::Camera() : DisplayObjectContainer() {}

Camera::~Camera(){}

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
    DisplayObjectContainer::update(pressedKeys, currState);
}

void Camera::changeScene(Scene* old_scene, Scene* new_scene){
    old_scene->isActive = false;
    new_scene->isActive = true;
}