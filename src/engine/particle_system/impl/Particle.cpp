#include "Particle.h"

Particle::Particle() : DisplayObject()
{
    position.x = 0;
    position.y = 0;
    x_range = 0;
    y_range = 0;
    frame = 0;
    alpha = 192;

    //Randomly assign texture
    switch( rand() % 4 )
    {
        case 0: this->loadTexture( "./resources/particles/red.bmp" ); break;
        case 1: this->loadTexture( "./resources/particles/blue.bmp" ); break;
        case 2: this->loadTexture( "./resources/particles/green.bmp" ); break;
        case 3: this->loadTexture( "./resources/particles/shimmer.bmp" ); break;
    }
}

Particle::~Particle() 
{

}

void Particle::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState )
{   
    //Set spawn range to parent dimensions
    if( parent != NULL )
    {
        x_range = parent->width;
        y_range = parent->height;
    }
    
    //Update counter
    frame++;

    //Slow particle movement
    if( frame % 2 == 0 )
    {
        //Simulate random movement
        position.x = (rand() % x_range) - ((int) x_range / 2);
        position.y = (rand() % y_range) - ((int) y_range / 2);
    }
    
    DisplayObject::update( pressedKeys, currState );
}

void Particle::draw( AffineTransform &at )
{
    DisplayObject::draw( at );
}