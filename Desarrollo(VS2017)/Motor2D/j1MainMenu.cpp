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
	name.create("menu");
}

// Destructor
j1MainMenu::~j1MainMenu()
{}

// Called before render is available
bool j1MainMenu::Awake()
{
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1MainMenu::Start()
{
	texture = App->tex->Load("sprites/menufinal.png");
	play_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,50 }, { 0,0 }, true, true, { 4,69,130,37 }, "PLAY", this);
	continue_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,100 }, { 0,0 }, true, true, { 4,69,130,37 }, "CONTINUE", this);
	exit_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,150 }, { 0,0 }, true, true, { 4,69,130,37 }, "EXIT", this);

	// Settings menu UI elements
	settings_menu.image = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 200, 50 }, { 0,0 }, true, false, { 20, 324, 251, 270 }, nullptr, this);
	settings_menu.button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,200 }, { 0,0 }, true, true, { 4,69,130,37 }, "SETTINGS", this);
	settings_menu.exit = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 410,60 }, { 0,0 }, true, false, { 513,53,14,14 }, nullptr, this);
	settings_menu.scroll = App->gui->AddGUIelement(GUItype::GUI_SCROLLBAR, nullptr, { 210, 80 }, { 0,0 }, false, true, { 0, 6, 183, 7 }, nullptr, this);

	// Credits menu UI elements
	credits_menu.image = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 50, 300 }, { 0,0 }, true, false, { 20, 324, 251, 270 }, nullptr, this);
	credits_menu.button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 50,250 }, { 0,0 }, true, true, { 4,69,130,37 }, "CREDITS", this);
	credits_menu.exit = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 260,310 }, { 0,0 }, true, false, { 513,53,14,14 }, nullptr, this);

	return true;
}

// Called each loop iteration
bool j1MainMenu::PreUpdate() {

	return true;
}

// Called each loop iteration
bool j1MainMenu::Update(float dt)
{

	bool ret = true;

	if (want_exit)
		ret = false;

	SDL_Rect rect = { 0,0, App->win->screen_surface->w, App->win->screen_surface->h };
	App->render->Blit(texture, 0, 10, &rect);

	return ret;
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
	play_button = nullptr;
	continue_button = nullptr;
	exit_button = nullptr;

	//Cleaning Setting menu UI
	settings_menu.image = nullptr;
	settings_menu.exit = nullptr;
	settings_menu.button = nullptr;
	settings_menu.scroll = nullptr;

	//Cleaning Credits menu UI
	credits_menu.image = nullptr;
	credits_menu.exit = nullptr;
	credits_menu.button = nullptr;

	App->gui->CleanUp();
	App->tex->Unload(texture);
	return true;
}

void j1MainMenu::GuiObserver(GUI_Event type, j1GUIelement* element)
{

	switch (type)
	{

	case GUI_Event::EVENT_ONCLICK:
	{

		if (element == play_button) {
		
		}
			
		if (element == continue_button) {
			want_continue = true;
			
		}

		if (element == settings_menu.button) {
			settings_menu.image->enabled = true;
			settings_menu.exit->enabled = true;
		}

		if (element == settings_menu.exit) {
			settings_menu.image->enabled = false;
			settings_menu.exit->enabled = false;
		}

		if (element == credits_menu.button) {
			credits_menu.image->enabled = true;
			credits_menu.exit->enabled = true;
		}

		if (element == credits_menu.exit) {
			credits_menu.image->enabled = false;
			credits_menu.exit->enabled = false;
		}

		if (element == exit_button)
			want_exit = true;

	}
	}

}
