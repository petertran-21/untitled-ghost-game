#include "Ghost.h"

Ghost::Ghost() : AnimatedSprite("Ghost"){

	this->type = "Ghost";
	this->id = "Ghost";
	this->subtype = GHOST_SUBTYPE;
	this->npc = NULL;
	
	this->position.x = 55;
	this->position.y = 200;
	this->width = 416;
	this->height = 454;
	// this->scaleX = 0.3;
	// this->scaleY = 0.3;
	this->pivot.x = this->width / 2;
	this->pivot.y = this->height / 2;

	//eventually replace the following with "recourses/PlayerSprites/"
	this->addSpriteSheet("./resources/grendel/Grendel_Idle_Sheet.png", "./resources/grendel/grendel_idle.xml", "idle", 3, 12, true);
	this->addSpriteSheet("./resources/grendel/Grendel_Move_Sheet.png", "./resources/grendel/grendel_move.xml", "move", 4, 12, true);
	
	this->play("move");
}

Ghost::~Ghost() {}

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
void Ghost::onCollision(DisplayObject* other){
	if(other->type == "Platform"){
		// Game::instance->collisionSystem.resolveCollision(this, other, this->x - oldX, this->y - oldY);	
		_yVel = 0;
		_standing=true;
	}
	else if(other->type == "Enemy"){
		if(!this->iFrames){
			this->onEnemyCollision((Enemy*)other);
		}
	}

}


void Ghost::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	AnimatedSprite::update(pressedKeys, currState);

	//run state machine
	Ghost::state_execute(pressedKeys, currState);

	oldY = this->position.y;
	oldX = this->position.x;

	/* handle iFrames if player was hit by enemy recently */
	if(this->iFrames){
		this->visible = this->iFrameCount%2 == 0;
		this->iFrameCount++;
		if(this->iFrameCount == this->numIFrames){
			this->iFrames = false;
			this->visible = true;
		}
	}

	//not in a state bc you should be able to do this ALWAYS to your heart's content :D
	if(Controls::pressBoo(pressedKeys, currState)) boo();
}

void Ghost::onEnemyCollision(Enemy* enemy){
	// this->health -= enemy->damage;
	this->initIFrames(120);
}

void Ghost::state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "GHOST: IDLE" << endl;
	}
	//anything that should always run while in this state
	this->play("Idle");

	//switch to moving
	if (Controls::holdRight(pressedKeys, currState) || 
	    Controls::holdLeft(pressedKeys, currState)  || 
		Controls::holdUp(pressedKeys, currState)    || 
		Controls::holdDown(pressedKeys, currState)  ){
			state_switch(ghost_states::Moving);
	}

	//switch to possession
	if (Controls::pressPossess(pressedKeys, currState)) state_switch(ghost_states::Possessing);
}

void Ghost::state_moving(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "GHOST: MOVING" << endl;
		movespeed = 4;
	}
	//anything that should always run while in this state

	// Movement arrow keys
	// Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	if(Controls::holdRight(pressedKeys, currState)){
		this->position.x += movespeed;
		this->facingRight = true;
		if(_standing){
			this->play("Run");
		}
	}
	else if(Controls::holdLeft(pressedKeys, currState)){
		this->position.x -= movespeed;
		this->facingRight = false;
		if(_standing){
			this->play("Run");
		}
	}

	if (Controls::holdUp(pressedKeys, currState)){
		this->position.y -= movespeed;
		if(_standing){
			this->play("Run");
		}
	}
	else if (Controls::holdDown(pressedKeys, currState)){
		this->position.y += movespeed;
		if(_standing){
			this->play("Run");
		}
	}	

	if (movespeed < 16) movespeed++;
	
	//slow down and change state
	if( !Controls::holdLeft(pressedKeys, currState)  && 
		!Controls::holdRight(pressedKeys, currState) &&
		!Controls::holdUp(pressedKeys, currState)    &&
		!Controls::holdDown(pressedKeys, currState)  ){
			state_switch(ghost_states::Idle);
	}

	//switch to possession
	if (Controls::pressPossess(pressedKeys, currState)) state_switch(ghost_states::Possessing);
}

void Ghost::state_possessing(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "GHOST: POSSESSING" << endl;

		//CHECK COLLISION WITH NPC HERE
		// if (colliding w/NPC) MainNPC* npc = npc we're colliding with;
		// else return;

		if (npc == NULL){
			state_switch(ghost_states::Idle);
			cout << "Yuck" << endl;
			return;
		}

		isPossessing = true;
		npc->is_possessed = true;
	}
	//anything that should always run while in this state

	if (isPossessing){
		this->alpha = 0; //replace with tweening effect later
		this->position.x = npc->position.x;
		this->position.y = npc->position.y - 10;
	}

	//wait for NPC to eject player
	if (npc->is_possessed == false){
		isPossessing = false;
		npc = NULL;
		state_switch(ghost_states::Idle);
	}

}

void Ghost::state_fizzle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
	if (state_new){
		//anything that should happen once, right at the start of the state
		cout << "GHOST: FIZZLE" << endl;
	}
	//anything that should always run while in this state

	//play dead animation and restart in regions hub or village
	this->play("Dead");
	//reset to idle state-->make reset function?
}

void Ghost::boo(){
	//play boo noise
	cout<< "boos"<<endl;
}

void Ghost::initIFrames(int numFrames){
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}

void Ghost::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

//STATE MACHINE METHODS
void Ghost::state_switch(ghost_states new_state){
    if (state != new_state){
        state_new = true;
        state = new_state;
        state_updated = true;
    }
}
void Ghost::state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    switch(state){
        case ghost_states::Idle:       Ghost::state_idle(pressedKeys, currState);       break;
		case ghost_states::Moving:     Ghost::state_moving(pressedKeys, currState);     break;
        case ghost_states::Possessing: Ghost::state_possessing(pressedKeys, currState); break;
		case ghost_states::Fizzle:	 Ghost::state_fizzle(pressedKeys, currState);     break;
    }
    if (state_updated) state_updated = false;
    else state_new = false;
}

void Ghost::resolve_collision(DisplayObject *obj){
	MainNPC* collider = dynamic_cast<MainNPC*>(obj);
	//check that collider is an NPC
	if (collider){
		npc = collider;
	}
}