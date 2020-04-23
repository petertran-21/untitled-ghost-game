#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() : DisplayObjectContainer()
{
    type = "ParticleEmitter";
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

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState )
{
    //Match parent dimensions
    if( parent != NULL )
    {
        //Center with parent
        position.x = (0 + parent->width) / 2;
        position.y = (0 + parent->height) / 2;
        
        width = parent->width;
        height = parent->height;
    }

    DisplayObjectContainer::update( pressedKeys, currState );
}

void ParticleEmitter::draw( AffineTransform &at )
{
    DisplayObjectContainer::draw( at );
}