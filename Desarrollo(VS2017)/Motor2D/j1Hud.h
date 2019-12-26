#ifndef __j1HUD_H__
#define __j1HUD_H__

#include "j1Timer.h"
#include <string>
#include <list>
#include "j1Animation.h"


class j1Button;
class j1Label;

struct _TTF_Font;
struct SDL_Texture;

class j1Hud
{
public:
	j1Hud();
	~j1Hud();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

public:

	char const *current_coins;

private:

	SDL_Texture* coins_tex = nullptr;

	std::list<j1Label*> labels_list;
	std::list<j1Button*> hud_buttons;

	

	SDL_Color color;

};

#endif // __j1HUD_H__