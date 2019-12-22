#ifndef __j1MAINMENU_H__
#define __j1MAINMENU_H__

#include "j1Module.h"
#include "p2DynArray.h"

struct SDL_Texture;
class j1GUIelement;

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

public:

	SDL_Texture* texture;
	j1GUIelement* play_button= nullptr;
	j1GUIelement* continue_button = nullptr;

	bool want_continue = false;
};

#endif // __j1MAINMENU_H__