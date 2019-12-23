#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1MainMenu.h"
#include "j1Scene.h"
#include "j1Window.h"
#include "j1GUI.h"
#include "j1FadeToBlack.h"
#include "j1Scene.h"
#include "j1Map.h"

j1MainMenu::j1MainMenu() : j1Module()
{
	name.create("intro");
}

// Destructor
j1MainMenu::~j1MainMenu()
{}

// Called before render is available
bool j1MainMenu::Awake()
{
	LOG("Loading Intro Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1MainMenu::Start()
{
	
	texture = App->tex->Load("sprites/mainfinal.png");
	play_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,50 }, { 0,0 }, true, true, { 4,69,130,37 });
	continue_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,100 }, { 0,0 }, true, false, { 4,69,130,37 });



	return true;
}

// Called each loop iteration
bool j1MainMenu::PreUpdate() {

	return true;
}

// Called each loop iteration
bool j1MainMenu::Update(float dt)
{


	//if (play_button->focus) {		
		//App->scene->actual_map = App->scene->Change_Map(1);
	//}

	//if (continue_button->focus) {
	//	want_continue = true;
	//	App->scene->actual_map = App->scene->Change_Map(1);
	//}		

	SDL_Rect rect = { 0,0, App->win->screen_surface->w, App->win->screen_surface->h };
	App->render->Blit(texture, 0, 0, &rect);

	return true;
}

// Called each loop iteration
bool j1MainMenu::PostUpdate()
{
	bool ret = true;	

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1MainMenu::CleanUp()
{
	LOG("Freeing intro scene");
	play_button = nullptr;
	App->gui->CleanUp();
	App->tex->Unload(texture);
	return true;
}
