#pragma once
#include "Point.h"
#include "Module.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;
struct SDL_Rect;
struct Collider;

class Player : public Module
{
private:

	iPoint position;
	SDL_Texture* playerText;
	SDL_Rect playerColl;
	fPoint speed;
	SDL_Rect textureRect;
	SDL_Rect colRect;
	Collider* playerCol;

public:

	// Constructor & destructor
	Player();
	~Player();

	// Module class methods
	bool Awake(pugi::xml_node& playerNode);
	void Init();
	bool Start();
	bool Update(float dt);
	bool CleanUp();


	// Getter to access the player information
	iPoint GetPlayerPosition();
	fPoint GetPlayerSpeed();

private:

	void Draw();
	void SetPlayerCollider();
	void OnCollision(Collider* c1, Collider* c2) override;




};