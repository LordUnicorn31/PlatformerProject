#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Module.h"
#include "Log.h"
#include "Scene.h"
#include "Map.h"

Collisions::Collisions()
{
	name = "collisions";

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_PLAYER][COLLIDER_MAP] == true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] == true;
	
	matrix[COLLIDER_MAP][COLLIDER_PLAYER] == true;
	matrix[COLLIDER_MAP][COLLIDER_MAP] == true;

}

// Destructor
Collisions::~Collisions()
{}

void Collisions::Init()
{
	active = true;
}

bool Collisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->toDelete == true)
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

			if (c1->CheckCollision(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->callback && c1->active)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback && c2->active)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return 1;
}

// Called before render is available
bool Collisions::Update(float dt)
{

	DebugDraw();

	return 1;
}

void Collisions::DebugDraw()
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 140;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;
		if (colliders[i]->active)
		{
			switch (colliders[i]->type)
			{
			case COLLIDER_PLAYER: // green
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case COLLIDER_MAP:
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			}
		}
	}
}

// Called before quitting
bool Collisions::CleanUp()
{
	LOG("Freeing all colliders");

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

Collider* Collisions::AddCollider(SDL_Rect rect, ColliderType type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return SDL_HasIntersection(&rect, &r);
}