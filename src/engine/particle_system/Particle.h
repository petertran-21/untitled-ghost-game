#ifndef PARTICLE_H
#define PARTICLE_H

#include "DisplayObject.h"
#include "Controls.h"
#include "Ghost.h"

using namespace std;

/**
 * Author: Bradley Knaysi
 * File: Particle.h
 * Created: April 14th, 2020
 * 
 * Influenced by Lazy Foo' Productions tutorial on
 * particle engines.
 */
class Particle : public DisplayObject
{
    public:

        Particle();
        ~Particle();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

    private:

        //Range that particles can spawn within
        int horizontal_domain;
        int vertical_domain;

        //Number of frames since creation
        int age;

        //Number of frames before death
        static const int LIFE_SPAN = 100;

        //Effects the speed of particles
        static const int UPDATE_RATE = 10;

        //Effects the particle trail length when Ghost moves
        static const int TRAIL_LENGTH = UPDATE_RATE;

        //Allows us to check before loading texture
        bool isTextureSet;
};

#endif