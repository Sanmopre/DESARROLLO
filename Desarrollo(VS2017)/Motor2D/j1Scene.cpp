#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1Collision.h"
#include "j1FadeToBlack.h"
#include "j1Entity.h"
#include "j1EntityManager.h"

#include "Brofiler/Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	//App->map->Load("dungeon.tmx");
	//App->audio->PlayMusic("audio/music/ghost.ogg");
	App->map2->Load("castle.tmx");
	App->audio->PlayMusic("audio/music/castle.ogg");

	
	//ENTITY
	skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
	//App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
	App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);

	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Scene_Update", Profiler::Color::Violet)

	

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		actual_map = Change_Map(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		actual_map = Change_Map(2);
	}


	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) 
	{
		App->LoadGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->SaveGame();
	}


	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if (actual_map == true) {
		App->map2->Draw();
	}
	else {
		App->map->Draw();
	}
	

	
	return true;
}



// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}




bool j1Scene::Change_Map(int map)
{
	CleanUp();
	App->player->Restart();

	int current_map = map;
	if (map == 1)
	{
		App->fade->Fade_To_Black(2);
		App->map->CleanUp();
		App->map2->CleanUp();
		App->player->playerinfo.Alive = false;
		App->collision->MapCleanUp();
		
			App->map2->Load("castle.tmx");
			App->audio->PlayMusic("audio/music/castle.ogg");
		current_map = 1;
		return true;
		
	}
	else
	{
		App->fade->Fade_To_Black(2);
		App->map2->CleanUp();
		App->map->CleanUp();
		App->collision->MapCleanUp();
		App->player->playerinfo.Alive = false;
		App->collision->MapCleanUp();
		
			App->map->Load("dungeon.tmx");
			App->audio->PlayMusic("audio/music/ghost.ogg");
		
		current_map = 2;
		return false;
	}
}


bool j1Scene::Load(pugi::xml_node& data)
{
	App->player->playerinfo.position.x = data.child("playerPos").attribute("player_pos_x").as_float();
	App->player->playerinfo.position.y = data.child("playerPos").attribute("player_pos_y").as_float();

	return true;
}


bool j1Scene::Save(pugi::xml_node& data) const
{
	pugi::xml_node player = data.append_child("playerPos");

	player.append_attribute("player_pos_x") = App->player->playerinfo.position.x;
	player.append_attribute("player_pos_y") = App->player->playerinfo.position.y;

	pugi::xml_node player_collider = data.append_child("player_collider");

	return true;
}
// Called before quitting
