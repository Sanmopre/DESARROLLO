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
#include "j1FadeToBlack.h"
#include "j1Map.h"
#include "j1Entity.h"
#include "j1EntityManager.h"

#include "Brofiler/Brofiler.h"



j1Player::j1Player(Types::PLAYER)
{
	name.create("player");

	playerinfo.idle.PushBack({ 163,11,12,30 }, 0, 0);
	playerinfo.idle.PushBack({ 185, 11,12 , 30 }, 0, 0);
	/*playerinfo.idle.PushBack({ 205, 12, 12,30 }, 0, 0);*/
	playerinfo.idle.PushBack({ 229, 11, 12, 30 }, 0, 0);
	playerinfo.idle.PushBack({ 251, 11, 10, 30 }, 0, 0);
	playerinfo.idle.PushBack({ 272, 11, 11, 30 }, 0, 0);
	playerinfo.idle.speed = 0.075f;
	playerinfo.idle.lock = true;

	playerinfo.idle2.PushBack({108, 351, 12, 30});
	playerinfo.idle2.PushBack({86, 351, 12, 30});
	playerinfo.idle2.PushBack({42, 351, 12, 30});
	playerinfo.idle2.PushBack({20, 351, 10, 30});
	playerinfo.idle2.PushBack({0,351, 11, 30});
	playerinfo.idle2.speed = 0.075f;
	playerinfo.idle2.lock = true;

	playerinfo.walk.PushBack({11, 79, 16, 29},0,0);
	playerinfo.walk.PushBack({ 36, 78, 12, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 52, 78, 13, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 69, 78, 20, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 89, 78, 22, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 111, 79, 16, 29 }, 0, 0);
	playerinfo.walk.PushBack({ 130, 78, 16, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 148, 78, 14, 30 }, 0, 0);
	playerinfo.walk.PushBack({ 164, 79, 15, 29 }, 0, 0);
	playerinfo.walk.PushBack({ 179, 80, 19, 28 }, 0, 0);
	playerinfo.walk.PushBack({ 199, 79, 21, 29 }, 0, 0);
	playerinfo.walk.lock = true;
	playerinfo.walk.speed = 0.325f;

	playerinfo.walk2.PushBack({222,420,16,29});
	playerinfo.walk2.PushBack({201, 419, 12, 30});
	playerinfo.walk2.PushBack({185, 419, 13, 30});
	playerinfo.walk2.PushBack({164, 419,20, 30});
	playerinfo.walk2.PushBack({139, 419, 22, 30});
	playerinfo.walk2.PushBack({122, 420, 16, 29});
	playerinfo.walk2.PushBack({102, 420, 16, 29});
	playerinfo.walk2.PushBack({86, 419, 14, 30});
	playerinfo.walk2.PushBack({70, 419, 15, 29});
	playerinfo.walk2.PushBack({51, 421, 19, 28});
	playerinfo.walk2.PushBack({28, 420, 21,29});
	playerinfo.walk2.lock = true;
	playerinfo.walk2.speed = 0.325f;

	playerinfo.jump.PushBack({62, 181, 15, 30},0,0);
	playerinfo.jump.PushBack({ 82, 181, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 105, 181, 15, 30 }, 0, 0);
	playerinfo.jump.PushBack({ 127, 181, 15, 30 }, 0, 0);
	playerinfo.jump.PushBack({ 150, 181, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 171, 181, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 190, 181, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 213, 181, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 235, 181, 15, 29 }, 0, 0);
	playerinfo.jump.PushBack({ 254, 181, 15, 31 }, 0, 0);
	playerinfo.jump.PushBack({ 276, 181, 15, 31 }, 0, 0);
	playerinfo.jump.PushBack({ 21, 181, 15, 30 }, 0, 0);
	playerinfo.jump.PushBack({ 41, 181, 15, 30 }, 0, 0);
	playerinfo.jump.lock = true;
	playerinfo.jump.speed = 0.155f;

	
	playerinfo.jump2.PushBack({276,420 ,15,29 });
	playerinfo.jump2.PushBack({254, 420, 15, 29});
	playerinfo.jump2.PushBack({339, 385, 15, 29});
	playerinfo.jump2.PushBack({316, 385, 15, 29});
	playerinfo.jump2.PushBack({294, 385, 15, 29});
	playerinfo.jump2.PushBack({275, 385, 16, 30});
	playerinfo.jump2.PushBack({253, 385, 15, 30});
	playerinfo.jump2.PushBack({358, 420, 15, 30});
	playerinfo.jump2.lock = true;
	playerinfo.jump2.speed = 0.155f;



	playerinfo.death.PushBack({11, 110, 11, 28},0,0);
	playerinfo.death.PushBack({28, 117, 19, 24}, 0, 0);
	playerinfo.death.PushBack({49, 120, 23, 19}, 0, 0);
	playerinfo.death.PushBack({74, 125, 26, 16}, 0, 0);
	playerinfo.death.PushBack({101, 128, 27, 13}, 0, 0);
	playerinfo.death.PushBack({ 130, 135, 34, 6 }, 0, 0);
	playerinfo.death.lock = true;
	playerinfo.death.speed = 0.4f;

	playerinfo.voltereta.PushBack({110, 148, 20, 26});
	playerinfo.voltereta.PushBack({134, 150, 25, 24});
	playerinfo.voltereta.PushBack({162, 159, 24, 13});
	playerinfo.voltereta.PushBack({189, 159, 17, 13});
	playerinfo.voltereta.PushBack({211, 158, 16, 14});
	playerinfo.voltereta.PushBack({230, 159, 15, 13});
	playerinfo.voltereta.PushBack({250, 160, 15, 12});
	playerinfo.voltereta.PushBack({266, 158, 16, 14});
	playerinfo.voltereta.PushBack({282, 162, 16, 10});
	playerinfo.voltereta.PushBack({9, 160, 15, 14});
	playerinfo.voltereta.PushBack({27, 159, 15, 15});
	playerinfo.voltereta.PushBack({46, 155, 17, 19});
	playerinfo.voltereta.PushBack({67, 149, 16, 25});
	playerinfo.voltereta.lock = true;

	playerinfo.voltereta.speed = 0.555f;

	playerinfo.voltereta2.PushBack({334, 458, 20, 26});
	playerinfo.voltereta2.PushBack({305, 460, 25, 24});
	playerinfo.voltereta2.PushBack({278, 469, 24, 13});
	playerinfo.voltereta2.PushBack({258, 469, 17, 13});
	playerinfo.voltereta2.PushBack({237, 468, 16, 14});
	playerinfo.voltereta2.PushBack({219, 469, 15, 13});
	playerinfo.voltereta2.PushBack({199, 470, 15, 12});
	playerinfo.voltereta2.PushBack({182, 468, 16, 14});
	playerinfo.voltereta2.PushBack({166, 472, 16, 10});
	playerinfo.voltereta2.PushBack({440, 470, 15, 14});
	playerinfo.voltereta2.PushBack({421, 469, 15, 15});
	playerinfo.voltereta2.PushBack({401, 465, 17, 19});
	playerinfo.voltereta2.PushBack({381, 459, 16, 25});
	playerinfo.voltereta2.lock = true;
	playerinfo.voltereta2.speed = 0.555f;


	playerinfo.attack.PushBack({1, 318, 43, 28});
	playerinfo.attack.PushBack({46, 320, 43, 26});
	playerinfo.attack.speed = 0.1f;
	playerinfo.attack.lock = true;

	playerinfo.attack2.PushBack({469, 0, 43, 28});
	playerinfo.attack2.PushBack({424, 0, 43, 26});
	playerinfo.attack2.speed = 0.1f;
	playerinfo.attack2.lock = true;
	

	//these are for the next delivery an especial attack :)

	/*playerinfo.attack.PushBack({ 113, 241, 15, 39 },0, 10);

	playerinfo.attack.PushBack({ 113, 241, 15, 39 });

	playerinfo.attack.PushBack({ 140, 241, 20, 35 });
	playerinfo.attack.PushBack({ 174, 241, 42, 31 });
	playerinfo.attack.PushBack({ 218, 241, 41, 25 });
	playerinfo.attack.PushBack({ 264, 241, 30, 27 });
	playerinfo.attack.PushBack({ 298, 241, 18, 31 });
	playerinfo.attack.lock = true;
	playerinfo.attack.speed = 0.475f;

	playerinfo.attack2.PushBack({455, 337, 41, 38});
	playerinfo.attack2.PushBack({414, 337, 41, 38});
	playerinfo.attack2.PushBack({369, 337, 41, 38});
	playerinfo.attack2.PushBack({324, 337, 41, 38});
	playerinfo.attack2.PushBack({276, 337, 41, 38});
	playerinfo.attack2.lock = true;
	playerinfo.attack2.speed = 0.275f;*/

	/*playerinfo.kick.PushBack({ 305, 254, 18, 31 });*/
	playerinfo.kick.PushBack({3, 285, 23, 29});
	playerinfo.kick.PushBack({36, 286, 27, 28});
	playerinfo.kick.lock = true;
	playerinfo.kick.speed = 0.1f;

	playerinfo.kick2.PushBack({442, 292, 23, 29});
	playerinfo.kick2.PushBack({405, 292, 27, 28});
	playerinfo.kick2.lock = true;
	playerinfo.kick2.speed = 0.1f;

}

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& config)
{
	bool ret = true;

	folder.create(config.child("folder").child_value());
	
	playerinfo.Spawn_X = config.child("initialPosition").attribute("x").as_int();
	playerinfo.Spawn_Y = config.child("initialPosition").attribute("y").as_int();
	
	playerinfo.MAX_X = config.child("speed").attribute("MAX_X").as_int();
	playerinfo.MAX_Y = config.child("speed").attribute("MAX_Y").as_float();

	playerinfo.Speed_X = config.child("speed").attribute("Speed_X").as_float();
	playerinfo.Speed_Y = config.child("speed").attribute("Speed_Y").as_float();
	playerinfo.Dash_Speed = config.child("speed").attribute("Dash_Speed").as_float();

	playerinfo.World_Gravity = config.child("World_Gravity").attribute("value").as_float();
	playerinfo.MAX_JUMP = config.child("speed").attribute("MAX_JUMP").as_int();
	playerinfo.Reducction_Speed = config.child("speed").attribute("Reducction_Speed").as_float();
	playerinfo.dashTime = config.child("Dash").attribute("dashTime").as_int();

	playerinfo.attackTime = config.child("Attack").attribute("Time").as_int();
	playerinfo.deathTime = config.child("Death").attribute("Time").as_int();

	node = config;
	return ret;
}


bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;


	graphics=App->tex->Load("sprites/pepe.png");
    //SETS POSITION POLAYER FROM XML
	playerinfo.position.x = playerinfo.Spawn_X;
	playerinfo.position.y = playerinfo.Spawn_Y;
    playerinfo.playerbody = App->collision->AddCollider({ playerinfo.position.x, playerinfo.position.y ,13 ,13}, COLLIDER_PLAYER1, this);
	playerinfo.playerhead = App->collision->AddCollider({ playerinfo.position.x , playerinfo.position.y - 15,5 ,3 }, COLLIDER_PLAYER1, this);
	playerinfo.playerfeet = App->collision->AddCollider({ playerinfo.position.x  , playerinfo.position.y + 10 ,3 ,2 }, COLLIDER_PLAYER1, this);

	playerinfo.enemy = App->collision->AddCollider({ 190  , 100 ,30 ,20 }, COLLIDER_ENEMY, this);
	
	return ret;
}

bool j1Player::PreUpdate()
{
	//PLAYER CONTROLS:
	Input.pressing_A = App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT;
	Input.pressing_S = App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT;
	Input.pressing_D = App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT;
	Input.pressing_W = App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT;
	Input.pressing_SPACE = App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN;
	Input.pressing_F = App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT;
	Input.pressing_E = App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN;
	Input.pressing_Q = App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT;


	return true;
}

bool j1Player::Update(float dt)
{

	BROFILER_CATEGORY("Player_Update", Profiler::Color::Blue)
		
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_REPEAT) { playerinfo.Alive = false; }
	
	if (playerinfo.God_Mode == false && playerinfo.Alive == true)
	{
		Player_State_Machine();
		switch (state) {
		case JUMP:
			playerinfo.Grounded = false;
			App->audio->PlayFx(App->audio->LoadFx("audio/fx/jumping.wav"));
			while (playerinfo.velocity.y > -2)
			{
				if (playerinfo.Looking_Forward == true)
				{
					playerinfo.current_animation = &playerinfo.jump;
					playerinfo.velocity.y -= playerinfo.Speed_Y;
				}
				else
				{
					playerinfo.current_animation = &playerinfo.jump2;
					playerinfo.velocity.y -= playerinfo.Speed_Y;
				}
				
				
			} 
			
			break;

		case BACKWARD:
			playerinfo.Looking_Forward = false;
			playerinfo.velocity.x -= playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.walk2;
			
			if (playerinfo.Grounded == false) { playerinfo.current_animation = &playerinfo.jump2; }
			break;

		case JUMP_BACKWARD:
			playerinfo.Looking_Forward = false;
			playerinfo.velocity.x -= playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.jump2;
			break;

		case FORWARD:
			playerinfo.Looking_Forward = true;
			playerinfo.velocity.x += playerinfo.Speed_X;
			playerinfo.current_animation = &playerinfo.walk;
			if (playerinfo.velocity.x == 0) {
				playerinfo.current_animation = &playerinfo.idle;
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

			if (playerinfo.Looking_Forward == true)
			{
				playerinfo.velocity.x = playerinfo.Dash_Speed;
				playerinfo.current_animation = &playerinfo.voltereta;
			}
			else
			{
				playerinfo.velocity.x = -playerinfo.Dash_Speed + 1;
				playerinfo.current_animation = &playerinfo.voltereta2;
			}
			playerinfo.velocity.y = 0;
			
			if (SDL_GetTicks() - playerinfo.dash_timer > playerinfo.dashTime)
			{
				playerinfo.Can_Input = true;
				playerinfo.dashTimer = false;
				playerinfo.voltereta.Reset();
				playerinfo.voltereta2.Reset();
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

			if (playerinfo.velocity.y == 0 && playerinfo.velocity.x == 0 && playerinfo.Looking_Forward==true)
			{
				playerinfo.current_animation = &playerinfo.idle;
			}
			/*if (playerinfo.velocity.y == 0 && playerinfo.velocity.x == 0 && playerinfo.Looking_Forward == false)
			{
				playerinfo.current_animation = &playerinfo.idle2;
			}*/
			break;
		
		case ATTACK_E:
			if (playerinfo.attackTimer == false)
			{
				playerinfo.attack_timer = SDL_GetTicks();
				playerinfo.attackTimer = true;
				playerinfo.attacking = true;
				App->audio->PlayFx(App->audio->LoadFx("audio/fx/E.wav"));
			
				//COLLIDER ATTACK
				if (playerinfo.Looking_Forward == false)
				{
					playerinfo.playerattack = App->collision->AddCollider({ playerinfo.position.x +30, playerinfo.position.y - 5,30 ,20 }, COLLIDER_ATTACK, this);
					playerinfo.current_animation = &playerinfo.attack2;
					playerinfo.attack.SetOffset(1, -20, 0);
					playerinfo.attack.SetOffset(2, -20, 0);
					
				}


				else
				{
					playerinfo.playerattack = App->collision->AddCollider({ playerinfo.position.x + 10, playerinfo.position.y - 5,30 ,20 }, COLLIDER_ATTACK, this);
					playerinfo.current_animation = &playerinfo.attack;
				}



				//MOVEMENT WHILE ATTACKING (CAN ATTACK JUMP BUT NOT RUN ATTACK)
				if(playerinfo.velocity.y == 0){
					playerinfo.velocity.x = 0;
				}
			}

	
			if (SDL_GetTicks() - playerinfo.attack_timer > playerinfo.attackTime)
			{
				playerinfo.Can_Input = true;
				playerinfo.attackTimer = false;

				playerinfo.attacking = false;
				App->collision->AttackCleanUp();
				playerinfo.attack.Reset();
			}
			else
			{
				playerinfo.Can_Input = false;
			}
		
			

			
			break;
		case KICK:
			if (playerinfo.attackTimer == false)
			{
				playerinfo.attack_timer = SDL_GetTicks();
				playerinfo.playerattack = App->collision->AddCollider({ playerinfo.position.x + 10, playerinfo.position.y + 20,25 ,10 }, COLLIDER_ATTACK, this);
				playerinfo.attackTimer = true;
				playerinfo.attacking = true;
				App->audio->PlayFx(App->audio->LoadFx("audio/fx/kick.wav"));
				
			}
			if (playerinfo.Looking_Forward == true)
			{
				playerinfo.current_animation = &playerinfo.kick;
				/*playerinfo.playerattack = App->collision->AddCollider({ playerinfo.position.x + 10, playerinfo.position.y,25 ,10 }, COLLIDER_ATTACK, this);*/
			}
			if(playerinfo.Looking_Forward==false)
			{
				playerinfo.current_animation = &playerinfo.kick2;
				playerinfo.playerattack = App->collision->AddCollider({ playerinfo.position.x +30, playerinfo.position.y,25 ,10 }, COLLIDER_ATTACK, this);
				App->collision->AttackCleanUp();
			}
			if (SDL_GetTicks() - playerinfo.attack_timer > playerinfo.attackTime)
			{
				playerinfo.Can_Input = true;
				playerinfo.attackTimer = false;
				playerinfo.attacking = false;
				App->collision->AttackCleanUp();

			}
			if (playerinfo.velocity.y == 0) {
				playerinfo.velocity.x = 0;
			}
			break;

		case DEAD:
			playerinfo.velocity.x = 0;
			playerinfo.velocity.y = 0;
			playerinfo.current_animation = &playerinfo.death;
			break;
		}
	
		
		
		
		//SPEED LIMITS AND ANIMATION FIXES
		if (state != DASH) {
			if (playerinfo.velocity.x > playerinfo.MAX_X) { playerinfo.velocity.x = playerinfo.MAX_X; }
			if (playerinfo.velocity.x < -playerinfo.MAX_X) { playerinfo.velocity.x = -playerinfo.MAX_X; }
		}
		if (playerinfo.velocity.y > playerinfo.MAX_Y) { playerinfo.velocity.y = playerinfo.MAX_Y; }
	
		Player_Position();

	


	}
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		playerinfo.God_Mode = !playerinfo.God_Mode;

	}

	if (playerinfo.God_Mode)
	{
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) { playerinfo.GodModeUp = true; }
		else if (App->input->GetKey(SDL_SCANCODE_I) == KEY_UP) { playerinfo.GodModeUp = false; }

		if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) { playerinfo.GodModeDown = true; }
		else if (App->input->GetKey(SDL_SCANCODE_K) == KEY_UP) { playerinfo.GodModeDown = false; }

		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) { playerinfo.GodModeForward = true; }
		else if (App->input->GetKey(SDL_SCANCODE_L) == KEY_UP) { playerinfo.GodModeForward = false; }

		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) { playerinfo.GodModeBackward = true; }
		else if (App->input->GetKey(SDL_SCANCODE_J) == KEY_UP) { playerinfo.GodModeBackward = false; }

		if (playerinfo.GodModeUp == true)
		{
			playerinfo.position.y = playerinfo.position.y - 8;
			if (playerinfo.GodModeForward == true)
			{
				playerinfo.position.x = playerinfo.position.x + 8;
			}
			if (playerinfo.GodModeBackward == true)
			{
				playerinfo.position.x = playerinfo.position.x - 8;
			}
			if (playerinfo.GodModeDown == true)
			{
				playerinfo.position.y = playerinfo.position.y + 8;
			}

		}

		else if (playerinfo.GodModeDown == true)
		{
			playerinfo.position.y = playerinfo.position.y + 8;
			if (playerinfo.GodModeForward == true)
			{
				playerinfo.position.x = playerinfo.position.x + 8;
			}
			if (playerinfo.GodModeBackward == true)
			{
				playerinfo.position.x = playerinfo.position.x - 8;
			}

		}

		else if (playerinfo.GodModeForward == true)
		{
			playerinfo.position.x = playerinfo.position.x + 8;
			if (playerinfo.GodModeBackward == true)
			{
				playerinfo.position.x = playerinfo.position.x - 8;
			}

		}

		else if (playerinfo.GodModeBackward == true)
		{
			playerinfo.position.x = playerinfo.position.x - 8;
			if (playerinfo.GodModeForward == true)
			{
				playerinfo.position.x = playerinfo.position.x + 8;
			}

		}
	}
	playerinfo.Grounded = false;

	if (playerinfo.Alive == false)
	{
		playerinfo.current_animation = &playerinfo.death;
		Restart();
	}

	//DRAW COLLIDER
	if (playerinfo.God_Mode == false) {
		playerinfo.playerbody->SetPos(playerinfo.position.x + 2, playerinfo.position.y);
		playerinfo.playerfeet->SetPos(playerinfo.position.x + 7, playerinfo.position.y + 18);
		playerinfo.playerhead->SetPos(playerinfo.position.x + 5, playerinfo.position.y - 4);
		if (playerinfo.attacking == true) {
			if (playerinfo.Looking_Forward) {
				playerinfo.playerattack->SetPos(playerinfo.position.x + 10, playerinfo.position.y - 5);
			}
			else {
				playerinfo.playerattack->SetPos(playerinfo.position.x - 20, playerinfo.position.y - 5);
			}
		}
	}
	App->render->Player_Camera(playerinfo.position.x, playerinfo.position.y + 10);
	
	//DRAW THE PLAYER BLIT
	
	
		if (App->render->camera.x < -550) {
			
			if (playerinfo.attacking == true && playerinfo.Looking_Forward == false) {
				App->render->Blit_Player(graphics, playerinfo.position.x  - 390, playerinfo.position.y - 20, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
			}
			else{
				App->render->Blit_Player(graphics, playerinfo.position.x - 350, playerinfo.position.y - 20, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
			}
		}
		if (App->render->camera.x > -550) {

			if (playerinfo.attacking == true && playerinfo.Looking_Forward == false) {
				App->render->Blit_Player(graphics, playerinfo.position.x + 15, playerinfo.position.y - 20, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
			}
			else {
				App->render->Blit_Player(graphics, playerinfo.position.x + 55, playerinfo.position.y - 20, &(playerinfo.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);
			}
		}
	


	return true;
}

void j1Player::Player_State_Machine()
{
	if (playerinfo.Can_Input == true && playerinfo.God_Mode == false)
	{
		if (Input.pressing_SPACE && playerinfo.velocity.y == 0)
		{
			state = JUMP;
			if (playerinfo.Looking_Forward == true) { playerinfo.current_animation = &playerinfo.jump; }
			else { playerinfo.current_animation = &playerinfo.jump2; }
		}

		else if (Input.pressing_F && playerinfo.Dash == false)
		{
			state = DASH;
			playerinfo.Dash = true;
		}

		else if (Input.pressing_E)
		{
			state = ATTACK_E;
			
		
		}

		else if (Input.pressing_Q)
		{
			state = KICK;
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

		else if (playerinfo.Alive == false) {
			state = DEAD;
		}

		

		else
		{
			state = IDLE;
			if (playerinfo.Looking_Forward == true) { playerinfo.current_animation = &playerinfo.idle; }
			else { playerinfo.current_animation = &playerinfo.idle2; }
			
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

		App->collision->AttackCleanUp();
		App->fade->Fade_To_Black(1);
		playerinfo.Can_Input = false;

		if (playerinfo.deathTimer == false)
		{
			playerinfo.death_timer = SDL_GetTicks();
			playerinfo.deathTimer = true;

		}

		if (SDL_GetTicks() - playerinfo.death_timer > playerinfo.deathTime)
		{
		playerinfo.Can_Input = true;
		playerinfo.deathTimer = false;	
		playerinfo.position.x = playerinfo.Spawn_X;
		playerinfo.position.y = playerinfo.Spawn_Y;
		playerinfo.velocity.y = 0;
		playerinfo.velocity.x = 0;
		playerinfo.Looking_Forward = true;	
		playerinfo.Alive = true;
		App->audio->PlayFx(App->audio->LoadFx("audio/fx/death.wav"));
		playerinfo.current_animation = &playerinfo.death;
		}
		else {
			playerinfo.Can_Input = false;
			playerinfo.velocity.x = 0;
			playerinfo.velocity.y = 0;
		}
	
	}
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
				playerinfo.position.y -= 3;
			}

			playerinfo.Grounded = true;
		}

	}

	if (c1 == playerinfo.playerhead && c2->type == COLLIDER_PLATFORM)
	{
		if ((playerinfo.playerhead->rect.y) < (c2->rect.y + c2->rect.h))
		{
			playerinfo.position.y = playerinfo.position.y + 7;
		}
	}

	if (c1 == playerinfo.playerbody && c2->type == COLLIDER_PLATFORM)
	{
		if (state == DASH)
		{
			if (playerinfo.playerbody->rect.x + playerinfo.playerbody->rect.w > c2->rect.x && playerinfo.playerbody->rect.x < c2->rect.x) {
				playerinfo.position.x = playerinfo.position.x - 7;

			}
			if (playerinfo.playerbody->rect.x < c2->rect.x + c2->rect.w && playerinfo.playerbody->rect.x > c2->rect.x)
			{
				playerinfo.position.x = playerinfo.position.x + 7;
			}
		}
		else
		{
			if (playerinfo.playerbody->rect.x + playerinfo.playerbody->rect.w > c2->rect.x && playerinfo.playerbody->rect.x < c2->rect.x) {
				playerinfo.position.x = playerinfo.position.x - 4;

			}
			if (playerinfo.playerbody->rect.x < c2->rect.x + c2->rect.w && playerinfo.playerbody->rect.x > c2->rect.x)
			{
				playerinfo.position.x = playerinfo.position.x + 4;
			}
		}
	}
	
	if (c1 == playerinfo.playerbody && c2->type == COLLIDER_DEATH)
	{
		if (state == DASH)
		{
			if (playerinfo.playerbody->rect.x + playerinfo.playerbody->rect.w > c2->rect.x && playerinfo.playerbody->rect.x < c2->rect.x) {
				playerinfo.Alive = false;

			}
			if (playerinfo.playerbody->rect.x < c2->rect.x + c2->rect.w && playerinfo.playerbody->rect.x > c2->rect.x)
			{
				playerinfo.Alive = false;
			}
		}
		else
		{
			if (playerinfo.playerbody->rect.x + playerinfo.playerbody->rect.w > c2->rect.x && playerinfo.playerbody->rect.x < c2->rect.x) {
				playerinfo.Alive = false;

			}
			if (playerinfo.playerbody->rect.x < c2->rect.x + c2->rect.w && playerinfo.playerbody->rect.x > c2->rect.x)
			{
				playerinfo.Alive = false;
			}
		}
	}



	if (c1 == playerinfo.playerfeet && c2->type == COLLIDER_DEATH)
	{
		if ((playerinfo.playerfeet->rect.y + playerinfo.playerfeet->rect.h) > (c2->rect.y))
		{
			playerinfo.Alive = false; 
			playerinfo.Can_Input = false;
		}

	}

	if (c1 == playerinfo.playerhead && c2->type == COLLIDER_DEATH)
	{
		if ((playerinfo.playerhead->rect.y + playerinfo.playerhead->rect.h) > (c2->rect.y))
		{
			playerinfo.Alive = false;
			
		}

	}

	if (c1 == playerinfo.playerhead && c2->type == COLLIDER_WIN)
	{
		if ((playerinfo.playerhead->rect.y + playerinfo.playerhead->rect.h) > (c2->rect.y))
		{
			App->scene->actual_map = App->scene->Change_Map(2);

		}

	}


	if (c1 == playerinfo.playerbody && c2->type == COLLIDER_ENEMY)
	{
		if ((playerinfo.playerbody->rect.y + playerinfo.playerbody->rect.h) > (c2->rect.y))
		{
			playerinfo.Alive = false;
		}

	}

	}

bool j1Player::Save(pugi::xml_node& data) 
{
	//PLAYER POSITION
	LOG("Loading player state");
	playerinfo.position.x = data.child("position").attribute("X").as_int();
	playerinfo.position.y = data.child("position").attribute("Y").as_int();
	return true;
}

bool j1Player::Load(pugi::xml_node& data)
{
	//PLAYER POSITION
	LOG("Loading player state");
	playerinfo.position.x = data.child("position").attribute("X").as_int();
	playerinfo.position.y = data.child("position").attribute("Y").as_int();
	return true;
}

bool j1Player::CleanUp() {

	//DESTROY GRAPHICS
	
	if (graphics != nullptr) {
		SDL_DestroyTexture(graphics);
		graphics = nullptr;
	}
	//App->collision->

	return true;

}
