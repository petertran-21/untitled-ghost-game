#include "Particle.h"

Particle::Particle() : DisplayObject()
{
    type = "Particle";
    position.x = 0;
    position.y = 0;
    horizontal_domain = 0;
    vertical_domain = 0;
    alpha = 140;
    scaleX = 0.55;
    scaleY = 0.55;
    isTextureSet = false;

    //Randomize age so deaths occur async
    age = rand() % LIFE_SPAN;
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

    //Creates a trailing effect when the Ghost moves.
    if( parent->parent != NULL )
    {
        if( parent->parent->subtype == GHOST_SUBTYPE )
        {
            bool reversed = ((Ghost*) parent->parent)->reverse_controls;
            int trail_length = TRAIL_LENGTH;
            if( reversed )
            {
                trail_length = -trail_length;
            }
            if( Controls::holdLeft( pressedKeys, currState ) )
            {
                position.x += trail_length;
            }
            if( Controls::holdRight( pressedKeys, currState ) )
            {
                position.x -= trail_length;
            }
            if ( Controls::holdUp( pressedKeys, currState ) )
            {
                position.y += trail_length;
            }
            if ( Controls::holdDown( pressedKeys, currState ) )
            {
                position.y -= trail_length;
            }
        }
    }

    //Frequency of updates
    if( age % UPDATE_RATE == 0 )
    {
        //Simulate random movement
        position.x = (rand() % horizontal_domain) - ((int) horizontal_domain / 2) - 5;
        position.y = (rand() % vertical_domain) - ((int) vertical_domain / 2) + 13;
    }
    
    DisplayObject::update( pressedKeys, currState );
}

void Particle::draw( AffineTransform &at )
{
    if( isTextureSet == false )
    {
        //Assign texture by type of grandparent
        switch( parent->parent->subtype )
        {
            case GHOST_SUBTYPE: this->loadTexture("./resources/particles/grendel_particle.png" ); break;
        }
        isTextureSet = true;
    }

    DisplayObject::draw( at );
}