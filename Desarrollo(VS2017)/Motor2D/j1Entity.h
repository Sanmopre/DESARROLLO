#ifndef _j1ENTITY_H
#define _j1ENTITY_H
#include "SDL/include/SDL.h"
#include "j1Animation.h"
#include "j1EntityManager.h"

struct SDL_Texture;
struct Collider;

enum class EntityState {
	IDLE,
	FORWARD,
	BACKWARD,
};

class j1Entity : public j1EntityManager
{
public:

	j1Entity(Entity_Class type);
	virtual ~j1Entity();

	virtual bool Awake(pugi::xml_node&);
	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void OnCollision(Collider* c1, Collider* c2) {};

public:

	fPoint position;
	

	Collider* collider = nullptr;
	

	p2List<Animation*> animations;
	Animation idle;
	Animation idle2;
	Animation walk;
	Animation walk2;
	Animation jump;
	Animation jump2;

	Animation* current_animation = nullptr;

	Entity_Class type = Entity_Class::UNKNOWN;
	EntityState state = EntityState::IDLE;
	SDL_Texture* texture = nullptr;
};
#endif // !_j1ENTITY_H