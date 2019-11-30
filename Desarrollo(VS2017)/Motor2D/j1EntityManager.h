#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "j1Module.h"
#include "j1Entity.h"
#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"

struct SDL_Texture;

class j1EntityManager : public j1Module
{
public:
	j1EntityManager();
	~j1EntityManager();
	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	j1Entity* Get_Player();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	j1Entity* Summon_Entity(j1Entity::Types type, iPoint pos);
	void Destroy_Entity(j1Entity* entity);
	void Destroy_Entities();

	pugi::xml_node node;
	p2List<j1Entity*> entities;
};


#endif