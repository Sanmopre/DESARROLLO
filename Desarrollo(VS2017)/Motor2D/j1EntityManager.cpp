#include "j1EntityManager.h"
#include "j1Player.h"
#include "Brofiler/Brofiler.h"

j1EntityManager::j1EntityManager()
{
}

j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Awake(pugi::xml_node &)
{
	return true;
}

bool j1EntityManager::Start()
{
	BROFILER_CATEGORY("EntityManager_Start", Profiler::Color::BurlyWood)

		for (p2List_item<j1Entity*>* it = Entity_List.start; it != nullptr; it = it->next)
		{
			it->data->Start();
		}

	return true;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("EntityManager_PreUpdate", Profiler::Color::Coral)

		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			if (array[i].type != Type::NULL_ENTITY)
			{
				Summon_Entity(array[i]);
				array[i].type = Type::NULL_ENTITY;
			}
		}

	return true;
}

bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("EntityManager_Update", Profiler::Color::Aqua)

		for (p2List_item<j1Entity*>* it = Entity_List.start; it != nullptr; it = it->next)
		{
			it->data->Update(dt);
		}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("EntityManager_PostUpdate", Profiler::Color::Magenta)

		for (p2List_item<j1Entity*>* it = Entity_List.start; it != nullptr; it = it->next)
		{
			it->data->PostUpdate();
		}

	return true;
}

bool j1EntityManager::CleanUp()
{
		bool ret = true;

	return ret;
}

void j1EntityManager::OnCollision(Collider * c1, Collider * c2)
{

}

j1Entity* j1EntityManager::Entity_Manager(Type type, float x, float y)
{
	j1Entity* ret = nullptr;
	switch (type)
	{
	case Type::PLAYER:
		break;

	case Type::GROUNDED_ENEMY:
		break;

	case Type::FLYING_ENEMY:
		break;
	}

	return ret;
}

void j1EntityManager::Create_Entity(Type type, float x, float y)
{
	switch (type)
	{
	case Type::PLAYER:
		break;

	case Type::GROUNDED_ENEMY:
		break;

	case Type::FLYING_ENEMY:
		break;
	}
}


void j1EntityManager::Add_Entity(float x, float y, Type type)
{
	for (int i = 0; i < MAX_ENTITIES; ++i)
	{
		if (array[i].type == Type::NULL_ENTITY)
		{
			array[i].type = type;
			array[i].position.x = x;
			array[i].position.y = y;
			break;
		}
	}
}


void j1EntityManager::Summon_Entity(const info & info)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (array[i].type != Type::NULL_ENTITY)
		{
			j1Entity* ret = nullptr;

			switch (info.type) {
			case Type::PLAYER:
				Entity_List.add(ret);
				break;
			case Type::GROUNDED_ENEMY:
				Entity_List.add(ret);
				break;
			case Type::FLYING_ENEMY:
				Entity_List.add(ret);
				break;
			}

			ret->Start();

			break;
		}
	}
}

bool j1EntityManager::Load(pugi::xml_node &)
{
	return true;
}

bool j1EntityManager::Save(pugi::xml_node &) const
{
	return true;
}
