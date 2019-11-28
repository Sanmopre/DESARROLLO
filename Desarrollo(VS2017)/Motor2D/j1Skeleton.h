#ifndef __j1Skeleton_H__
#define __j1Skeleton_H__

#include "j1Entity.h"
#include "j1Animation.h"
#include "p2Point.h"
#include "j1EntityManager.h"
#include "p2Log.h"
#include "j1Pathfinding.h"


enum Type;
struct SDL_Texture;
struct Collider;

class j1Skeleton : public j1Entity
{
public:
	j1Skeleton(int x, int y, Type type);;
	~j1Skeleton();
	virtual bool Start();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual void OnCollision(Collider* c1, Collider*c2);
	virtual bool Load(pugi::xml_node&);
	virtual bool Save(pugi::xml_node&);


};

#endif