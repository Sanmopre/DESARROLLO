#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Collision.h"

j1Collision::j1Collision()
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_DEATH] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLATFORM] = false;
    
	
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PLATFORM] = true;


	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER1] = false;
	matrix[COLLIDER_PLAYER1][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_PLATFORM] = true;

	matrix[COLLIDER_WIN][COLLIDER_DEATH] = false;
	matrix[COLLIDER_WIN][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_WIN][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_WIN][COLLIDER_PLATFORM] = true;


	
}

// Destructor
j1Collision::~j1Collision()
{}

bool j1Collision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

// Called before render is available
bool j1Collision::Update(float dt)
{
	DebugDraw();

	return true;
}

void j1Collision::DebugDraw()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_PLATFORM: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER1: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;

		case COLLIDER_WIN: // yellow
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;

		case COLLIDER_ATTACK: // yellow
			App->render->DrawQuad(colliders[i]->rect, 254, 203, 0, alpha);
			break;

		case COLLIDER_DEATH: // purple
			App->render->DrawQuad(colliders[i]->rect, 102, 0, 153, alpha);
			break;

		case COLLIDER_ENEMY: // purple
			App->render->DrawQuad(colliders[i]->rect, 200, 200, 50, alpha);
			break;
		}
	}
}

// Called before quitting
bool j1Collision::CleanUp()
{

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			rect.x = rect.x ;
			rect.y = rect.y;
			rect.w = rect.w;
			rect.h = rect.h;
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w && rect.x + rect.w > r.x && rect.y < r.y + r.h && rect.h + rect.y > r.y);
}


//Deletes map colliders

bool j1Collision::MapCleanUp()
{

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			if (colliders[i]->type == COLLIDER_FLOOR || colliders[i]->type == COLLIDER_PLATFORM || colliders[i]->type == COLLIDER_DEATH || colliders[i]->type == COLLIDER_WIN)
			{
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}
	}

	return true;
}