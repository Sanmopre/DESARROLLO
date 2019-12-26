#include "j1Hud.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Gui.h"

j1Hud::j1Hud() {}

j1Hud::~j1Hud() {}

bool j1Hud::Start()
{
	
	coins_tex = App->tex->Load("textures/coin_tex.png");

	color = { 0,0,0,0 };

	return true;
}

bool j1Hud::Update(float dt)
{
	// HUD
	SDL_Rect hud_rect = { 0,0,342,256 };
	

	// Score
	/*current_coins = App->EntityManager->player->current_points.c_str();*/

	SDL_Rect temp;
	temp.x = temp.y = 0;
	temp.w = temp.h = 10;

	App->tex->Unload(coins_tex);
	coins_tex = App->fonts->Print(current_coins, color, App->fonts->default);
	App->render->BlitHUD(coins_tex, 900, 18, &temp, SDL_FLIP_NONE, false);


	return true;
}

bool j1Hud::CleanUp()
{
	return true;
}