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
	void draw()
	{
		DrawRectangleV(position, size, RED);
	}

	void playerInit() {

	}
	void playerLoop() {

	}
};