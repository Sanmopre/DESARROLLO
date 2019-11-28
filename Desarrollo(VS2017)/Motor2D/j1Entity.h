#ifndef __j1ENTITY_H__
#define __j1ENTITY_H__

#include "PugiXml/src/pugixml.hpp"
#include "j1Module.h"
#include "j1Animation.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2DynArray.h"

#define DT_CONVERTER 60

struct SDL_Texture;
//struct Collider;
struct Anim;

class j1Entity : public j1Module
{

public:

	enum class Types
	{
		PLAYER,
		SKELETON,
		FLYING_ENEMY,
		NULL_ENTITY
	};

	Types type;

	j1Entity(Types type);

	virtual ~j1Entity();

	bool CleanUp();
	bool Load(pugi::xml_node& data);
	bool Save(pugi::xml_node& data) const;



protected:

	int gravity;
	int Speed_X;
	int Speed_Y;
	bool Looking_Forward;

	Animation* current_animation = nullptr;
	p2List<Animation> animations;

	

public:
	iPoint position;
	Collider *Collider;
	bool to_delete = false;

	pugi::xml_document	entity_file;

};

#endif
