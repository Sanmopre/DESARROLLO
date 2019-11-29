#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Flying_Enemy.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Entity.h"
#include "SDL_image/include/SDL_image.h"
#include "Brofiler/Brofiler.h"

j1Flying_Enemy::j1Flying_Enemy() : j1Entity(Types::FLYING_ENEMY)
{
	name.create("Flying_Enemy");
}

j1Flying_Enemy::j1Flying_Enemy(iPoint pos) : j1Entity(Types::FLYING_ENEMY)
{
	name.create("skeleton");
	position = pos;
}

// Destructor
j1Flying_Enemy::~j1Flying_Enemy()
{}

// Called before render is available
bool j1Flying_Enemy::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Flying_Enemy::Start()
{
	Pushbacks();
	vel.x = 0;
	vel.y = 0;

	//SkeletonFx = App->audio->LoadFx("audio/jumping.wav");

	position.x = SpawnPointX;
	position.y = SpawnPointY;

	current_animation = &walking;
	Flying_Enemy_Collider = App->collision->AddCollider({ position.x , position.y , 30, 30 }, COLLIDER_ENEMY, this);
	Flying_Enemy_Tex = App->tex->Load(PATH(folder.GetString(), texture_path.GetString()));
	return true;
}

// Called each loop iteration
bool j1Flying_Enemy::PreUpdate()
{
	Flying_Enemy_Collider->SetPos(position.x + 1, position.y + 8);

	return true;
}

bool j1Flying_Enemy::Update(float dt)
{
	switch (state)
	{
	case FLYING_ENEMY_FORWARD:
		Looking_Forward = true;
		vel.x += SpeedX;
		current_animation = &walking;
		break;

	case FLYING_ENEMY_BACKWARD:
		Looking_Forward = false;
		vel.x -= SpeedX;
		current_animation = &walking;
		break;

	case FLYING_ENEMY_DEATH:
		current_animation = &death;
		break;
	}

	Flying_Enemy_Position();

	return true;
}

bool j1Flying_Enemy::PostUpdate()
{
	return true;
}




// Called before quitting
bool j1Flying_Enemy::CleanUp()
{
	App->tex->Unload(Flying_Enemy_Tex);

	return true;
}

// Load Game State
bool j1Flying_Enemy::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("posX").as_int();
	position.y = data.child("position").attribute("posY").as_int();
	return true;
}

// Save Game State
bool j1Flying_Enemy::Save(pugi::xml_node& data) const
{
	pugi::xml_node playerNode = data.append_child("position");
	playerNode.append_attribute("posX") = position.x;
	playerNode.append_attribute("posY") = position.y;
	return true;
}


void j1Flying_Enemy::Flying_Enemy_State(Flying_Enemy_States stateS)
{
	state = stateS;
}

void j1Flying_Enemy::Pushbacks()
{

}


void j1Flying_Enemy::OnCollision(Collider* c1, Collider* c2)
{
}

void j1Flying_Enemy::Flying_Enemy_Position()
{
	

}