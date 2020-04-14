#include "Dot.h"

Dot::Dot( int x, int y ) : DisplayObjectContainer()
{
    position.x = x;
    position.y = y;

    velocityX = 0;
    velocityY = 0;

    /**
     * TODO, this is broken, you must load these .bmp files differently
     */
    this->loadTexture( "./resources/particles/38_particle_engines/dot.bmp" );

    for( int i = 0; i < TOTAL_PARTICLES; i++ )
    {
        this->addChild( new Particle( x, y ) );
    }
}

Dot::~Dot()
{
    /**
     * Particle destruction is handled by the base-class destructor DisplayObjectContainer.
     */
}

void Dot::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState )
{
    DisplayObjectContainer::update( pressedKeys, currState );
}

void Dot::draw( AffineTransform &at )
{
    DisplayObjectContainer::draw( at );
}