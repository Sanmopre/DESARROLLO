#ifndef __j1MAINMENU_H__
#define __j1MAINMENU_H__

#include "j1Module.h"
#include "p2DynArray.h"


struct SDL_Texture;
class j1GUIelement;

struct Settings_Menu {

	j1GUIelement* image = nullptr;
	j1GUIelement* exit = nullptr;
	j1GUIelement* button = nullptr;
	j1GUIelement* scroll = nullptr;
};

struct Credits_Menu 
{
	j1GUIelement* button = nullptr;
	j1GUIelement* license = nullptr;
	j1GUIelement* credits = nullptr;
	j1GUIelement* link = nullptr;
};
class j1MainMenu : public j1Module
{
public:

	j1MainMenu();

	// Destructor
	virtual ~j1MainMenu();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void Disable_UI();
	void Enable_UI();

	void GUI_Event_Manager(GUI_Event type, j1GUIelement* element);

public:

	SDL_Texture* texture;
	j1GUIelement* play_button = nullptr;
	j1GUIelement* continue_button = nullptr;
	j1GUIelement* exit_button = nullptr;

	bool want_continue = false;
	bool want_exit = false;

	Settings_Menu settings_menu;
	Credits_Menu credits_menu;
};

#endif // __j1MAINMENU_H__