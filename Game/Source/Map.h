#pragma once
#include "Point.h"
#include "Module.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
struct Collider;
struct SDL_Rect;

class Map : public Module
{
private:

	iPoint position;
	SDL_Texture* mapText;
	Collider* mapCol;
	SDL_Rect mapRect;

public:

	Map();
	~Map();

	bool Awake(pugi::xml_node& mapNode);
	void Init();
	bool Start();
	bool Update(float dt);
	bool CleanUp();

private:

	void Draw();

};