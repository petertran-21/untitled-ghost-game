#include "Particle.h"

Particle::Particle() : DisplayObject()
{
    position.x = 0;
    position.y = 0;
    x_range = 0;
    y_range = 0;
    alpha = 192;

    //Randomize frame so particles die randomly
    frame = rand() % LIFE_SPAN;

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

    //Kill old particles (creates a "trailing" effect)
    if( frame > LIFE_SPAN )
    {
        ((DisplayObjectContainer*) this->parent)->removeImmediateChild(this);
    }

    //HANDLE MOVEMENTS
    int x_trail = 0;
    int y_trail = 0;
    if( Controls::holdLeft( pressedKeys, currState ) )
    {
        x_trail = TRAIL_LENGTH;
    }
    if( Controls::holdRight( pressedKeys, currState ) )
    {
        x_trail = -TRAIL_LENGTH;
    }
    if ( Controls::holdUp( pressedKeys, currState ) )
    {
        y_trail = TRAIL_LENGTH;
    }
    if ( Controls::holdDown( pressedKeys, currState ) )
    {
        y_trail = -TRAIL_LENGTH;
    }

    //Slow particle movement
    if( frame % 30 == 0 )
    {
        //Simulate random movement
        position.x = (rand() % x_range) - ((int) x_range / 2) + x_trail;
        position.y = (rand() % y_range) - ((int) y_range / 2) + y_trail;
    }
    
    DisplayObject::update( pressedKeys, currState );
}

void Particle::draw( AffineTransform &at )
{
    DisplayObject::draw( at );
}