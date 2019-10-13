/*
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
*/
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "ModulePlayer.h"
#include "Animation.h"


ModulePlayer::ModulePlayer()
{
	//position.x = ;
	//position.y = ;

}

ModulePlayer::~ModulePlayer()
{}


bool ModulePlayer::Start()
{
	bool ret = true;
	/*
	graphics = App->textures->Load("");
	player = App->collision->AddCollider({ position.x, position.y , ,  }, COLLIDER_PLAYER1, this);
*/

	return ret;
}


bool ModulePlayer::Update()
{
	bool ret = true;

	int speed = 1;
	float speed_y = 2.5f;

	if (current_animation->Finished() || current_animation->lock == false) {

		if (current_animation->Finished()) {
			current_animation->Reset();
		}

		current_animation = &idle;

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			current_animation = &forward;
			position.x += speed;
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			current_animation = &forward;
			position.x -= speed;
		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
			current_animation = &jump;
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
		if (current_animation->current_frame >= 2.5f) {
			jumping = JUMP_DOWN;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	//App->player->SetPos(position.x, position.y);

	//App->render->Blit(graphics, position.x, position.y, &r, 1.0f, flip);

	return ret;
}

bool ModulePlayer::CleanUp() {

	SDL_DestroyTexture(graphics);
	return true;

}