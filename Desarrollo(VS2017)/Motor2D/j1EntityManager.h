#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "j1Module.h"
#include "p2Point.h"
#include "p2List.h"
#include "j1Animation.h"

class j1Entity;

enum class Entity_Class
{
	PLAYER,
	FLYING_ENEMY,
	GROUND_ENEMY,

	UNKNOWN
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	virtual bool Awake(pugi::xml_node& config);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2);
	virtual bool Load(pugi::xml_node& data);
	virtual bool Save(pugi::xml_node& data);

	//CREATION AND DESTRUCTION OF ENTITIES
	j1Entity* CreateEntity(Entity_Class type);
	virtual void DestroyEntity(j1Entity* delete_entity);

public:
	p2List<j1Entity*> entities;
	pugi::xml_node config;

};

#endif // !_ENTITY_MANAGER_H_