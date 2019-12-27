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
#include "j1Gui.h"
#include "j1MainMenu.h"

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

	
	//App->audio->PlayMusic("audio/music/castle.ogg");

	
	//ENTITY
	//skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
	//player = App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
	//flying_enemy = App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);

	//UI
	//App->gui->AddGUIelement(GUItype::GUI_INPUTBOX, nullptr, { 50,50 }, { 0,0 }, true, true, { 295,343,199,31 });

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
		Main_Menu = false;
		actual_map = Change_Map(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		Main_Menu = false;
		actual_map = Change_Map(2);
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		Main_Menu = true;
		actual_map = Change_Map(3);
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) 
	{
		App->LoadGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		App->SaveGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
			App->MainMenu->Enable_UI();
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


	if (map == 1)
	{
		Main_Menu = false;
		App->MainMenu->Disable_UI();
		//App->EntityManager->Destroy_Entities();
		if (player == nullptr) {
			player = App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
		}
		//skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
		//flying_enemy = App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);
		player->Alive = false;
		App->fade->Fade_To_Black(2);
		App->map->CleanUp();
		App->map2->CleanUp();
		App->collision->MapCleanUp();
		App->map2->Load("castle.tmx");
		App->audio->PlayMusic("audio/music/castle.ogg");
		actual_map = 1;
		return true;
	}
	if (map == 2)
	{
		Main_Menu = false;
		App->MainMenu->Disable_UI();
		//App->EntityManager->Destroy_Entities();
		//skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
		//flying_enemy = App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);
		if (player == nullptr) {
			player = App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
		}
		player->Alive = false;
		App->fade->Fade_To_Black(2);
		App->map2->CleanUp();
		App->map->CleanUp();
		App->collision->MapCleanUp();
		App->map->Load("dungeon.tmx");
		App->audio->PlayMusic("audio/music/ghost.ogg");
		actual_map = 2;
		return false;
	}
	if (map == 3)
	{
		Main_Menu = true;
		App->MainMenu->Enable_UI();
		App->fade->Fade_To_Black(2);
		App->map2->CleanUp();
		App->map->CleanUp();
		actual_map = 3;
		return false;
	}

	int current_map = map;
}


bool j1Scene::Load(pugi::xml_node& data)
{

	return true;
}


bool j1Scene::Save(pugi::xml_node& data) const
{
	pugi::xml_node player = data.append_child("playerPos");



	pugi::xml_node player_collider = data.append_child("player_collider");

	return true;
}
// Called before quitting
