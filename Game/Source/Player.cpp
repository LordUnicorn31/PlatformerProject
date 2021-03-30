#include "Player.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Collisions.h"

Player::Player()
{
	position = { 70, 100 };
	speed = { 1.0f, 1.0f };
}

Player::~Player()
{

}

bool Player::Awake(pugi::xml_node& playerNode)
{
	return true;
}

void Player::Init()
{
	active = true;
}

bool Player::Start()
{
	playerText = app->tex->Load("Assets/Textures/Player.png");
	textureRect = { 0, 0, 32, 32 };
	colRect = { 0, 0, 30, 30 };
	playerCol = app->collisions->AddCollider(colRect, ColliderType::COLLIDER_PLAYER, this);
	return true;
}

bool Player::Update(float dt)
{
	// Gravity

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed.x;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed.x;
	}

	Draw();
	SetPlayerCollider();
	return true;
}

void Player::Draw()
{
	app->render->DrawTexture(playerText, position.x, position.y, &textureRect);
}

bool Player::CleanUp()
{
	app->tex->UnLoad(playerText);
	return true;
}

iPoint Player::GetPlayerPosition()
{
	return position;
}

fPoint Player::GetPlayerSpeed()
{
	return speed;
}

void Player::SetPlayerCollider()
{
	playerCol->SetPos(position.x, position.y);
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == ColliderType::COLLIDER_PLAYER && c2->type == ColliderType::COLLIDER_MAP)
	{
		speed.y = 0.0f;
	}
}
