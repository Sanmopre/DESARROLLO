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

	return ret;
}

bool ModulePlayer::CleanUp() {

	SDL_DestroyTexture(graphics);
	return true;

}