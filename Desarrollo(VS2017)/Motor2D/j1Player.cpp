#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Animation.h"
#include "j1Collision.h"



j1Player::j1Player()
{
	//aqui ponemos los pixeles y los pushback :)
	position.x = 0;
	position.y = 30;

	playerinfo.idle.PushBack({ 163,11,12,30 }, 0, 0);
	playerinfo.idle.PushBack({ 185, 11,12 , 30 }, 0, 0);
	playerinfo.idle.speed = 0.2f;
	playerinfo.idle.lock = true;
}


bool j1Player::Awake(pugi::xml_node& config)
{
	bool ret = true;
	file.create(config.child("load").attribute("docname").as_string());
	return ret;
}


bool j1Player::Start()
{
	bool ret = true;
	
	graphics = App->tex->Load("sprites/character.png");
	playerinfo.player = App->collision->AddCollider({ position.x, position.y ,10 ,10}, COLLIDER_PLAYER1, this);


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

	//App->render->Blit(graphics, position.x, position.y, &r, 1.0f, flip);

	return ret;
}

bool j1Player::CleanUp() {

	SDL_DestroyTexture(graphics);
	return true;

}