#pragma once

#include <raylib.h>
#include <../src/core/animation.h>
#include <../src/core/entity.h>
#include <../src/core/camera.h>

class player:public Entity
{

public:
	AnimationSheet anim;
	Vector2 position = { 120,120 };
	float speed=0;
	Vector2 size = { 16,16 };

	enum States {
		PLAYER_IDLE,
		PLAYER_MOVE,
		PLAYER_ATTACK,
		PLAYER_HURT,
		PLAYER_DIE,
		PLAYER_REVERSE
	};

	player(): Entity({120 , 120, 16, 16}) {

			state = States::PLAYER_IDLE;
			direction = 1;
	};


	void attack() {
		isAttacking = true;
	}

	void movementCheck()
	{
		if (IsKeyDown(KEY_RIGHT)) position.x += 5;
		if (IsKeyDown(KEY_LEFT)) position.x -= 5;
		if (IsKeyDown(KEY_DOWN)) position.y += 5;
		if (IsKeyDown(KEY_UP)) position.y -= 5;
	}

	void draw()
	{
		//DrawRectangleV({position.x - camerapos.x, position.y - camerapos.y}, size, RED);
	}

	void playerInit() {
			anim = AnimationSheet("./assets/player.png", 50, 37);
			anim.addAnimation("idle", 0, 4, true);
			anim.addAnimation("idle2", 38, 4, true);
			anim.addAnimation("move", 9, 6, true);
			anim.addAnimation("attack", 39, 11, false);
			anim.setDefaultAnimation("idle");

			anim.setFPS(7);
	}

	void move() {
		if (IsKeyDown(KEY_W)) {
			addVelocity(Vector2{ 0,-10.0f });
		}
		else if (IsKeyDown(KEY_S)) {
			addVelocity(Vector2{ 0, 10.0f });
		}
		if (IsKeyDown(KEY_A)) {
			addVelocity(Vector2{ -10.0f,0 });
			direction = 0;
		}
		else if (IsKeyDown(KEY_D)) {
			addVelocity(Vector2{ 10.0f,0 });
			direction = 1;
		}

	}

	void resolveChanges() {
		state = States::PLAYER_IDLE;
		if (isAttacking || IsKeyDown(KEY_E)) {
			attack();
			state = States::PLAYER_ATTACK;

		}

		else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
			move();
			state = States::PLAYER_MOVE;
		}

	}

	void animatep(FollowCamera* camera, float deltaTime) {
		Rectangle r = camera->toScreenSpace(sprite);

		switch (state) {
		case PLAYER_IDLE:
			anim.playAnimation("idle", deltaTime, r, direction);
			break;
		case PLAYER_MOVE:
			anim.playAnimation("move", deltaTime, r, direction);
			break;
		case PLAYER_ATTACK:
			if (anim.playAnimation("attack", deltaTime, r, direction)) {
				isAttacking = false;
			}
			break;
		case PLAYER_HURT:
			anim.playAnimation("attack", deltaTime, r, direction);
			break;

		default:
			break;
		}
	}

};