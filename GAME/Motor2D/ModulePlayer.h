#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
//#include "Animation.h"
//#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

enum jump
{
	JUMP_DOWN = -1,
	JUMP_NOT = 0,
	JUMP_UP = 1
};

class ModulePlayer : public j1Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	bool Update();
	bool CleanUp();

public:

	int hp = 100;
	jump jumping = JUMP_NOT;
	bool keyup = true;

	// Animation* current_animation = &idle;
	//COLLIDERS NOT IMPLEMENTED
	/*
	Collider * player = nullptr;
	Collider * melee = nullptr;
*/
	SDL_Texture* graphics = nullptr;

	//ANIMATIONS NOT IMPLEMENTED
	/*
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
*/
	iPoint position;

};

#endif