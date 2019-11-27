#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "j1EntityManager.h"
#include "p2Point.h"
#include "j1Animation.h"

struct Collider;


enum Type;

class j1Entity
{
public:
	j1Entity(int x, int y, Type type);

	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2) {};

	virtual bool Load(pugi::xml_node&);
	virtual bool Save(pugi::xml_node&);

public:

	Type type;
	fPoint position;

	Collider* body = nullptr;
	Collider* feet = nullptr;
};

#endif // __ENTITY_H__
