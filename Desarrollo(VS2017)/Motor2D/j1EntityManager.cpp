#include "j1EntityManager.h"
#include "j1Entity.h"
#include "j1Player.h"
#include "j1Skeleton.h"
#include "J1Flying_Enemy.h"
#include "j1Scene.h"
#include "j1Animation.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "PugiXml/src/pugixml.hpp"
#include "Brofiler/Brofiler.h"

j1EntityManager::j1EntityManager()
{

}

j1EntityManager::~j1EntityManager()
{}

bool j1EntityManager::Awake(pugi::xml_node& config) {
	node = config;
	return true;
}

bool j1EntityManager::Start()
{
	return true;
}

bool j1EntityManager::PreUpdate()
{
	return true;
}

bool j1EntityManager::Update(float dt)
{
	/*for (p2List_item<j1Entity*>* entity = entities.start; entity; entity = entity->next)
	{
			entity->data->Update(dt);

	}*/
	return true;
}

bool j1EntityManager::PostUpdate()
{
	return true;
}

bool j1EntityManager::CleanUp()
{
	return true;
}

bool j1EntityManager::Load(pugi::xml_node& data)
{
	return true;
}

bool j1EntityManager::Save(pugi::xml_node& data) const
{
	return true;
}

j1Entity* j1EntityManager::Summon_Entity(j1Entity::Types type, iPoint pos)
{
	j1Entity* ret = nullptr;

	switch (type)
	{
	case j1Entity::Types::PLAYER:
		ret = new j1Player(pos);
		break;

		
	case j1Entity::Types::SKELETON:
		ret = new j1Skeleton(pos);
		break;

	case j1Entity::Types::FLYING_ENEMY:

		ret = new j1Flying_Enemy(pos);
		break;
	}

	if (ret != nullptr)
	{
		entities.add(ret);
		entities.end->data->Awake(node);
		entities.end->data->Start();
	}
	return ret;
}

void j1EntityManager::Destroy_Entity(j1Entity* entity)
{
	delete entity;
}

void j1EntityManager::Destroy_Entities()
{
	p2List_item<j1Entity*>* entityList = entities.start;
	while (entityList)
	{
		entities.del(entityList);
		entityList = entityList->next;
	}
}

j1Entity* j1EntityManager::Get_Player()
{

	p2List_item<j1Entity*>* entities_list = entities.start;
	while (entities_list) {
		if (entities_list->data->name == "player") {
			return entities_list->data;
		}
		entities_list = entities_list->next;
	}
	return NULL;
}