#include "Particle.h"

Particle::Particle( int x, int y ) : DisplayObject()
{
    //Set offsets
    position.x = x - 5 + ( rand() % 25 );
    position.y = y - 5 + ( rand() % 25 );

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