#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Skeleton.h"
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

j1Skeleton::j1Skeleton() : j1Entity(Types::SKELETON)
{
	name.create("skeleton");
}

j1Skeleton::j1Skeleton(iPoint pos) : j1Entity(Types::SKELETON)
{
	name.create("skeleton");
	position = pos;
}

// Destructor
j1Skeleton::~j1Skeleton()
{}

// Called before render is available
bool j1Skeleton::Awake(pugi::xml_node& config)
{
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Skeleton::Start()
{

	vel.x = 0;
	vel.y = 0;
	
	current_animation = &walking;
	skeletonCollider = App->collision->AddCollider({ position.x , position.y , 15, 25 }, COLLIDER_ENEMY, this);

	skeletonTex = App->tex->Load("sprites/ENEMIES.png");
	Pushbacks();

	return true;
}

// Called each loop iteration
bool j1Skeleton::PreUpdate()
{
	skeletonCollider->SetPos(position.x, position.y );

	return true;
}

bool j1Skeleton::Update(float dt)
{
	BlitEntity(current_animation->GetCurrentFrame(), SDL_FLIP_NONE, position.x, position.y);
	switch (state)
	{
	case SKELETON_FORWARD:
		Looking_Forward = true;
		vel.x += SpeedX;
		current_animation = &walking;
		break;

	case SKELETON_BACKWARD:
		Looking_Forward = false;
		vel.x -= SpeedX;
		current_animation = &walking2;
		break;

	case SKELETON_DEATH:
		current_animation = &death;
		break;
	}
	current_animation = &walking;
	Skeleton_Position();



	//COLLIDER POSITION
	skeletonCollider->SetPos(position.x , position.y);

	App->render->Blit_Player(skeletonTex, position.x , position.y , &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
	

	//SKELETON BLIT
	/*
	if (App->render->camera.x < -550) {

		if (Looking_Forward == false) {
			App->render->Blit_Player(skeletonTex, position.x - 390, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
		else {
			App->render->Blit_Player(skeletonTex, position.x - 350, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
	}
	if (App->render->camera.x > -550) {

		if (Looking_Forward == false) {
			App->render->Blit_Player(skeletonTex, position.x + 15, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
		else {
			App->render->Blit_Player(skeletonTex, position.x + 55, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
	}
	
*/

	return true;
}

bool j1Skeleton::PostUpdate()
{
	return true;
}




// Called before quitting
bool j1Skeleton::CleanUp()
{
	App->tex->Unload(skeletonTex);

	return true;
}

// Load Game State
bool j1Skeleton::Load(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("posX").as_int();
	position.y = data.child("position").attribute("posY").as_int();
	return true;
}

// Save Game State
bool j1Skeleton::Save(pugi::xml_node& data) const
{
	pugi::xml_node playerNode = data.append_child("position");
	playerNode.append_attribute("posX") = position.x;
	playerNode.append_attribute("posY") = position.y;
	return true;
}


void j1Skeleton::Skeleton_State(Skeleton_States stateS)
{
	state = stateS;
}

void j1Skeleton::Pushbacks()
{
	walking.PushBack({ 3, 273, 18, 32 });
	walking.PushBack({ 25, 273, 18, 32 });
	walking.PushBack({ 47, 273, 18, 32 });
	walking.PushBack({ 68, 272, 20, 33 });
	walking.PushBack({ 90, 272, 21, 33 });
	walking.PushBack({ 112, 272, 22, 33 });
	walking.PushBack({ 134, 273, 22, 32 });
	walking.PushBack({ 156, 273, 22, 32 });
	walking.PushBack({ 178, 273, 22, 32 });
	walking.PushBack({ 200, 273, 22, 32 });
	walking.PushBack({ 223, 273, 20, 32 });
	walking.PushBack({ 246,273, 18, 32 });
	walking.PushBack({ 268, 273, 17, 32 });
	walking.lock = true;
	walking.speed = 0.5f;

	walking2.PushBack({ 958, 594, 18, 32 });
	walking2.PushBack({ 936, 594, 18, 32 });
	walking2.PushBack({ 914, 594, 18, 32 });
	walking2.PushBack({ 891, 593, 20, 33 });
	walking2.PushBack({ 868, 593, 21, 33 });
	walking2.PushBack({ 845, 593, 22, 33 });
	walking2.PushBack({ 823, 594, 22, 32 });
	walking2.PushBack({ 801, 594, 22, 32 });
	walking2.PushBack({ 779, 594, 22, 32 });
	walking2.PushBack({ 757, 594, 22, 32 });
	walking2.PushBack({ 736, 594, 20, 32 });
	walking2.PushBack({ 715, 594, 18, 32 });
	walking2.PushBack({ 694, 594, 17, 32 });
	walking.lock = true;
	walking.speed = 0.5f;

	death.PushBack({ 14, 76, 22, 32 });
	death.PushBack({ 44, 76, 23, 32 });
	death.PushBack({ 76, 76, 23, 32 });
	death.PushBack({ 206, 76, 24, 32 });
	death.PushBack({ 239, 76, 24, 32 });
	death.PushBack({ 272, 77, 23, 31 });
	death.PushBack({ 304, 80, 23, 28 });
	death.PushBack({ 337,83, 24, 25 });
	death.PushBack({ 370, 92, 25, 16 });
	death.PushBack({ 399, 100, 28, 6 });
	death.lock = true;
	death.speed = 0.3f;

	death2.PushBack({ 943, 397, 22, 32 });
	death2.PushBack({ 912, 397, 23, 32 });
	death2.PushBack({ 880, 397, 23, 32 });
	death2.PushBack({ 749, 397, 24, 32 });
	death2.PushBack({ 716, 397, 24, 32 });
	death2.PushBack({ 684, 398, 23, 31 });
	death2.PushBack({ 652, 401, 23, 28 });
	death2.PushBack({ 618, 404, 25, 16 });
	death2.PushBack({ 584, 413, 25, 16 });
	death2.PushBack({ 550, 421, 28, 6 });
	death2.lock = true;
	death.speed = 0.3f;
}


void j1Skeleton::OnCollision(Collider* c1, Collider* c2)
{
}

void j1Skeleton::Skeleton_Position()
{
	if (Near_Player) {
	
	}
	
}

bool j1Skeleton::pathfinding_ground() {

	static iPoint InicialEntityPosition;

	iPoint RIGHT(position.x, position.y); iPoint UP(position.x, position.y);
	iPoint LEFT(position.x, position.y); iPoint DOWN(position.x, position.y);

	iPoint playerPos = App->EntityManager->Get_Player()->position;
	playerPos = App->map->WorldToMap(playerPos.x + 30, playerPos.y + 30);

	InicialEntityPosition = App->map->WorldToMap(position.x, position.y);
	App->pathfinding->CreatePath(InicialEntityPosition, playerPos);


	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
	if (path->At(1) != NULL)
	{
		if (state != SKELETON_DEATH)
		{
			if (path->At(1)->x < InicialEntityPosition.x && !App->pathfinding->IsWalkable(DOWN))
			{
				position.x -= SpeedX;
				Looking_Forward = false;
			}
			if (path->At(1)->x > InicialEntityPosition.x && !App->pathfinding->IsWalkable(RIGHT))
			{
				position.x += SpeedX;
				Looking_Forward = true;
			}
		}
	}
	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint nextPathPosition = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
	}

	return true;
}