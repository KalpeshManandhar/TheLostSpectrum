#pragma once

#include <raylib.h>
class player
{
	Vector2 position = { 120,120 };
	float speed=0;
	Vector2 size = { 16,16 };

public:
	void movementCheck()
	{
		if (IsKeyDown(KEY_RIGHT)) position.x += 5;
		if (IsKeyDown(KEY_LEFT)) position.x -= 5;
		if (IsKeyDown(KEY_DOWN)) position.y += 5;
		if (IsKeyDown(KEY_UP)) position.y -= 5;
	}
	void draw(Vector2 camerapos)
	{
		DrawRectangleV({position.x - camerapos.x, position.y - camerapos.y}, size, RED);
	}
	
};