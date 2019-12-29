#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2Point.h"
#include "j1Entity.h"

struct SDL_Texture;
class j1GUIelement;


struct Stats_Menu
{
	j1GUIelement*		Coins_label = nullptr;	
	j1GUIelement*		Coins_icon = nullptr;
	j1GUIelement*		Lifes_icon = nullptr;
	j1GUIelement*		Lifes_label = nullptr;
	j1GUIelement*		Timer_label = nullptr;
	j1GUIelement*		Timer_icon = nullptr;
};
struct Console
{
	j1GUIelement* Input = nullptr;
	j1GUIelement* Image = nullptr;
};

struct Game_Menu {

	j1GUIelement* Menu_button = nullptr;
	j1GUIelement* Title = nullptr;
	j1GUIelement* Image = nullptr;
	j1GUIelement* Exit_button = nullptr;
	j1GUIelement* Return_button = nullptr;
	j1GUIelement* Resume_button = nullptr;
	j1GUIelement* Music_scroll = nullptr;
	j1GUIelement* Save = nullptr;
	j1GUIelement* Load = nullptr;
	j1GUIelement* label1 = nullptr;
};


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	bool Change_Map(int map);
	int actual_map = 3;

	//UI managment
	void GUI_Event_Manager(GUI_Event type, j1GUIelement* element);
	bool Console_Manager();

	void Add_UI();
	void Activate_Menu();
	void Activate_Console();

public:

	bool already_added = false;
	bool Main_Menu = true;
	SDL_Texture* graphics = nullptr;
	j1Entity* skeleton;
	j1Entity* player;
	j1Entity* flying_enemy;
	j1Entity* coin;
	j1Entity* coin2;

	int					Lifes;
	int					Coins = 0;
	float				Timer;
	float				Lifes_num;

	char				Timer_T[100];
	char				Lifes_T[100];
	char				Coins_T[100];

	iPoint Fly_Position =  { 690 , 100 };
	iPoint Skeleton_Position = {190 , 30};
	iPoint Player_Pos = { 30, 320 };
	iPoint Coin_pos = { 290, 350 };
	iPoint Coin2_pos = { 250, 350 };

	Game_Menu			menu;
	Console				console;
	Stats_Menu			stats;
};

#endif // __j1SCENE_H__