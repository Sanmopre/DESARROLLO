#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Defs.h"
#include "p2List.h"
#include "p2Point.h"
#include "j1Entity.h"

#define MAX_ENTITIES 50

struct SDL_Texture;
class j1Entity;
class j1Player;


enum Type
{
	PLAYER,
	GROUNDED_ENEMY,
	FLYING_ENEMY,
	NULL_ENTITY
};

struct info
{
	Type type = Type::NULL_ENTITY;
	fPoint position;
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	j1Entity* Entity_Manager(Type type, float x = 0, float y = 0);	
	void Add_Entity(float x, float y, Type type);
	void Create_Entity(Type type, float x = 0, float y = 0);
	void Summon_Entity(const info& info);
	
	void OnCollision(Collider* c1, Collider* c2);

public:

	p2List<j1Entity*>	Entity_List;
	j1Player*			j1Player = nullptr;
	info			array[MAX_ENTITIES];

};

#endif 
