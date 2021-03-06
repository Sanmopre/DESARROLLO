#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1Map;
class j1Animation;
class j1Collision;
class j1PathFinding;
class j1FadeToBlack;
class j1EntityManager;
class j1Entity;
class j1GUI;
class j1Fonts;
class j1MainMenu;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame();
	void SaveGame() const;
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	bool LoadColliders(pugi::xml_node& node, p2SString object_name);

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;
	j1Map*				map;
	j1Animation*        animation;
	j1Collision*        collision;
	j1Map*              map2;
	j1PathFinding*      pathfinding;
	j1FadeToBlack*      fade;
	j1EntityManager*	EntityManager;
	j1GUI*				gui;
	j1Fonts*			fonts;
	j1MainMenu*			MainMenu;


	j1PerfTimer			Perf_Timer;
	uint				Frame_Counter = 0;
	j1Timer				Starting_Time;
	j1Timer				Frame_Time;

	j1Timer				Last_Frame_Time;
	uint				Last_Frame_Counter = 0;
	uint				Prev_Last_Frame_Counter = 0;
	float				Delta_Time;
	bool				Fps_Cap_ON = true;	
	

public:
	uint16_t			Framerate = 1000 / 30;

	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game;
	mutable p2SString	save_game;
};

extern j1App* App; // No student is asking me about that ... odd :-S

#endif