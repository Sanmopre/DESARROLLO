#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
#include "j1Animation.h"
//#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

struct PlayerInfo
{
	//ANIMATIONS NOT IMPLEMENTED
	Animation*		current_animation=&idle;
	Animation idle;
	Animation walk;
	Animation jump;

    iPoint position;
	iPoint Initial_position;

	p2SString		Death_Effect;
	p2SString		Jump_Effect;

	pugi::xml_document playerdoc;
	pugi::xml_node playernode;

	SDL_Rect		col;
	iPoint			colOffset;
	SDL_Texture*	Tex_Player;
    bool grounded;
	bool platformdrop;
	float jump_time = 0.0f;
	bool injump = false;	
	bool canjump = false;  
	int jumpvel;
	float gravity;
	bool player_flip;


	
	//COLLIDERS NOT IMPLEMENTED
	Collider * player = nullptr;
	Collider* colliders_1 = nullptr;
	
	bool showcolliders = false;
};

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
	PlayerInfo playerinfo;
	p2SString file;
	jump jumping = JUMP_NOT;
	bool keyup = true;

	



	SDL_Texture* graphics = nullptr;
	
	iPoint position;

};

#endif