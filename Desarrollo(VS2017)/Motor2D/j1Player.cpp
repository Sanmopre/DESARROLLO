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
#include "j1Scene.h"



j1Player::j1Player()
{
	name.create("player");

	playerinfo.idle.PushBack({ 163,11,12,30 }, 0, 0);
	playerinfo.idle.PushBack({ 185, 11,12 , 30 }, 0, 0);
	//playerinfo.idle.PushBack({ 205, 12, 12,30 }, 0, 0);
	playerinfo.idle.PushBack({ 229, 10, 12, 30 }, 0, 0);
	playerinfo.idle.PushBack({ 251, 10, 10, 30 }, 0, 0);
	playerinfo.idle.PushBack({ 271, 10, 11, 30 }, 0, 0);
	playerinfo.idle.speed = 0.005f;
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
	playerinfo.walk.speed = 0.05f;

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
	playerinfo.jump.lock = true;
	playerinfo.jump.speed = 0.05f;

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
	playerinfo.voltereta.speed = 0.1f;

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
	//playerinfo.position.x = playerinfo.playernode.child("position_x").attribute("x").as_int();
	//playerinfo.position.y = playerinfo.playernode.child("position_y").attribute("y").as_int();
	
	playerinfo.position.x = 40;
	playerinfo.position.y = 350;
    playerinfo.playerbody = App->collision->AddCollider({ playerinfo.position.x, playerinfo.position.y ,10 ,10}, COLLIDER_PLAYER1, this);
	playerinfo.playerhead = App->collision->AddCollider({ playerinfo.position.x , playerinfo.position.y - 10,10 ,10 }, COLLIDER_PLAYER1, this);
	playerinfo.playerfeet = App->collision->AddCollider({ playerinfo.position.x , playerinfo.position.y + 10 ,10 ,10 }, COLLIDER_PLAYER1, this);
	return ret;
}

bool j1Player::PreUpdate()
{
	//PLAYER CONTROLS:
	Input.pressing_A = App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT;
	Input.pressing_S = App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT;
	Input.pressing_D = App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT;
	Input.pressing_W = App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT;
	Input.pressing_SPACE = App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT;
	Input.pressing_F = App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT;



	return true;
}

bool j1Player::Update(float dt)
{
	if (playerinfo.God_Mode == false)
	{
		Player_State_Machine();
		switch (state) {
		case JUMP:
			playerinfo.Grounded = false;
			App->audio->PlayFx(App->audio->LoadFx("audio/fx/jump.wav"));
			while (playerinfo.velocity.y > -2)
			{
				playerinfo.current_animation = &playerinfo.jump;
				playerinfo.velocity.y -= playerinfo.Speed_Y;
				
			}
			break;

		case BACKWARD:
			playerinfo.Looking_Forward = false;
			playerinfo.velocity.x -= playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.walk;
			if (playerinfo.Grounded)
			{
			}
			if (playerinfo.Grounded == false) { playerinfo.current_animation = &playerinfo.jump; }
			break;

		case JUMP_BACKWARD:
			playerinfo.Looking_Forward = false;
			playerinfo.velocity.x -= playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.jump;
			break;

		case FORWARD:
			playerinfo.Looking_Forward = true;
			playerinfo.velocity.x += playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.walk;
			if (playerinfo.Grounded)
			{

			}
			if (playerinfo.Grounded == false) { playerinfo.current_animation = &playerinfo.jump; }
			break;

		case JUMP_FORWARD:
			playerinfo.Looking_Forward = true;
			playerinfo.velocity.x += playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.jump;
			break;

		case DASH:
			if (playerinfo.dashTimer == false)
			{
				playerinfo.dash_timer = SDL_GetTicks();
				playerinfo.dashTimer = true;
			}

			if (playerinfo.Looking_Forward = true)
			{
				playerinfo.velocity.x = playerinfo.Dash_Speed;
			}
			else
			{
				playerinfo.velocity.x = -playerinfo.Dash_Speed;
			}
			playerinfo.velocity.y = 0;
			playerinfo.current_animation = &playerinfo.voltereta;
			if (SDL_GetTicks() - playerinfo.dash_timer > playerinfo.dashTime)
			{
				playerinfo.Can_Input = true;
				playerinfo.dashTimer = false;
			}
			else
			{
				playerinfo.Can_Input = false;
			}
			break;

		case IDLE:
		
			if (playerinfo.velocity.x != 0 && playerinfo.velocity.x > 0) { playerinfo.velocity.x = playerinfo.velocity.x - playerinfo.Reducction_Speed; }
			if (playerinfo.velocity.x != 0 && playerinfo.velocity.x < 0) { playerinfo.velocity.x = playerinfo.velocity.x + playerinfo.Reducction_Speed; }

			if (playerinfo.Grounded == false) { playerinfo.current_animation = &playerinfo.jump; }

			if (playerinfo.velocity.y == 0 && playerinfo.velocity.x == 0)
			{
				playerinfo.current_animation = &playerinfo.idle;
			}
			break;
		}
		
		//SPEED LIMITS
		if (state != DASH) {
			if (playerinfo.velocity.x > playerinfo.MAX_X) { playerinfo.velocity.x = playerinfo.MAX_X; }
			if (playerinfo.velocity.x < -playerinfo.MAX_X) { playerinfo.velocity.x = -playerinfo.MAX_X; }
		}
		if (playerinfo.velocity.y > playerinfo.MAX_Y) { playerinfo.velocity.y = playerinfo.MAX_Y; }

		Player_Position();

		if (playerinfo.Alive == false)
		{
			Restart();
		}

	}
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		playerinfo.God_Mode = !playerinfo.God_Mode;

	}

	if (playerinfo.God_Mode)
	{

	}
	playerinfo.Grounded = false;

	//DRAW COLLIDER
	playerinfo.playerbody->SetPos(playerinfo.position.x, playerinfo.position.y);
	playerinfo.playerfeet->SetPos(playerinfo.position.x, playerinfo.position.y + 15);
	playerinfo.playerhead->SetPos(playerinfo.position.x, playerinfo.position.y - 10);
	
	//DRAW THE PLAYER BLIT
	SDL_Rect r = playerinfo.current_animation->GetCurrentFrame();

	//if (playerinfo.Looking_Forward) {
		App->render->Blit(graphics, playerinfo.position.x, playerinfo.position.y - 245, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
	//}
	//else {
	//	App->render->Blit(graphics, playerinfo.position.x, playerinfo.position.y + 30, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_HORIZONTAL, -1.0);
	//}

	
	
	return true;
}

void j1Player::Player_State_Machine()
{
	if (playerinfo.Can_Input == true && playerinfo.God_Mode == false)
	{

		if (Input.pressing_SPACE && playerinfo.velocity.y == 0)
		{
			state = JUMP;
			playerinfo.jump.Reset();
		}

		else if (Input.pressing_F && playerinfo.Dash == false)
		{
			state = DASH;
			playerinfo.Dash = true;
		}

		else if (Input.pressing_D)
		{
			if (state == JUMP)
			{
				state = JUMP_FORWARD;
			}
			if (state != JUMP)
			{
				state = FORWARD;
			}
		}

		else if (Input.pressing_A)
		{
			if (state == JUMP)
			{
				state = JUMP_BACKWARD;
			}
			if (state != JUMP)
			{
				state = BACKWARD;
			}
		}

		else
		{
			state = IDLE;
		}
	}
}

void j1Player::Player_Position()
{
	playerinfo.velocity.y += playerinfo.World_Gravity;
	playerinfo.position.x = playerinfo.position.x + playerinfo.velocity.x;
	playerinfo.position.y = playerinfo.position.y + playerinfo.velocity.y;

	if (playerinfo.position.y > 1000 && playerinfo.God_Mode == false) { playerinfo.Alive = false; }
}

void j1Player::Restart()
{
	if (playerinfo.Alive == false) {
		playerinfo.Can_Input = false;

		playerinfo.position.x = 0;
		playerinfo.position.y = 0;
		playerinfo.velocity.y = 0;
		playerinfo.Looking_Forward = true;
	}
		playerinfo.Can_Input = true;
		playerinfo.Alive = true;
}


void j1Player::Set_Player_State(states stateP)
{
	state = stateP;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == playerinfo.playerfeet && c2->type == COLLIDER_PLATFORM)
	{
		if ((playerinfo.playerfeet->rect.y + playerinfo.playerfeet->rect.h) > (c2->rect.y))
		{
			playerinfo.velocity.y = 0;
			if (playerinfo.Dash == true)
			{
				playerinfo.Dash = false;
			}
			if ((playerinfo.playerfeet->rect.y + playerinfo.playerfeet->rect.h - 3) > (c2->rect.y))
			{
				playerinfo.position.y -= 2;
			}

			playerinfo.Grounded = true;
		}
		
	}

	if (c1 == playerinfo.playerbody && c2->type == COLLIDER_PLATFORM)
	{
		if ((playerinfo.playerbody->rect.y) < (c2->rect.y + c2->rect.h))
		{
			playerinfo.position.y = playerinfo.position.y + 2;
			playerinfo.velocity.y = 0;
		}
	}

	if (c1 == playerinfo.playerbody && c2->type == COLLIDER_PLATFORM)
	{
		if (state == DASH)
		{
			if (playerinfo.playerbody->rect.x + playerinfo.playerbody->rect.w > c2->rect.x && playerinfo.playerbody->rect.x < c2->rect.x) {
				playerinfo.position.x = playerinfo.position.x - 3;
				
			}
			if (playerinfo.playerbody->rect.x < c2->rect.x + c2->rect.w && playerinfo.playerbody->rect.x > c2->rect.x)
			{
				playerinfo.position.x = playerinfo.position.x + 4;
			}
		}
		else
		{
			if (playerinfo.playerbody->rect.x + playerinfo.playerbody->rect.w > c2->rect.x && playerinfo.playerbody->rect.x < c2->rect.x) {
				playerinfo.position.x = playerinfo.position.x - 2;
				//vel.x = 0;
			}
			if (playerinfo.playerbody->rect.x < c2->rect.x + c2->rect.w && playerinfo.playerbody->rect.x > c2->rect.x)
			{
				playerinfo.position.x = playerinfo.position.x + 2;
			}
		}
	}

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
