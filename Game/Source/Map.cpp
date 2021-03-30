#include "Map.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Collisions.h"


Map::Map()
{
	position = { 0, 7 };
}

Map::~Map()
{
}

bool Map::Awake(pugi::xml_node& mapNode)
{
	return true;
}

void Map::Init()
{
}

bool Map::Start()
{
	mapText = app->tex->Load("Assets/Textures/Stage1.png");
	mapRect = { 0, 185, 2500, 40 };
	mapCol = app->collisions->AddCollider(mapRect, ColliderType::COLLIDER_MAP, this);
	return true;
}

bool Map::Update(float dt)
{
	Draw();
	return true;
}

void Map::Draw()
{
	app->render->DrawTexture(mapText, position.x, position.y);
}

bool Map::CleanUp()
{
	return true;
}


