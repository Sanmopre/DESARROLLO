#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

constexpr auto MAX_COLLIDERS = 275;


#include "j1Module.h"
#include "SDL/include/SDL_rect.h"


enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_FLOOR,
	COLLIDER_PLAYER1,
	COLLIDER_DEATH,
	COLLIDER_PLATFORM,
	COLLIDER_WIN,
	COLLIDER_ATTACK,
	COLLIDER_ENEMY,
	COLLIDER_SKELETON,
	COLLIDER_COIN,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool PreUpdate() override;
	bool Update(float) override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	void DebugDraw();
	bool MapCleanUp();
	bool AttackCleanUp();
	bool EnemyCleanUp();
	bool SkeletonCleanUp();
	bool CoinCleanUp();
	SDL_Rect rect;
	bool debug = false;
private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];

};

#endif // __ModuleCollision_H__