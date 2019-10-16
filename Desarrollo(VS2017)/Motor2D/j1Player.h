#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
#include "j1Animation.h"
//#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

enum jump
{
	JUMP_DOWN = -1,
	JUMP_NOT = 0,
	JUMP_UP = 1
};

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update();
	bool CleanUp();

public:

	p2SString file;
	int hp = 100;
	jump jumping = JUMP_NOT;
	bool keyup = true;

	Animation* current_animation = &idle;
	//COLLIDERS NOT IMPLEMENTED
	
	Collider * player = nullptr;
	Collider * melee = nullptr;

	SDL_Texture* graphics = nullptr;

	//ANIMATIONS NOT IMPLEMENTED
	
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation jump;

	iPoint position;

};

#endif