#pragma once
#include <raylib.h>
#include <raymath.h>

struct Circle{
    Vector2 center;
    float r;
};



struct Entity{
    Rectangle sprite;
    Vector2 velocity;
    Vector2 acceleration;

    // the hitbox of attacks
    Rectangle hitbox;
    bool isAttacking;
    // the hitbox of the entity
    Circle hurtbox;

    int state;
    

    Entity(){}
    Entity(Rectangle spriteRect){
        velocity = {0,0};
        acceleration = {0,0};
        sprite = spriteRect;
    }

    void addVelocity(Vector2 v){
        velocity.x += v.x;
        velocity.y += v.y;
    }

    void update(float deltaTime){
        float dx = velocity.x * deltaTime;
        float dy = velocity.y * deltaTime;

        sprite.x += dx;
        hitbox.x += dx;
        hurtbox.center.x += dx;
        sprite.y += dy;
        hitbox.y += dy;
        hurtbox.center.y += dy;

        velocity.x *= 0.9;
        velocity.y *= 0.9;
    }

};
