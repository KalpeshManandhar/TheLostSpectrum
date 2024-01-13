#pragma once
#include <raylib.h>
#include <raymath.h>
#include "geometry.h"

#define ZY_FACTOR 1.0f



struct Entity{
    Rectangle sprite;
    Vector2 velocity;

    // the hitbox of attacks
    Circle hitbox;
    // the hitbox of the entity
    Circle hurtbox;

    int state;
    int direction;
    int health;

    float attackCooldown;
    float attackTimer;
    
    unsigned int bosslives;
    bool isActive;
    bool isAttacking;
    bool isVulnerable;
    bool isHurt;
    float invulnerableTime;

    Entity(){}
    Entity(Rectangle spriteRect){
        velocity = {0,0};
        sprite = spriteRect;

        attackCooldown = 5.0f;
        attackTimer = 0.0f;
        hurtbox.center.x = sprite.x + 0.5 * sprite.width; 
        hurtbox.center.y = 0; 
        hurtbox.center.z = sprite.y / ZY_FACTOR; 
        hurtbox.r = sprite.width * 0.2;
    }

    void addVelocity(Vector2 v){
        velocity.x += v.x;
        velocity.y += v.y;
    }

    void updatePos(Vector2 v){
        hurtbox.center.x += v.x;
        hurtbox.center.z += v.y;
        hurtbox.center.y += v.y * ZY_FACTOR;
        
        sprite.x += v.x;
        sprite.y += v.y * ZY_FACTOR;
    }

    void update(float deltaTime){
        float dx = velocity.x * deltaTime;
        float dz = velocity.y * deltaTime;
        float dy = dz * ZY_FACTOR;

        sprite.x += dx;
        sprite.y += dy;
        hurtbox.center.x += dx;
        hurtbox.center.y += dy;
        hurtbox.center.z += dz;

        velocity.x *= 0.9;
        velocity.y *= 0.9;
    }

};
