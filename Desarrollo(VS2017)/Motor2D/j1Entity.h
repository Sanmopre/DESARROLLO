#ifndef _ENTITY_H
#define _ENTITY_H

#include "j1Module.h"
#include "p2Point.h"
#include "p2Log.h"

enum class Types
{
	PLAYER,
	GROUNDED_ENEMY,
	AIR_ENEMY,
	NULL_ENTITY
};

class Entity :public j1Module
{
public:
	Entity(Types type) {}

	virtual ~Entity() {}

	virtual bool Awake(pugi::xml_node&) {return true;}

	virtual bool Start() {return true;}

	virtual bool PreUpdate() {return true;}

	virtual bool Update(float dt) {return true;}

	virtual bool CleanUp() {return true;}

	virtual bool Load(pugi::xml_node&) {return true;}

	virtual bool Save(pugi::xml_node&) const {return true;}

public:
	Types entity_type;
	iPoint position;

};

#endif // !ENTITY_H
