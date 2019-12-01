#include "j1Entity.h"
#include "j1Animation.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Skeleton.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Collision.h"



j1Entity::j1Entity(Types type)
{
	entity_type = type;
}

j1Entity:: ~j1Entity()
{}

bool j1Entity::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("posX").as_int();
	position.y = data.child("position").attribute("posY").as_int();
	return true;
}

bool j1Entity::Save(pugi::xml_node& data) const
{

	return true;
}


void j1Entity::Pushbacks() {}

void j1Entity::OnCollision(Collider* c1, Collider* c2) {}

void j1Entity::GetPosition() {}




