#pragma once

#include "entity.h"
#include "animation.h"

struct Slime: public Entity{
    AnimationSheet ani;

    enum States{
        STATE_IDLE,
        STATE_MOVE,
        STATE_ATTACK,
        STATE_HURT,
        STATE_DIE
    };


    Slime(){}
    Slime(Rectangle sprite): Entity (sprite){
        loadAnimations();

        state = States::STATE_IDLE;
        direction = 1;

        

        
    }

    void loadAnimations(){
        ani = AnimationSheet("./assets/slime-Sheet.png", 32, 25);
        ani.addAnimation("idle", 0, 4, true);
        ani.addAnimation("move", 4, 4, true);
        ani.addAnimation("attack", 8, 5, false);
        ani.addAnimation("hurt", 13, 4, false);
        ani.addAnimation("die", 17, 4, false);
        ani.setDefaultAnimation("idle");

        ani.setFPS(6);
    }

    void move(){
        if (IsKeyDown(KEY_W)) {
            addVelocity(Vector2{0,-10.0f});
        }
        if (IsKeyDown(KEY_A)) {
            addVelocity(Vector2{-10.0f,0});
        }
        if (IsKeyDown(KEY_S)) {
            addVelocity(Vector2{0, 10.0f});
        }
        if (IsKeyDown(KEY_D)) {
            addVelocity(Vector2{10.0f,0});
        }

    }

    void attack(){
        isAttacking = true;
    }
    
    void takeDamage(){

    }

    void resolveChanges(){
        state = States::STATE_IDLE;
        if (isAttacking || IsKeyDown(KEY_E)){
            attack();
            state = States::STATE_ATTACK;
            
        }

        else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)){
            move();
            state = States::STATE_MOVE;
        }

    }

    void animate(float deltaTime){
        switch (state){
        case STATE_IDLE:
            ani.playAnimation("idle", deltaTime, sprite);
            break;
        case STATE_MOVE:
            ani.playAnimation("move", deltaTime, sprite);
            break;
        case STATE_ATTACK:
            if (ani.playAnimation("attack", deltaTime, sprite)){
                isAttacking = false;
            }
            break;
        case STATE_HURT:
            ani.playAnimation("attack", deltaTime, sprite);
            break;
        
        default:
            break;
        }
    }


};
