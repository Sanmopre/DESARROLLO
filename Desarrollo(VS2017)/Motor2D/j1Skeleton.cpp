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
	Pushbacks();
	vel.x = 0;
	vel.y = 0;

	current_animation = &walking;
	skeletonCollider = App->collision->AddCollider({ position.x , position.y , 15, 25 }, COLLIDER_ENEMY, this);

	skeletonTex = App->tex->Load(PATH(folder.GetString(), texture_path.GetString()));
	return true;
}

// Called each loop iteration
bool j1Skeleton::PreUpdate()
{
	skeletonCollider->SetPos(position.x + 1, position.y + 8);

	return true;
}

bool j1Skeleton::Update(float dt)
{
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

	Skeleton_Position();

	//COLLIDER POSITION
	skeletonCollider->SetPos(position.x , position.y);

	//SKELETON BLIT
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

}


void j1Skeleton::OnCollision(Collider* c1, Collider* c2)
{
}

void j1Skeleton::Skeleton_Position()
{
	if (Near_Player) {
	
	}
	
}