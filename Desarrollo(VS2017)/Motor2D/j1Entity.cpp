#include "j1Entity.h"
#include "p2Defs.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Animation.h"
#include "math.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "J1EntityManager.h"



j1Entity::j1Entity(Types type) : type(type)
{
}

j1Entity::~j1Entity() {

}


bool j1Entity::CleanUp() {

	if (Collider != false)
		Collider->to_delete = true;
	return true;
}

bool j1Entity::Load(pugi::xml_node& data) {
	LOG("Loading %s state", name.GetString());
	return true;
}

bool j1Entity::Save(pugi::xml_node& data) const {
	LOG("Saving %s state", name.GetString());

	data.append_child("position");

	data.append_attribute("type") = name.GetString();
	data.child("position").append_attribute("pos_x") = position.x;
	data.child("position").append_attribute("pos_y") = position.y;
	return true;
}
SDL_Rect TileSetPlayer::GetAnimRect(int id) const
{
	int relative_id = id;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = ((rect.w) * (relative_id % num_tiles_width));
	rect.y = ((rect.h) * (relative_id / num_tiles_width));
	return rect;
}





