#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
#include "j1Animation.h"
//#include "Globals.h"
#include "p2Point.h"
#include "p2Log.h"

struct SDL_Texture;

struct input {	
	bool pressing_A;
	bool pressing_S;
	bool pressing_D;
	bool pressing_W;
	bool pressing_lshift;
};

enum states {
	IDLE,
	DASH_RIGHT,
	DASH_LEFT,
    FORWARD,
	BACKWARD,
	JUMP,
	JUMP_FORWARD,
	JUMP_BACKWARD
};

struct PlayerInfo
{
	//ANIMATIONS NOT IMPLEMENTED
	Animation*		current_animation=&idle;
	Animation idle;
	Animation walk;
	Animation jump;
	Animation death;
	Animation voltereta;

    iPoint position;
	iPoint Initial_position;

	p2SString		Death_Effect;
	p2SString		Jump_Effect;

	pugi::xml_document playerdoc;
	pugi::xml_node playernode;

    input Input; 

	SDL_Rect		col;
	SDL_Texture*	Tex_Player;

	bool can_walk = true;
	float jump_time = 0.0f;
	bool injump = false;	
	bool canjump = false;  
	float player_velocity = 3.0f;
	float jumpvel = 7.0f;
	float gravity = 0.5f;
	bool GodMode;
	
	//STATES OF PLAYER MOVEMENT
    bool air = false;
	bool right = false; 
	bool left = false;

	bool looking_right = true;
	bool player_flip = false;

	//COLLIDERS NOT IMPLEMENTED
	Collider * player = nullptr;
	Collider* colliders_1 = nullptr;
	
	bool showcolliders = false;
};

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update();
	bool CleanUp();


	//LOADING AND SAVING OPTIONS
	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

public:
	
	PlayerInfo playerinfo;
	p2SString file;
	bool keyup = true;
	SDL_Texture* graphics = nullptr;
	//STATES DOEN'T WORK INSIDE PLAYERINFO. SO THATS WHY ITS IN HERE
	states state;
};

#endif