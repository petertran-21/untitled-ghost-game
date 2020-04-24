#ifndef MAINNPC_H
#define MAINNPC_H

#include "AnimatedSprite.h"
#include "DisplayObjectContainer.h"
#include "MainCollectibles.h"
#include "Controls.h"
#include "EnvObjImports.h"
#include "CollectiblesImports.h"
#include "NPCObjImports.h"

using namespace std;

enum class npc_states {Idle, Possessed, Moving, Ability};

class MainNPC : public AnimatedSprite{
    
    public:
        MainNPC();
        MainNPC(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	    virtual void draw(AffineTransform &at);
        //virtual void onCollision(DisplayObject* other);

        bool is_possessed = false;
        bool can_move = true;

        directions dir = S;
        SDL_Point abilityPt;
        int grid_size = 100;
        void move_on_grid(directions direction, int distance);
        
        int cooldown_max = 30;
        int cooldown_timer = 0;
        bool reverse_controls = false;
        int reverse_controls_timer = 0;
        int reverse_controls_max = 400;

        npc_states state = npc_states::Idle;
        bool state_new = true;
        bool state_updated = false;

        void state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_switch(npc_states new_state);
        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_possessed(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_moving(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        virtual void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) = 0;

        virtual void resolve_collision(DisplayObject *obj);
        virtual void resolve_adjacency(DisplayObject *obj, int status);
        virtual void resolve_collectible_collision(DisplayObject *obj, DisplayObjectContainer* collideContainer, DisplayObjectContainer* drawContainer);
        DisplayObjectContainer* collisionContainer;
        DisplayObjectContainer* drawingContainer;
   
};

#endif