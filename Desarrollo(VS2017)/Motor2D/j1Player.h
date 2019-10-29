#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"
#include "p2Log.h"

struct SDL_Texture;

struct input {	
	bool pressing_A;
	bool pressing_S;
	bool pressing_D;
	bool pressing_W;
	bool pressing_SPACE;
	bool pressing_lshift;
};

enum states {
	IDLE,
	DASH,
    FORWARD,
	BACKWARD,
	JUMP,
	JUMP_FORWARD,
	JUMP_BACKWARD
};

struct PlayerInfo
{
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

	//PLAYER, AND WORLD MAX VELOCITIES
	float			World_Gravity = 0.05;
	float			Speed_X = 0.5;
	float			Speed_Y = 0.6;
	float			Dash_Speed = 3.5;
	float			Reducction_Speed = 0.25;
	float		    MAX_X = 2.0;
	float			MAX_Y = 8.0;
	float		    MAX_JUMP = 5.0;
	fPoint		    velocity;

	bool            Looking_Forward = true;
	bool			Can_Input = true;
	bool			Alive = true;
	bool			Dash = false;
	bool            Grounded = true;
	bool            God_Mode = false;

	bool showcolliders = false;
	Collider * player = nullptr;
	Collider* colliders_1 = nullptr;
};

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();


	//PLAYER STATE MANAGER
	void Player_Position();
	void Player_State_Machine();
	void Set_Player_State(states state);
	void Restart();



	//LOADING AND SAVING OPTIONS
	bool Save(pugi::xml_node& data) const;
	bool Load(pugi::xml_node& data);

public:
	
	PlayerInfo playerinfo;
	input Input;
	p2SString file;
	bool keyup = true;
	SDL_Texture* graphics = nullptr;
	//STATES DOEN'T WORK INSIDE PLAYERINFO. SO THATS WHY ITS IN HERE
	states state;

	
};

#endif