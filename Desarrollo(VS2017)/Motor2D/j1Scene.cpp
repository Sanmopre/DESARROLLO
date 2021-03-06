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
#include "j1Fonts.h"
#include <stdio.h>

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
	
	Timer = 0;
	Lifes = 3;
	Coins = 0;
	
	player = nullptr;
	skeleton = nullptr;
	flying_enemy = nullptr;
	coin = App->EntityManager->Summon_Entity(j1Entity::Types::COIN, Coin_pos);
	Add_Console();
	

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

		bool ret = true;
	/*
	if (already_added == true) {
		Timer += dt;
		sprintf_s(Timer_T, "%.2f", Timer);
		App->tex->Unload(stats.Timer_label->texture);
		stats.Timer_label->text = Timer_T;

		sprintf_s(Lifes_T, "%d", Lifes);
		App->tex->Unload(stats.Lifes_label->texture);
		stats.Lifes_label->text = Lifes_T;

		sprintf_s(Coins_T, "%d", Coins);
		App->tex->Unload(stats.Coins_label->texture);
		stats.Coins_label->text = Coins_T;
	}
	*/
	

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		Main_Menu = false;
		Change_Map(1);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		Main_Menu = false;
		 Change_Map(2);
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
		Main_Menu = true;
		Change_Map(3);
		Close_InGame_UI();
			
	}

	//Game menu
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && Main_Menu == false) {
		Activate_Menu();
	}

	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN ){
		Activate_Console();
}
	//if (console.Input->focus)
	//	ret = Console_Manager();


	//UPDATES ALL UI POSITIONS
	if (already_added == true) {
		
		//App->gui->Update_Position(stats.Timer_label, { 220,(-App->render->camera.y / 2) + 22 }, { 0,(-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Timer_icon, { 180,(-App->render->camera.y / 2) + 13 }, { 0, (-App->render->camera.y / 2) });
		//App->gui->Update_Position(stats.Lifes_label, { 150,(-App->render->camera.y / 2) + 22 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Lifes_icon, { 100,(-App->render->camera.y / 2) + 13 }, { 0, (-App->render->camera.y / 2) });
		//App->gui->Update_Position(stats.Coins_label, { 55,(-App->render->camera.y / 2) + 22 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Coins_icon, { 10,(-App->render->camera.y / 2) + 15 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(menu.Image, { 160,(-App->render->camera.y / 2) + 5 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(menu.Menu_button, { 450,(-App->render->camera.y / 2 )+13}, { 0, 0 });
		App->gui->Update_Position(menu.Return_button, { 210,(-App->render->camera.y / 2) + 130 }, { -3, (-App->render->camera.y / 2) - 5 });
		App->gui->Update_Position(menu.Title, { 205,(-App->render->camera.y / 2) + 50 }, { 30, (-App->render->camera.y / 2) });
		App->gui->Update_Position(menu.Resume_button, { 210,(-App->render->camera.y / 2) + 100 }, { 10, (-App->render->camera.y / 2) - 5 });
		App->gui->Update_Position(menu.Exit_button, { 210,(-App->render->camera.y / 2) + 220 }, { 20, (-App->render->camera.y / 2) - 5 });
		App->gui->Update_Position(menu.Save, { 210,(-App->render->camera.y / 2) + 160 }, { 20, (-App->render->camera.y / 2) - 5 });
		App->gui->Update_Position(menu.Load, { 210,(-App->render->camera.y / 2) + 190 }, { 20, (-App->render->camera.y / 2) - 5 });
		App->gui->Update_Position(console.Image, { 160,(-App->render->camera.y / 2) + 60 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(console.Input, { 170,(-App->render->camera.y / 2) + 220 }, { 0, (-App->render->camera.y / 2) });
	}



	if (actual_map == 1) {App->map2->Draw();}
	if (actual_map == 2) {App->map->Draw();}
		
	


	
	return ret;
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

		if (already_added == false) {
			Add_UI();
		}
		Open_InGame_UI();
		Main_Menu = false;
		App->MainMenu->Disable_UI();
		//App->EntityManager->Destroy_Entities();
		if (player == nullptr) {
			player = App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
		}
		skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
		flying_enemy = App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);
		player->Alive = false;
		App->fade->Fade_To_Black(2);
		App->map->CleanUp();
		App->collision->MapCleanUp();
		App->map2->Load("castle.tmx");
		App->audio->PlayMusic("audio/music/castle.ogg");
		actual_map = 1;
		return true;
	}
	if (map == 2)
	{

		if (already_added == false) {
			Add_UI();
		}
		Open_InGame_UI();
		Main_Menu = false;
		App->MainMenu->Disable_UI();
		//App->EntityManager->Destroy_Entities();
		skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
		flying_enemy = App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);
		if (player == nullptr) {
			player = App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
		}
		player->Alive = false;
		App->fade->Fade_To_Black(2);
		App->map2->CleanUp();
		App->collision->MapCleanUp();
		App->map->Load("dungeon.tmx");
		App->audio->PlayMusic("audio/music/ghost.ogg");
		actual_map = 2;
		return false;
	}
	if (map == 3)
	{
		//Activate_Menu();
		Main_Menu = true;
		App->MainMenu->Enable_UI();
		App->fade->Fade_To_Black(2);
		App->map2->CleanUp();
		App->map->CleanUp();
		actual_map = 3;
		return false;
	}

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

void j1Scene::Add_UI()
{
	stats.Timer_label = App->gui->ADD_ELEMENT(GUItype::GUI_LABEL, nullptr, { 220,22 }, { 0,0 }, false, true, { 0,0,0,0 }, "0:00");
	stats.Timer_icon = App->gui->ADD_ELEMENT(GUItype::GUI_IMAGE, nullptr, { 180, 13 }, { 0,0 }, false, true, { 0, 0, 30,30 }, nullptr, this);
	stats.Lifes_label = App->gui->ADD_ELEMENT(GUItype::GUI_LABEL, nullptr, { 146,22 }, { 0,0 }, false, true, { 0,0,0,0 }, "3");
	stats.Lifes_icon = App->gui->ADD_ELEMENT(GUItype::GUI_IMAGE, nullptr, { 100, 13 }, { 0,0 }, false, true, { 0, 0, 30,30 }, nullptr, this);
	stats.Coins_label = App->gui->ADD_ELEMENT(GUItype::GUI_LABEL, nullptr, { 55,22 }, { 0,0 }, false, true, { 0,0,0,0 }, "0");
	stats.Coins_icon = App->gui->ADD_ELEMENT(GUItype::GUI_IMAGE, nullptr, { 10, 15 }, { 0,0 }, false, true, { 0, 0, 30,30 }, nullptr, this);
	menu.Image = App->gui->ADD_ELEMENT(GUItype::GUI_IMAGE, nullptr, { 10, 60 }, { 0,0 }, false, false, { 0, 0, 200, 280 }, nullptr, this);
	menu.Menu_button = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 450,250 }, { 0,-235 }, true, true, { 0,0,70,30 }, "OPTIONS",  this);
	menu.Return_button = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 210,130 }, { 20,5 }, true, false, { 0, 0,100,22 }, "RETURN", this);
	menu.Title = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 205,50 }, { 30,0 }, false, false, { 0, 0,109,27 }, "MENU", this, false, false, SCROLL_TYPE::SCROLL_NONE, true);
	menu.Resume_button = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 210,100 }, { 20,5 }, true, false, { 0, 0,100,22 }, "RESUME", this);
	menu.Exit_button = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 210,220 }, { 20,5 }, true, false, { 0, 0,100,22 }, "EXIT", this);
	menu.Save = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 210,160 }, { 20,5 }, true, false, { 0, 0,100,22 }, "SAVE", this);
	menu.Load = App->gui->ADD_ELEMENT(GUItype::GUI_BUTTON, nullptr, { 210,190 }, { 20,5 }, true, false, { 0, 0,100,22 }, "LOAD", this);

	
	already_added = true;
}


void j1Scene::Add_Console()
{
console.Image = App->gui->ADD_ELEMENT(GUItype::GUI_IMAGE, nullptr, { 160, 60 }, { 0,0 }, false, false, { 0, 0, 198, 200 }, nullptr, this);
console.Input = App->gui->ADD_ELEMENT(GUItype::GUI_INPUTBOX, nullptr, { 168,220 }, { 0,0 }, true, false, { 0, 0,182,26 }, nullptr, this);
}

void j1Scene::Activate_Menu() 
{
	menu.Image->enabled = !menu.Image->enabled;
	menu.Resume_button->enabled = !menu.Resume_button->enabled;
	menu.Return_button->enabled = !menu.Return_button->enabled;
	menu.Title->enabled = !menu.Title->enabled;
	menu.Exit_button->enabled = !menu.Exit_button->enabled;
	menu.Load->enabled = !menu.Load->enabled;
	menu.Save->enabled = !menu.Save->enabled;
}

void j1Scene::Activate_Console()
{
	console.Input->focus = !console.Input->focus;
	console.Input->enabled = !console.Input->enabled;
	console.Image->enabled = !console.Image->enabled;
}

void j1Scene::GUI_Event_Manager(GUI_Event type, j1GUIelement* element)
{
	switch (type)
	{

	case GUI_Event::EVENT_ONCLICK:
	{
		App->audio->PlayFx(App->audio->LoadFx("audio/fx/UI_fx.wav"));

		
		if (element == menu.Return_button) {
			Activate_Menu();
		}

		if (element == menu.Exit_button) {
			Main_Menu = true;
			 Change_Map(3);
		}

		if (element == menu.Save) {
			App->SaveGame();
			Activate_Menu();
		}
		if (element == menu.Load) {
			Activate_Menu();

		}

		if (element == menu.Resume_button) {
			Activate_Menu();
		}
		if (element == menu.Menu_button) {
			Activate_Menu();
		}

		if (element == menu.Exit_button) {
			Main_Menu = true;
			actual_map = Change_Map(3);
			Close_InGame_UI();
		}
	}
	}
}

void j1Scene::Close_InGame_UI() 
{
	stats.Timer_label->enabled = false;
	stats.Timer_icon->enabled = false;
	stats.Lifes_label->enabled = false;
	stats.Lifes_icon->enabled = false;
	stats.Coins_label->enabled = false;
	stats.Coins_icon->enabled = false;
	menu.Image->enabled = false;
	menu.Menu_button->enabled = false;
	menu.Return_button->enabled = false;
	menu.Title->enabled = false;
	menu.Resume_button->enabled = false;
	menu.Exit_button->enabled = false;
	menu.Save->enabled = false;
	menu.Load->enabled = false;
	console.Image->enabled = false;
	console.Input->enabled = false;
}

void j1Scene::Open_InGame_UI() 
{
	stats.Timer_label->enabled = true;
	stats.Timer_icon->enabled = true;
	stats.Lifes_label->enabled = true;
	stats.Lifes_icon->enabled = true;
	stats.Coins_label->enabled = true;
	stats.Coins_icon->enabled = true;
	menu.Menu_button->enabled = true;

}