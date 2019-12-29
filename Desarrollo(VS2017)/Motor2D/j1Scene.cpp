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
	
	//App->audio->PlayMusic("audio/music/castle.ogg");

	
	//ENTITY
	//skeleton = App->EntityManager->Summon_Entity(j1Entity::Types::SKELETON, Skeleton_Position);
	//player = App->EntityManager->Summon_Entity(j1Entity::Types::PLAYER, Player_Pos);
	//flying_enemy = App->EntityManager->Summon_Entity(j1Entity::Types::FLYING_ENEMY, Fly_Position);
	coin = App->EntityManager->Summon_Entity(j1Entity::Types::COIN, Coin_pos);
	

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

	//Game menu
	//if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !console.Image->enabled) {
		//Activate_Menu();
	//}

	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN && !menu.Image->enabled){
	
		Activate_Console();
}
	//if (console.Input->focus)
	//	ret = Console_Manager();


	//UPDATES ALL UI POSITIONS
	if (already_added == true) {
		
		App->gui->Update_Position(stats.Timer_label, { 220,(-App->render->camera.y / 2) + 22 }, { 0,(-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Timer_icon, { 180,(-App->render->camera.y / 2) + 13 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Lifes_label, { 150,(-App->render->camera.y / 2) + 22 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Lifes_icon, { 100,(-App->render->camera.y / 2) + 13 }, { 0, (-App->render->camera.y / 2) });
		App->gui->Update_Position(stats.Coins_label, { 55,(-App->render->camera.y / 2) + 22 }, { 0, (-App->render->camera.y / 2) });
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
	stats.Timer_label = App->gui->AddGUIelement(GUItype::GUI_LABEL, nullptr, { 220,22 }, { 0,0 }, false, true, { 0,0,0,0 }, Timer_T, this, false, false);
	stats.Timer_icon = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 180, 13 }, { 0,0 }, false, true, { 460, 111, 27, 31 }, nullptr, this);
	stats.Lifes_label = App->gui->AddGUIelement(GUItype::GUI_LABEL, nullptr, { 146,22 }, { 0,0 }, false, true, { 0,0,0,0 }, "3");
	stats.Lifes_icon = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 100, 13 }, { 0,0 }, false, true, { 458, 78, 41, 31 }, nullptr, this);
	stats.Coins_label = App->gui->AddGUIelement(GUItype::GUI_LABEL, nullptr, { 55,22 }, { 0,0 }, false, true, { 0,0,0,0 }, "0");
	stats.Coins_icon = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 10, 15 }, { 0,0 }, false, true, { 458, 43, 40, 27 }, nullptr, this);
	menu.Image = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 10, 60 }, { 0,0 }, false, false, { 288, 144, 198, 282 }, nullptr, this);
	menu.Menu_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 450,250 }, { 0,0 }, true, true, { 84,164,37,31 }, nullptr, this);
	menu.Return_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 210,130 }, { -3,-5 }, true, false, { 283,109,100,22 }, "MAIN MENU", this);
	menu.Title = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 205,50 }, { 30,0 }, false, false, { 166,167,109,27 }, "MENU", this, false, false, SCROLL_TYPE::SCROLL_NONE, true);
	menu.Resume_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 210,100 }, { 10,-5 }, true, false, { 283,109,100,22 }, "RESUME", this);
	menu.Exit_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 210,220 }, { 20,-5 }, true, false, { 283,109,100,22 }, "EXIT", this);
	menu.Save = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 210,160 }, { 20,-5 }, true, false, { 283,109,100,22 }, "SAVE", this);
	menu.Load = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 210,190 }, { 20,-5 }, true, false, { 283,109,100,22 }, "LOAD", this);
	console.Image = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 160, 60 }, { 0,0 }, false, false, { 288, 144, 198, 200 }, nullptr, this);
	console.Input = App->gui->AddGUIelement(GUItype::GUI_INPUTBOX, nullptr, { 168,220 }, { 0,0 }, true, false, { 11,359,182,26 }, nullptr, this);
	
	already_added = true;
}

void j1Scene::Activate_Menu() {

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
		//AUDIO
		if (element == menu.Menu_button && !console.Image->enabled) {
			Activate_Menu();
		}
		if (element == menu.Return_button) {
			Activate_Menu();
		}

		if (element == menu.Exit_button) {
			Main_Menu = true;
			actual_map = Change_Map(3);
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
		}
	}
	}
}

