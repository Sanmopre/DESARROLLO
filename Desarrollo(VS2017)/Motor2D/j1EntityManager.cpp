#include "j1EntityManager.h"


EntityManager::EntityManager()
{
	name.create("entity_manager");
	//Player = (j1Player*)CreateEntity(Types::player);
}

//Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& a)
{
	for (unsigned int i = 0; i < entities.count(); i++)
	{
		entities.At(i)->data->Awake(a.child(entities.At(i)->data->name.GetString()));
	}
	return true;
}

// Called before the first frame
bool EntityManager::Start()
{
	for (unsigned int i = 0; i < entities.count(); i++)
	{
		entities.At(i)->data->Start();
	}
	return true;
}

// Called each loop iteration
bool EntityManager::PreUpdate()
{
	for (unsigned int i = 0; i < entities.count(); i++)
	{
		entities.At(i)->data->PreUpdate();
	}
	return true;
}

// Called each loop iteration
bool EntityManager::Update(float dt)
{
	for (unsigned int i = 0; i < entities.count(); i++)
	{
		entities.At(i)->data->Update(dt);
	}
	return true;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	for (int i = entities.count() - 1; i >= 0; i--)
	{
		entities.del(entities.At(i));
	}
	entities.clear();
	return true;
}

//Called when loading the game
bool EntityManager::Load(pugi::xml_node& n)
{
	for (unsigned int i = 0; i < entities.count(); i++)
	{
		entities.At(i)->data->Load(n.child(entities.At(i)->data->name.GetString()));
	}
	return true;
}

//Called when saving the game
bool EntityManager::Save(pugi::xml_node& s) const
{
	for (unsigned int i = 0; i < entities.count(); i++)
	{
		entities.At(i)->data->Save(s.append_child(entities.At(i)->data->name.GetString()));
	}
	return true;
}

//Called when creating a new Entity
Entity* EntityManager::CreateEntity(Types type)
{
	static_assert(Types::NULL_ENTITY == (Types)3, "Types need update");
	Entity* ret = nullptr;
	switch (type)
	{
	case Types::PLAYER:
		//ret = new j1Player(Types::PLAYER);
		break;
	case Types::GROUNDED_ENEMY:
		break;
	case Types::AIR_ENEMY:
		break;
	}

	if (ret != nullptr)
	{
		entities.add(ret);
	}
	return ret;
}

//Called when deleting a new Entity
bool EntityManager::DeleteEntity(Entity* e)
{
	int n = entities.find(e);
	if (n == -1)return false;
	else
	{
		entities.del(entities.At(n));
		return true;
	}
}