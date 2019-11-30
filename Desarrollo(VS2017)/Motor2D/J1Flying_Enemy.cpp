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



	current_animation = &walking;
	Flying_Enemy_Collider = App->collision->AddCollider({ position.x , position.y , 20, 20 }, COLLIDER_ENEMY, this);
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

	//COLLIDER POSITION
	Flying_Enemy_Collider->SetPos(position.x, position.y);

	//SKELETON BLIT
	if (App->render->camera.x < -550) {

		if (Looking_Forward == false) {
			App->render->Blit_Player(Flying_Enemy_Tex, position.x - 390, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
		else {
			App->render->Blit_Player(Flying_Enemy_Tex, position.x - 350, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
	}
	if (App->render->camera.x > -550) {

		if (Looking_Forward == false) {
			App->render->Blit_Player(Flying_Enemy_Tex, position.x + 15, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
		else {
			App->render->Blit_Player(Flying_Enemy_Tex, position.x + 55, position.y - 20, &(current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
		}
	}

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
	walking.PushBack({ 3, 347, 19, 42 });
	walking.PushBack({ 65, 349, 28, 41 });
	walking.PushBack({ 130, 345, 26, 42});
	walking.PushBack({195, 351, 24, 42});
	walking.PushBack({259, 352, 24, 42});
	walking.PushBack({322, 349, 25, 44});
	walking.PushBack({386, 348, 25, 42});
	walking.lock = true;
	walking.speed = 0.1;

	walking2.PushBack({387, 656, 19, 42});
	walking2.PushBack({321, 658, 28, 41});
	walking2.PushBack({258, 659, 26, 42});
	walking2.PushBack({195, 660, 24, 42});
	walking2.PushBack({131, 661, 24, 42});
	walking2.PushBack({67, 658, 25, 44});
	walking2.PushBack({3, 657, 25, 42});
	walking2.lock = true;
	walking2.speed = 0.1f;

	death.PushBack({ 3, 347, 19, 42 });
	death.PushBack({64, 460, 30, 30});
	death.PushBack({126, 458, 29, 26});
	death.PushBack({200, 462, 15, 17});
	death.PushBack({267, 465, 10, 12});
	death.PushBack({327, 463, 20, 18});
	death.PushBack({392, 461, 17, 18});
	death.lock = true;
	death.speed = 0.15f;

	death2.PushBack({ 387, 656, 19, 42 });
	death2.PushBack({320, 769, 30, 30});
	death2.PushBack({259, 767, 29, 26});
	death2.PushBack({199, 771, 15,17});
	death2.PushBack({137, 774, 10, 12});
	death2.PushBack({67, 772, 20, 18});
	death2.PushBack({5, 770,17,18});
	death2.lock = true;
	death2.speed = 0.15f;
}


void j1Flying_Enemy::OnCollision(Collider* c1, Collider* c2)
{
}

void j1Flying_Enemy::Flying_Enemy_Position()
{
	

}