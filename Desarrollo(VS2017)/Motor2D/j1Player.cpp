#include "p2Defs.h"
#include "j1Scene.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Animation.h"
#include "j1Collision.h"



j1Player::j1Player()
{
	name.create("player");

	//aqui ponemos los pixeles y los pushback :)


	playerinfo.idle.PushBack({ 163,11,12,30 }, 0, 0);
	playerinfo.idle.PushBack({ 185, 11,12 , 30 }, 0, 0);
	playerinfo.idle.PushBack({ 205, 12, 12,30 }, 0, 0);
	playerinfo.idle.PushBack({ 229, 10, 12, 30 }, 0, 0);
	playerinfo.idle.PushBack({ 251, 10, 10, 30 }, 0, 0);
	playerinfo.idle.PushBack({ 271, 10, 11, 30 }, 0, 0);
	playerinfo.idle.speed = 0.2f;
	playerinfo.idle.lock = true;

	playerinfo.walk.PushBack({11, 79, 16, 29},0,0);
	playerinfo.walk.PushBack({ 36, 78, 12, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 52, 79, 13, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 69, 80, 20, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 89, 79, 22, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 111, 80, 16, 29 }, 0, 0);
	playerinfo.walk.PushBack({ 131, 79, 16, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 148, 79, 14, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 164, 80, 15, 29 }, 0, 0);
	playerinfo.walk.PushBack({ 179, 81, 19, 28 }, 0, 0);
	playerinfo.walk.PushBack({ 199, 80, 21, 29 }, 0, 0);
	playerinfo.walk.lock = true;
	playerinfo.walk.speed = 0.2f;

	playerinfo.jump.PushBack({62, 181, 15, 30},0,0);
	playerinfo.jump.PushBack({ 82, 182, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 105, 182, 15, 30 }, 0, 0);
	playerinfo.jump.PushBack({ 127, 182, 15, 30 }, 0, 0);
	playerinfo.jump.PushBack({ 150, 182, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 171, 182, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 190, 180, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 213, 180, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 235, 179, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 254, 180, 15, 31 }, 0, 0);
	playerinfo.jump.PushBack({ 276, 180, 15, 31 }, 0, 0);
	playerinfo.jump.PushBack({ 21, 180, 15, 30 }, 0, 0);
	playerinfo.jump.PushBack({ 41, 181, 15, 30 }, 0, 0);
	playerinfo.jump.lock = false;
	playerinfo.jump.speed = 0.5f;

	playerinfo.death.PushBack({11, 110, 11, 28},0,0);
	playerinfo.death.PushBack({28, 117, 19, 24}, 0, 0);
	playerinfo.death.PushBack({49, 120, 23, 19}, 0, 0);
	playerinfo.death.PushBack({74, 125, 26, 16}, 0, 0);
	playerinfo.death.PushBack({101, 128, 27, 13}, 0, 0);
	playerinfo.death.PushBack({ 130, 135, 34, 6 }, 0, 0);
	playerinfo.death.lock = true;
	playerinfo.death.speed = 0.1f;

	playerinfo.voltereta.PushBack({110, 148, 20, 26}, 0, 0);
	playerinfo.voltereta.PushBack({134, 150, 25, 22}, 0, 0);
	playerinfo.voltereta.PushBack({162, 159, 24, 13}, 0, 0);
	playerinfo.voltereta.PushBack({189, 158, 17, 13}, 0, 0);
	playerinfo.voltereta.PushBack({211, 158, 16, 14}, 0, 0);
	playerinfo.voltereta.PushBack({230, 159, 15, 13}, 0, 0);
	playerinfo.voltereta.PushBack({250, 160, 15, 12}, 0, 0);
	playerinfo.voltereta.PushBack({266, 158, 16, 14}, 0, 0);
	playerinfo.voltereta.PushBack({282, 162, 16, 10 }, 0, 0);
	playerinfo.voltereta.PushBack({9, 159, 15, 14}, 0, 0);
	playerinfo.voltereta.PushBack({27, 158, 15, 15}, 0, 0);
	playerinfo.voltereta.PushBack({46, 155, 17, 19}, 0, 0);
	playerinfo.voltereta.PushBack({67, 149, 16, 25}, 0, 0);
	playerinfo.voltereta.lock = true;
	playerinfo.voltereta.speed = 0.3f;

}

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& config)
{
	bool ret = true;
	file.create(config.child("load").attribute("docname").as_string());
	return ret;
}


bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	pugi::xml_parse_result result = playerinfo.playerdoc.load_file(file.GetString());
	playerinfo.position.x = 0;
	playerinfo.position.y = 0;
	playerinfo.playernode = playerinfo.playerdoc.child("player");

	graphics=App->tex->Load("sprites/character.png");
    //sets initial position from xml
	playerinfo.position.x = playerinfo.playernode.child("position_x").attribute("x").as_int();
	playerinfo.position.y = playerinfo.playernode.child("position_y").attribute("y").as_int();
	
    playerinfo.player = App->collision->AddCollider({ playerinfo.position.x, playerinfo.position.y ,10 ,10}, COLLIDER_PLAYER1, this);
	return ret;
}


bool j1Player::Update()
{
	bool ret = true;
	
	int speed = 1;
	float speed_y = 2.5f;

	if (playerinfo.current_animation->Finished() || playerinfo.current_animation->lock == false) {

		if (playerinfo.current_animation->Finished()) {
			playerinfo.current_animation->Reset();
		}

		playerinfo.current_animation = &playerinfo.idle;

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			playerinfo.current_animation = &playerinfo.walk;
			position.x += speed;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			playerinfo.current_animation = &playerinfo.walk;
			position.x -= speed;
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
			playerinfo.current_animation = &playerinfo.jump;
			jumping = JUMP_UP;
		}
	}

	if (jumping == JUMP_DOWN)
	{
		position.y += (int)speed_y;
		//speed_y -= 0.3f;
		if (position.y >= 112) {
			jumping = JUMP_NOT;
			position.y = 112;
			//speed = 1.5f;
		}
	}
	if (jumping == JUMP_UP)
	{
		position.y -= (int)speed_y;
		//speed_y += 0.3f;
		if (playerinfo.current_animation->current_frame >= 2.5f) {
			jumping = JUMP_DOWN;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = playerinfo.current_animation->GetCurrentFrame();

	//App->player->SetPos(position.x, position.y);

	App->render->Blit(graphics, playerinfo.position.x, playerinfo.position.y, &r, 1.0f, playerinfo.player_flip);

	return ret;
}

bool j1Player::CleanUp() {

	if (graphics != nullptr) {
		SDL_DestroyTexture(graphics);
		graphics = nullptr;
	}
	
	return true;

}
