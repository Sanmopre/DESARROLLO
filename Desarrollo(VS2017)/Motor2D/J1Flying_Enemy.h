#ifndef __j1FLYING_ENEMY_H__
#define __j1FLYING_ENEMY_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Animation.h"
#include "j1Module.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

enum Flying_Enemy_States
{
	FLYING_ENEMY_FORWARD,
	FLYING_ENEMY_BACKWARD,
	FLYING_ENEMY_DEATH,
};

class j1Flying_Enemy : public j1Entity
{
public:

	j1Flying_Enemy();
	j1Flying_Enemy(iPoint pos);

	// Destructor
	virtual ~j1Flying_Enemy();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();


	// Called each loop iteration

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void Flying_Enemy_State(Flying_Enemy_States state);
	void Flying_Enemy_Position();

	// Called before quitting
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);


	iPoint			position;
	SDL_Texture*	Flying_Enemy_Tex = nullptr;
	bool			Looking_Forward = true;
	bool			Alive = true;
	bool			Grounded = true;

	//ANIMATIONS
	Animation*		current_animation = nullptr;
	Animation		walking;
	Animation		death;

	//SPEED
	float			SpeedX;
	float			SpeedY;
	float			gravity;
	fPoint		    vel;

	//COLLIDERS
	Collider*	Flying_Enemy_Collider = nullptr;

	void Pushbacks();

	Flying_Enemy_States state = FLYING_ENEMY_FORWARD;


private:

	p2SString		folder;
	p2SString		texture_path;
	pugi::xml_node	node;
};

#endif
