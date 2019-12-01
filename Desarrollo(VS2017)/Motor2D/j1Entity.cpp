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
#include "j1Pathfinding.h"


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

void j1Entity::Pathfind(int range, j1Entity* player) {

	if (abs(player->position.x - position.x) < range)
	{
		iPoint origin = App->map->WorldToMap(position.x, position.y);
		iPoint destination = App->map->WorldToMap(player->position.x, player->position.y);
		App->pathfinding->CreatePath(origin, destination);
		Following_Player = true;
	}
	else { Following_Player = false; }

	//PATHFINDING DRAW
	if (Following_Player)
	{
		int x, y;
		SDL_Rect Debug_rect = { 0,0,32,32 };

		path = App->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			Debug_rect.x = pos.x;
			Debug_rect.y = pos.y;
			if (App->collision->debug)App->render->DrawQuad(Debug_rect, 90, 850, 230, 40);
		}
	}

}

void j1Entity::Pushbacks() {}

void j1Entity::OnCollision(Collider* c1, Collider* c2) {}

void j1Entity::GetPosition() {}




