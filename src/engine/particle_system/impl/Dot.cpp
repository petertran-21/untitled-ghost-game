#include "Dot.h"

Dot::Dot() : DisplayObjectContainer()
{
    type = "Dot";
    position.x = 0;
    position.y = 0;
    width = 0;
    height = 0;

    //Create particles
    for( int i = 0; i < TOTAL_PARTICLES; i++ )
    {
        this->addChild( new Particle() );
    }
}

Dot::~Dot()
{

}

void Dot::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState )
{
    //Match parent dimensions
    if( parent != NULL )
    {
        width = parent->width * PARENT_TO_DOT_RATIO;
        height = parent->height * PARENT_TO_DOT_RATIO;
    }

    //Replace destroyed particles
    while( this->numChildren() < TOTAL_PARTICLES )
    {
        this->addChild( new Particle() );
    }

    DisplayObjectContainer::update( pressedKeys, currState );
}

void Dot::draw( AffineTransform &at )
{
    DisplayObjectContainer::draw( at );
}