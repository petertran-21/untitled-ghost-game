#include "Dot.h"

Dot::Dot( int x, int y ) : DisplayObjectContainer()
{
    position.x = x;
    position.y = y;

    velocityX = 0;
    velocityY = 0;

    this->loadTexture( "./resources/particles/dot.bmp" );

    for( int i = 0; i < TOTAL_PARTICLES; i++ )
    {
        /**
         * IMPORTANT
         * Particle is a child of Dot, therefore the position
         * is relative to Dot. Coodinates ( 0, 0 ) centers it on the parent.
         */
        this->addChild( new Particle( 0, 0, this->width, this->height ) );
    }
}

Dot::~Dot()
{
    /**
     * Particle destruction is handled by the 
     * base-class destructor DisplayObjectContainer.
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