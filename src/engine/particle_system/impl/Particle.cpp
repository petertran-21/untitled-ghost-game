#include "Particle.h"

Particle::Particle() : DisplayObject()
{
    type = "Particle";
    position.x = 0;
    position.y = 0;
    horizontal_domain = 0;
    vertical_domain = 0;
    alpha = 192;

    //Randomize age so deaths occur async
    age = rand() % LIFE_SPAN;

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
    //Set spawn range
    if( parent != NULL )
    {
        horizontal_domain = parent->width;
        vertical_domain = parent->height;
    }

    //Update age
    age++;

    /**
     * SUFFICIENT FOR DEMO
     * 
     * Creates a trailing effect when the Ghost moves.
     * It works great but need to find a better way b/c
     * this would move all particles on the screen, not
     * just the ones on the Ghost.
     */
    if( Controls::holdLeft( pressedKeys, currState ) )
    {
        position.x += TRAIL_LENGTH;
    }
    if( Controls::holdRight( pressedKeys, currState ) )
    {
        position.x -= TRAIL_LENGTH;
    }
    if ( Controls::holdUp( pressedKeys, currState ) )
    {
        position.y += TRAIL_LENGTH;
    }
    if ( Controls::holdDown( pressedKeys, currState ) )
    {
        position.y -= TRAIL_LENGTH;
    }

    //Frequency of updates
    if( age % UPDATE_RATE == 0 )
    {
        //Simulate random movement
        position.x = (rand() % horizontal_domain) - ((int) horizontal_domain / 2);
        position.y = (rand() % vertical_domain) - ((int) vertical_domain / 2);
    }
    
    DisplayObject::update( pressedKeys, currState );
}

void Particle::draw( AffineTransform &at )
{
    DisplayObject::draw( at );
}