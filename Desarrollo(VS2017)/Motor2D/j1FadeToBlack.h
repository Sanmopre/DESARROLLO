#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleFadeToBlack : public j1Module
{
public:
	ModuleFadeToBlack();
	~ModuleFadeToBlack();

	bool Start();
	bool Update();
	bool j1FadeToBlack(j1Module* module_off, j1Module* module_on, int black = 1, float time = 1.0f);
	bool IsFading() const;

private:

	int blacks;

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	j1Module* to_enable = nullptr;
	j1Module* to_disable = nullptr;
};

#endif //__MODULEFADETOBLACK_H__