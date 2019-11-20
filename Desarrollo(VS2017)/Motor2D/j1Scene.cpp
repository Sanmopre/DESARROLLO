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
	// Change map
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		actual_map = Change_Map(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		actual_map = Change_Map(2);
	}

	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame();

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
	

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d AVG_FPS:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());
					App->AVG_FPS;

	App->win->SetTitle(title.GetString());
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
	
	//App->collision->CleanUp();
	CleanUp();
	App->player->Restart();

	int current_map = map;
	if (map == 1) {
		App->fade->Fade_To_Black(2);
		App->map->CleanUp();
		App->map2->CleanUp();
		App->player->playerinfo.Alive = false;
		App->collision->MapCleanUp();
		
			App->map2->Load("castle.tmx");
		
		current_map = 1;
		return true;
		
	}
	else {
		App->fade->Fade_To_Black(2);
		App->map2->CleanUp();
		App->map->CleanUp();
		App->collision->MapCleanUp();
		App->player->playerinfo.Alive = false;
		App->collision->MapCleanUp();
		
			App->map->Load("dungeon.tmx");
		
		current_map = 2;
		return false;
	}
	
}

// Called before quitting
