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
#include "j1Skeleton.h"
#include "j1Window.h"

#include "Brofiler/Brofiler.h"

j1Skeleton::j1Skeleton(int x, int y, Type type) :j1Entity(x, y, Type::GROUNDED_ENEMY)
{}
j1Skeleton::~j1Skeleton()
{}
bool j1Skeleton::Start()
{
	/*graphics = App->tex->Load("sprites/enemies.png");*/
}