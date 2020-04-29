#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "DisplayObjectContainer.h"
#include "Particle.h"

using namespace std;

enum biomes { DEFAULT, Beach, Forest };

/**
 * Author: Bradley Knaysi
 * File: ParticleEmitter.h
 * Created: April 14th, 2020
 * 
 * Influenced by Lazy Foo' Productions tutorial on
 * particle engines.
 */
class ParticleEmitter : public DisplayObjectContainer
{
    public:

        ParticleEmitter();
        ~ParticleEmitter();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

        //Biome determines particle look
        void setBiome( string sceneFilePath );
        biomes biome = DEFAULT;

    private:

        //Total number of particles
        static const int TOTAL_PARTICLES = 20;

        //ParticleEmitter to parent ratio
        const double PARENT_TO_EMITTER_RATIO = 0.5;
};

#endif