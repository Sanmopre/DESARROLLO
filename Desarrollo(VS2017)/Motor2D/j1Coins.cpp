#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Coins.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Entity.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "SDL_image/include/SDL_image.h"
#include "Brofiler/Brofiler.h"

j1Coins::j1Coins() : j1Entity(Types::COIN)
{
	name.create("coin");
}

j1Coins::j1Coins(iPoint pos) : j1Entity(Types::COIN)
{
	name.create("coin");
	position = pos;
}

j1Coins::~j1Coins()
{}

// Called before render is available
bool j1Coins::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

bool j1Coins::Start()
{
	current_animation = &idle;
	//We need to put the collider here

	Asset_tex= App->tex->Load("sprites/assets.png");
	Pushbacks();
	return true;
}

bool j1Coins::PreUpdate()
{
	collider->SetPos(position.x, position.y);
	return true;
}

bool j1Coins::Update(float dt)
{
	if (Collected == false)
	{
		collider->SetPos(position.x, position.y);
	}
	App->render->Blit(Asset_tex, position.x, position.y, &current_animation->GetCurrentFrame(), SDL_FLIP_NONE);

	return true;
}

bool j1Coins::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Coins::CleanUp()
{
	Collected = true;
	return true;
}

// Load Game State
bool j1Coins::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("posX").as_int();
	position.y = data.child("position").attribute("posY").as_int();
	return true;
}

// Save Game State
bool j1Coins::Save(pugi::xml_node& data) const
{
	pugi::xml_node playerNode = data.append_child("position");
	playerNode.append_attribute("posX") = position.x;
	playerNode.append_attribute("posY") = position.y;
	return true;
}

void j1Coins::Pushbacks()
{
	idle.PushBack({ 55, 0, 18, 20 });
	idle.PushBack({75, 0, 14, 20});
	idle.PushBack({93, 0, 12, 20});
	idle.PushBack({116, 0, 4, 20});
	idle.PushBack({131, 0, 12, 20});
	idle.PushBack({147, 0, 14, 20});
	idle.lock = true;
	idle.speed = 0.5f;
	//ADD PUSHBACKS
}

void j1Coins::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER1 || c2->type == COLLIDER_COIN)
	{
		Collected = true;
		CoinCount++;
		CleanUp();
	}
}