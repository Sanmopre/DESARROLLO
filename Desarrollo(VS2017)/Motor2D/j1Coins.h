#ifndef  __j1COINS_H__
#define __j1COINS_H__

#include "j1Entity.h"
#include "p2Point.h"
#include "p2List.h"

struct SDL_Texture;
struct Collider;

enum ENTITY_TYPE;

struct SDL_Texture;
struct Collider;

class j1Coins : public j1Entity
{
public:

	j1Coins();
	j1Coins(iPoint pos);
	// Destructor
	virtual ~j1Coins();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called each loop iteration
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void Coins_Position();

	// Called before quitting
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	iPoint			position;
	SDL_Texture*	TEX = nullptr;
	bool			Collected = false;
	int				CoinCount=0;
	bool			Grounded = true;
	bool			Near_Player = false;

	//ANIMATIONS
	Animation*		current_animation = nullptr;
	Animation		idle;
	

	void Pushbacks();
	
private:

	p2SString		folder;
	p2SString		texture_path;
	pugi::xml_node	node;

};

#endif