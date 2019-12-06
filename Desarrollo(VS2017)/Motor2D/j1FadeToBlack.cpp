#include <math.h>
#include "p2Log.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Window.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "j1Player.h"

// Constructor
j1FadeToBlack::j1FadeToBlack()
{
	name.create("fadetoblack");
}

// Destructor
j1FadeToBlack::~j1FadeToBlack()
{}

bool j1FadeToBlack::Awake(pugi::xml_node&)
{
	bool ret = true;

	screen = { 0, 0, 5000 , 5000  };

	return ret;
}

bool j1FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool j1FadeToBlack::Update(float dt)
{

		if (current_step == Fade_State::NULL_FADE)
			return true;
	Uint32 time = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)time / (float)total_time);

	switch (current_step)
	{
	case Fade_State::FADE_TO_BLACK:
	{

		//App->player->playerinfo.Can_Input = false;
		if (time >= total_time)
		{
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = Fade_State::FADE_FROM_BLACK;
		}
	} break;

	case Fade_State::FADE_FROM_BLACK:
	{
		
		normalized = 1.0f - normalized;

		if (time >= total_time)
			current_step = Fade_State::NULL_FADE;
	} break;
	}

	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

bool j1FadeToBlack::Fade_To_Black(float time)
{
	bool ret = false;

	if (current_step == Fade_State::NULL_FADE)
	{
		current_step = Fade_State::FADE_TO_BLACK;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 500.0f);
		ret = true;
	}

	return ret;
}