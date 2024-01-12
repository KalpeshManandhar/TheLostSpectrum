#pragma once

#include <raylib.h>
#include <../src/core/animation.h>
#include <../src/core/entity.h>
#include <../src/core/camera.h>

class player:public Entity
{
	AnimationSheet anim;
	Vector2 position = { 120,120 };
	float speed=0;
	Vector2 size = { 16,16 };

public:
	enum States {
		STATE_IDLE,
		STATE_MOVE,
		STATE_ATTACK,
		STATE_HURT,
		STATE_DIE,
		STATE_REVERSE
	};

	player(): Entity({120 , 120, 16, 16}) {

			state = States::STATE_IDLE;
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
			anim = AnimationSheet("assets/player.png", 50, 37);
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
		if (IsKeyDown(KEY_A)) {
			addVelocity(Vector2{ -10.0f,0 });
		}
		if (IsKeyDown(KEY_S)) {
			addVelocity(Vector2{ 0, 10.0f });
		}
		if (IsKeyDown(KEY_D)) {
			addVelocity(Vector2{ 10.0f,0 });
		}

	}

	void resolveChanges() {
		state = States::STATE_IDLE;
		if (isAttacking || IsKeyDown(KEY_E)) {
			attack();
			state = States::STATE_ATTACK;

		}

		else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
			move();
			state = States::STATE_MOVE;
		}

		else if (IsKeyDown(KEY_A)) {
			move();
			state = States::STATE_REVERSE;
		}

	}

	void animate(FollowCamera* camera, float deltaTime) {
		Rectangle r = camera->toScreenSpace(sprite);

		switch (state) {
		case STATE_IDLE:
			anim.playAnimation("idle", deltaTime, r);
			break;
		case STATE_MOVE:
			anim.playAnimation("move", deltaTime, r);
			break;
		case STATE_REVERSE:
			anim.playAnimation("move", deltaTime, r, 0);
			break;
		case STATE_ATTACK:
			if (anim.playAnimation("attack", deltaTime, r)) {
				isAttacking = false;
			}
			break;
		case STATE_HURT:
			anim.playAnimation("attack", deltaTime, r);
			break;

		default:
			break;
		}
	}

};