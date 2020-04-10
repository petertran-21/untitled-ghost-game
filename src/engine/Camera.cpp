#include "Camera.h"

Camera::Camera(){}

Camera::~Camera(){}

// Do not draw scenes that are "inactive."
void Camera::draw(AffineTransform &at){
    for (int i = 0; i < children.size(); i++){
        if (static_cast<Scene*>(children[i])->isActive) {
            children[i]->draw(at);
        }
    }
}

void Camera::changeScene(Scene* old_scene, Scene* new_scene){
    old_scene->isActive = false;
    new_scene->isActive = true;
}