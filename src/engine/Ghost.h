#ifndef GHOST_H
#define GHOST_H
#define GHOST_SUBTYPE 4
#include "AnimatedSprite.h"
#include "Enemy.h"
#include "Controls.h"
#include "MainNPC.h"

using namespace std;

enum class ghost_states {Idle, Moving, Possessing, Fizzle};

class Ghost : public AnimatedSprite{

public:
	Ghost();
	~Ghost();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	void onEnemyCollision(Enemy* enemy);
	virtual void onCollision(DisplayObject* other);
	void boo();

	MainNPC* npc;

	/* Health and such */
	int health = 100;
	int maxHealth = 100;
	bool reverse_controls = false;
	int reverse_controls_timer = 0;
	int reverse_controls_max = 400;

	float movespeed = 4;

	ghost_states state = ghost_states::Idle;
	bool state_new = true;
	bool state_updated = false;

	void state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	void state_switch(ghost_states new_state);
	void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	void state_moving(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	void state_possessing(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	void state_fizzle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;

	/* Current Enemy player is engaging with*/
	Enemy* curEnemy = NULL;

	void resolve_collision(DisplayObject *obj);
	bool getIsPosessing(){return isPossessing;};
	void setIsPossessing(bool p){isPossessing = p;};

private:

	bool isPossessing = false;

	int oldX=0, oldY=0;

	int _jumpVel = -15;

	/* Falling variables */
	bool _standing = false;
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	int _yVel = 0;
	bool flipH = false;

	void initIFrames(int numFrames);

};

#endif