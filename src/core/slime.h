#pragma once

#include "entity.h"
#include "camera.h"
#include "animation.h"
#include "camera.h"

struct Slime: public Entity{
    AnimationSheet ani;

    enum States {
        SLIME_IDLE,
        SLIME_MOVE,
        SLIME_ATTACK,
        SLIME_HURT,
        SLIME_DIE,
        SLIME_REVERSE
    };

    Slime(){}
    Slime(Rectangle sprite): Entity (sprite){

        state = States::SLIME_IDLE;
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

    }

    void attack(){
        isAttacking = true;
    }
    
    void takeDamage(){

    }

    void resolveChanges(){
        state = States::SLIME_IDLE;
    }

    void animate(float deltaTime){
        Rectangle r = { 0,0,32*2, 25*2 };

        switch (state){
        case SLIME_IDLE:
            ani.playAnimation("idle", deltaTime, r, direction);
            break;
        case SLIME_MOVE:
            ani.playAnimation("move", deltaTime, r, direction);
            break;
        case SLIME_ATTACK:
            if (ani.playAnimation("attack", deltaTime, r, direction)){
                isAttacking = false;
            }
            break;
        case SLIME_HURT:
            ani.playAnimation("attack", deltaTime, r, direction);
            break;
        
        default:
            break;
        }
    }


};

struct Player : public Entity {
    AnimationSheet anim;
    Vector2 position = { 120,120 };
    float speed = 0;
    Vector2 size = { 16,16 };

    enum States {
        PLAYER_IDLE,
        PLAYER_MOVE,
        PLAYER_ATTACK,
        PLAYER_HURT,
        PLAYER_DIE,
        PLAYER_REVERSE
    };

    Player() {}
    Player(Rectangle sprite) : Entity(sprite) {

        state = States::PLAYER_IDLE;
        direction = 1;



    }

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

    void loadPlayerAnimations() {
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

struct Wizard : public Entity {
    AnimationSheet anim;
    float speed = 0;
    Vector2 position = { 120,120 };

    enum States {
        WIZARD_IDLE,
        WIZARD_MOVE,
        WIZARD_ATTACK,
        WIZARD_HURT,
        WIZARD_DIE,
        WIZARD_REVERSE
    };

    Wizard() {}
    Wizard(Rectangle sprite) : Entity(sprite) {

        state = States::WIZARD_IDLE;
        direction = 1;



    }

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

    void loadWizardAnimations() {
        anim = AnimationSheet("./assets/wizard.png", 78, 80);
        /*anim.addAnimation("idle", 0, 8, true);*/
        anim.addAnimation("idle", 25, 32, true);
        anim.addAnimation("die", 25, 32, true);
        anim.addAnimation("move", 33, 40, true);
        anim.addAnimation("attack", 17, 24, false);
        anim.setDefaultAnimation("idle");

        anim.setFPS(6);
    }

    void move() {}

    void resolveChanges() {
        state = States::WIZARD_IDLE;
    }

    void animatew(float deltaTime) {
        Rectangle r = { 200,300,78*3,80*3};

        switch (state) {
        case WIZARD_IDLE:
            anim.playAnimation("idle", deltaTime, r, direction);
            break;
        case WIZARD_MOVE:
            anim.playAnimation("move", deltaTime, r, direction);
            break;
        case WIZARD_ATTACK:
            if (anim.playAnimation("attack", deltaTime, r, direction)) {
                isAttacking = false;
            }
            break;
        case WIZARD_HURT:
            anim.playAnimation("attack", deltaTime, r, direction);
            break;

        default:
            break;
        }
    }
};

struct NPC : public Entity {
    AnimationSheet anim;
    float speed = 0;

    enum States {
        NPC_IDLE
    };

    NPC() {}
    NPC(Rectangle sprite) : Entity(sprite) {

        state = States::NPC_IDLE;
        direction = 0;



    }

    void loadNPC() {
        anim = AnimationSheet("./assets/npcs/npc1.png", 94, 91);
        anim.addAnimation("idle", 0, 4, true);
        anim.setDefaultAnimation("idle");

        anim.setFPS(4);
    }

    void move() {
    }

    void resolveChanges() {
        state = States::NPC_IDLE;
    }

    void animateNPC(float deltaTime) {

        Rectangle r = { 700,300,94 * 1,91 * 1 };

        anim.playAnimation("idle", deltaTime, r, direction);
    }
};
