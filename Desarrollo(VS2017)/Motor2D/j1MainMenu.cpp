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
	
	App->audio->PlayMusic("", 1.0f);
	texture = App->tex->Load("sprites/mainfinal.png");

	play_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 20,20 }, { 0,0 }, true, true, { 4,69,130,37 }, "PLAY", this);
	continue_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 20,70 }, { 0,0 }, true, true, { 4,69,130,37 }, "CONTINUE", this);
	exit_button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 20,120 }, { 0,0 }, true, true, { 4,69,130,37 }, "EXIT", this);
	settings_menu.image = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 200, 20 }, { 0,0 }, true, false, { 20, 324, 251, 270 }, nullptr, this);
	settings_menu.button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 20,170 }, { 0,0 }, true, true, { 4,69,130,37 }, "SETTINGS", this);
	settings_menu.exit = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 410,50 }, { 0,0 }, true, false, { 513,53,14,14 }, nullptr, this);
	settings_menu.scroll = App->gui->AddGUIelement(GUItype::GUI_SCROLLBAR, nullptr, { 210, 80 }, { 0,0 }, false, false, { 0, 6, 183, 7 }, nullptr, this);
	credits_menu.image = App->gui->AddGUIelement(GUItype::GUI_IMAGE, nullptr, { 200, 10 }, { 0,0 }, true, false, { 20, 324, 251, 270 }, nullptr, this);
	credits_menu.button = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 20,220 }, { 0,0 }, true, true, { 4,69,130,37 }, "CREDITS", this);
	credits_menu.exit = App->gui->AddGUIelement(GUItype::GUI_BUTTON, nullptr, { 400,20 }, { 0,0 }, true, false, { 513,53,14,14 }, nullptr, this);

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
	App->render->Blit(texture, 0, 0, &rect);

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
	LOG("Freeing intro scene");
	play_button = nullptr;
	continue_button = nullptr;
	exit_button = nullptr;

	settings_menu.image = nullptr;
	settings_menu.exit = nullptr;
	settings_menu.button = nullptr;
	settings_menu.scroll = nullptr;

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

		if (element == play_button)
	
			App->scene->actual_map = App->scene->Change_Map(1);

		if (element == continue_button) {
			App->scene->actual_map = App->scene->Change_Map(1);
		}

		if (element == settings_menu.button) {
			settings_menu.image->enabled = true;
			settings_menu.exit->enabled = true;
			settings_menu.scroll->enabled = true;
		}

		if (element == settings_menu.exit) {
			settings_menu.image->enabled = false;
			settings_menu.exit->enabled = false;
			settings_menu.scroll->enabled = false;
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

void j1MainMenu::Disable_UI() {

	play_button->enabled = false;
	continue_button->enabled = false;
	exit_button->enabled = false;
	settings_menu.image->enabled = false;
	settings_menu.button->enabled = false;
	settings_menu.exit->enabled = false;
	settings_menu.scroll->enabled = false;
	credits_menu.image->enabled = false;
	credits_menu.button->enabled = false;
	credits_menu.exit->enabled = false;

}
