#include "Particle.h"

Particle::Particle( int x, int y, int x_range, int y_range ) : DisplayObject()
{
    /**
     * IMPORTANT
     * This randomly sets a Particle's initial position within 
     * the limits { -range/2, ... 0, ..., range/2 }
     */
    position.x = x + (rand() % x_range) - ((int) x_range / 2);
    position.y = y + (rand() % y_range) - ((int) y_range / 2);

    //Save ranges
    this->x_range = x_range;
    this->y_range = y_range;

    //Set transparency
    alpha = 192;

    //Randomly assign texture
    switch( rand() % 3 )
    {
        case 0: this->loadTexture( "./resources/particles/red.bmp" ); break;
        case 1: this->loadTexture( "./resources/particles/blue.bmp" ); break;
        case 2: this->loadTexture( "./resources/particles/green.bmp" ); break;
    }
}

Particle::~Particle() 
{

}

void Particle::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState )
{   
    DisplayObject::update( pressedKeys, currState );
}

void Particle::draw( AffineTransform &at )
{
    DisplayObject::draw( at );
}