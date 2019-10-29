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

	playerinfo.playernode = playerinfo.playerdoc.child("player");

	graphics=App->tex->Load("sprites/pepe.png");
    //SETS POSITION POLAYER FROM XML
	playerinfo.position.x = playerinfo.playernode.child("position_x").attribute("x").as_int();
	playerinfo.position.y = playerinfo.playernode.child("position_y").attribute("y").as_int();
	
    playerinfo.player = App->collision->AddCollider({ playerinfo.position.x, playerinfo.position.y ,10 ,10}, COLLIDER_PLAYER1, this);
	return ret;
}

bool j1Player::PreUpdate()
{
	//PLAYER CONTROLS:
	playerinfo.Input.pressing_A = App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT;
	playerinfo.Input.pressing_S = App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT;
	playerinfo.Input.pressing_D = App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT;
	playerinfo.Input.pressing_W = App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT;
	playerinfo.Input.pressing_lshift = App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT;

	//GOD MODE:
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		if (playerinfo.GodMode == true)
		{
			playerinfo.GodMode = false;
		}
	}

	//SWITCH OF PLAYER STATES

	//RIGHT AND LEFT IS USEFULL LATER FOR KNOWING WHEN TO FLIP THE RENDER
	switch (state)
	{
	case IDLE:
		playerinfo.right = false;
		playerinfo.left = false;
		if (playerinfo.Input.pressing_W && playerinfo.air == false) 
		{
			playerinfo.jumpvel = 7.0f;
			state = JUMP;
			playerinfo.air = true;
		}
		else if (playerinfo.Input.pressing_D)
		{
			state = FORWARD;
		}
		else if (playerinfo.Input.pressing_A)
		{
			state = BACKWARD;
		}
		break;
	case FORWARD:
		
		if (!playerinfo.Input.pressing_D && playerinfo.right == false)
			state = IDLE;

		if (playerinfo.Input.pressing_W && playerinfo.air == false)
			state = JUMP_FORWARD;

		if (playerinfo.Input.pressing_lshift)
			state = DASH_RIGHT;

		if (playerinfo.Input.pressing_A)
		{
			playerinfo.position.x -= playerinfo.player_velocity;
			state = BACKWARD;
		}

		playerinfo.right = true;

		break;
	case BACKWARD:
		
		if (!playerinfo.Input.pressing_A && playerinfo.left == false)
			state = IDLE;

		if (playerinfo.Input.pressing_W && playerinfo.air == false)
			state = JUMP_BACKWARD;

		if (playerinfo.Input.pressing_lshift)
			state = DASH_LEFT;
        
		if (playerinfo.Input.pressing_D)
		{
			playerinfo.position.x -= playerinfo.player_velocity;
			state = FORWARD;
		}
		playerinfo.right = false;

		break;
	
	case JUMP:
		if (playerinfo.Input.pressing_D)
			state = JUMP_FORWARD;
		else if (playerinfo.Input.pressing_A)
			state = JUMP_BACKWARD;

		break;
	case JUMP_FORWARD:
		playerinfo.right = true;
		playerinfo.left = false;
		if (!playerinfo.Input.pressing_D)
			state = JUMP;
		break;
	case JUMP_BACKWARD:
		playerinfo.right = false;
		playerinfo.left = true;
		if (!playerinfo.Input.pressing_A)
			state = JUMP;

		playerinfo.right = false;

		break;
	case DASH_RIGHT:
		playerinfo.right = false;
		playerinfo.left = false;
		if (playerinfo.Input.pressing_A) {
			state = BACKWARD;
			playerinfo.player_velocity = 2.0f;
			
		}

		break;
	case DASH_LEFT:
		playerinfo.left = true;
		if (playerinfo.Input.pressing_D) {
			state = FORWARD;
			playerinfo.player_velocity = 2.0f;
		}
		break;
	}
	//DRAWS THE COLLIIDER IN THE NEW PLAYER POSITION
	playerinfo.player->SetPos(playerinfo.position.x, playerinfo.position.y);

	return true;
}

bool j1Player::Update(float dt)
{
	//UPDATE ANIMATIONS AND VELOCITIES
	switch (state)
	{
	case IDLE:
		playerinfo.current_animation = &playerinfo.idle;

		break;
	case FORWARD:
		playerinfo.current_animation = &playerinfo.walk;

		if (playerinfo.can_walk == true)
		{
			playerinfo.position.x += playerinfo.player_velocity;
			playerinfo.right = true;
		}
		else
			playerinfo.right = false;

		break;
	case BACKWARD:
		playerinfo.current_animation = &playerinfo.walk;

		if (playerinfo.can_walk == true)
		{
			playerinfo.position.x -= playerinfo.player_velocity;
			playerinfo.left = true;
		}
		else
			playerinfo.left = false;
		
		break;
	case JUMP:
			playerinfo.air = true;
			playerinfo.current_animation = &playerinfo.jump;
			playerinfo.position.y -= playerinfo.jumpvel;
		
			if (playerinfo.air == false) 
				state = IDLE;
		
		break;

	case DASH_RIGHT:
		playerinfo.current_animation = &playerinfo.voltereta;

		if (playerinfo.can_walk == true) {
			playerinfo.position.x += playerinfo.player_velocity * playerinfo.dash_multiplier;
		}
		
		break;
	case DASH_LEFT:
		playerinfo.current_animation = &playerinfo.voltereta;

		if (playerinfo.can_walk == true) {
			playerinfo.position.x -= playerinfo.player_velocity * playerinfo.dash_multiplier;
		}
			state = IDLE;
		
		break;
	}
	//IF GOD MODE, GRAVITY DOSEN'T AFFECT
	if (playerinfo.GodMode == false)
	{
		playerinfo.position.y -= playerinfo.gravity;
	}
	else if (playerinfo.GodMode == true)
	{
		playerinfo.gravity = 0.0f;
	}

	//DRAW THE PLAYER BLIT
	SDL_Rect r = playerinfo.current_animation->GetCurrentFrame();


	


	if (playerinfo.right = false) {
		App->render->Blit(graphics, playerinfo.position.x, playerinfo.position.y, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
	}
	else {
		App->render->Blit(graphics, playerinfo.position.x, playerinfo.position.y, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
	}
	return true;
}

bool j1Player::Save(pugi::xml_node& data) const 
{
	//PLAYER POSITION
	data.append_child("position").append_attribute("x") = playerinfo.position.x;
	data.child("position").append_attribute("y") = playerinfo.position.y;
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	//PLAYER POSITION
	playerinfo.position.x = data.child("position").attribute("x").as_int();
	playerinfo.position.y = data.child("position").attribute("y").as_int();
	return true;
}

bool j1Player::CleanUp() {

	//DESTROY GRAPHICS
	
	if (graphics != nullptr) {
		SDL_DestroyTexture(graphics);
		graphics = nullptr;
	}

	return true;

}
