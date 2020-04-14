#include "Particle.h"

Particle::Particle( int x, int y ) : DisplayObject()
{
    //Set offsets
    position.x = x - 5 + ( rand() % 25 );
    position.y = y - 5 + ( rand() % 25 );

    //Init animation
    frame = rand() % 5;

    //Set transparency
    alpha = 192;

    //Randomly assign texture
    switch( rand() % 3 )
    {
        /**
        * TODO, this is broken, you must load these .bmp files differently
        */
        case 0: this->loadTexture( "./resources/particles/38_particle_engines/red.bmp" ); break;
        case 1: this->loadTexture( "./resources/particles/38_particle_engines/blue.bmp" ); break;
        case 2: this->loadTexture( "./resources/particles/38_particle_engines/green.bmp" ); break;
    }
}

Particle::~Particle() 
{

}

void Particle::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState )
{
    frame++;
    DisplayObject::update( pressedKeys, currState );
}

void Particle::draw( AffineTransform &at )
{
    DisplayObject::draw( at );
}