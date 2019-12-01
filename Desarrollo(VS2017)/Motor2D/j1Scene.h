#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "p2Point.h"

struct SDL_Texture;

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
	bool actual_map = true;

public:
	SDL_Texture* graphics = nullptr;

	iPoint Player_Pos;
	iPoint Fly_Position =  { 690 , 100 };
	//iPoint Skeleton_Position = {190 , 30};
};

#endif // __j1SCENE_H__