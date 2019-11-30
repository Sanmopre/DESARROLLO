#ifndef __j1SKELETON_H__
#define __j1SKELETON_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Animation.h"
#include "j1Module.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

enum Skeleton_States
{
	SKELETON_FORWARD,
	SKELETON_BACKWARD,
	SKELETON_DEATH,
};

class j1Skeleton : public j1Entity
{
public:

	j1Skeleton();
	j1Skeleton(iPoint pos);

	// Destructor
	virtual ~j1Skeleton();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool pathfinding_ground();


	// Called each loop iteration

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void Skeleton_State(Skeleton_States state);
	void Skeleton_Position();

	// Called before quitting
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);


	iPoint			position;
	SDL_Texture*	skeletonTex = nullptr;
	bool			Looking_Forward = true;
	bool			Alive = true;
	bool			Grounded = true;
	
	bool			Near_Player = false;

	//ANIMATIONS
	Animation*		current_animation = nullptr;
	Animation		walking;
	Animation		walking2;
	Animation		death;
	Animation		death2;

	//SPEED
	float			SpeedX;
	float			SpeedY;
	float			gravity;
	fPoint		    vel;

	//COLLIDERS
	Collider*	skeletonCollider = nullptr;


	void Pushbacks();

	Skeleton_States state = SKELETON_FORWARD;


private:

	p2SString		folder;
	p2SString		texture_path;
	pugi::xml_node	node;
};

#endif