#pragma once

#include "entity.h"
#include "camera.h"
#include "animation.h"
#include "camera.h"

struct Slime: public Entity{
    AnimationSheet ani;

    bool isActive;
    float attackCooldown;
    float attackTimer;
    int damageCount;

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
        isActive = true;
        attackCooldown = 5.0f;
        attackTimer = 0.0f;
        damageCount = 0;
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
                addVelocity(Vector2{ 0,-25.0f });
            }
            else if (IsKeyDown(KEY_S)) {
                addVelocity(Vector2{ 0, 25.0f });
            }
            if (IsKeyDown(KEY_A)) {
                addVelocity(Vector2{ -25.0f,0 });
                direction = 0;
            }
            else if (IsKeyDown(KEY_D)) {
                addVelocity(Vector2{ 25.0f,0 });
                direction = 1;
            }
    }

    void attack(){
        isAttacking = true;
    }
    
    void takeDamage(FollowCamera* c, float deltaTime){
        Rectangle r = c->toScreenSpace(sprite);
        ani.addAnimation("hurt", 13, 4, false);
        damageCount++;
    }

    void resolveChanges(){
        state = States::SLIME_IDLE;
    }

    void playDead(FollowCamera* c, float deltaTime) {
        Rectangle r = c->toScreenSpace(sprite);
        ani.playAnimation("die", deltaTime, r, direction);
    }

    void animate(FollowCamera *c, float deltaTime){
        Rectangle r = c->toScreenSpace(sprite);

        if(isActive) {
            switch (state) {
            case SLIME_IDLE:
                ani.playAnimation("idle", deltaTime, r, direction);
                break;
            case SLIME_MOVE:
                ani.playAnimation("move", deltaTime, r, direction);
                break;
            case SLIME_ATTACK:
                if (ani.playAnimation("attack", deltaTime, r, direction)) {
                    isAttacking = false;
                }
                attackTimer = attackCooldown;
                break;
            case SLIME_DIE:
                ani.playAnimation("die", deltaTime, r, direction);
                break;
            case SLIME_HURT:
                ani.playAnimation("attack", deltaTime, r, direction);
                break;

            default:
                break;
            }
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
    Player(Rectangle sprite) : Entity (sprite) {

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

        anim.setFPS(12);
    }

    void move() {
        if (IsKeyDown(KEY_W)) {
            addVelocity(Vector2{ 0,-25.0f });
        }
        else if (IsKeyDown(KEY_S)) {
            addVelocity(Vector2{ 0, 25.0f });
        }
        if (IsKeyDown(KEY_A)) {
            addVelocity(Vector2{ -25.0f,0 });
            direction = 0;
        }
        else if (IsKeyDown(KEY_D)) {
            addVelocity(Vector2{ 25.0f,0 });
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

    void animate(FollowCamera* camera, float deltaTime) {
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

struct compass : public Entity {
    AnimationSheet anim;

    enum States {
        COMPASS_IDLE,
    };

    compass() {}
    compass(Rectangle sprite) : Entity(sprite) {

        state = States::COMPASS_IDLE;
        direction = 1;



    }

    void loadCompass() {
        anim = AnimationSheet("./assets/compassbg.png", 67, 68);
        /*anim.addAnimation("idle", 0, 8, true);*/
        anim.addAnimation("idle", 0,54 , true);
        anim.setDefaultAnimation("idle");

        anim.setFPS(5);
    }
    void animate(float deltaTime) {
        Rectangle r = { 0,0,150, 150 };

        anim.playAnimation("idle", deltaTime, r, direction);
    }
};

struct Wizard : public Entity {
    AnimationSheet anim;
    float speed = 0;
    Vector2 position = { 120,120 };
    Entity _wizard;

    enum States {
        WIZARD_IDLE,
        WIZARD_MOVE,
        WIZARD_ATTACK,
        WIZARD_HURT,
        WIZARD_DIE,
        WIZARD_REVERSE
    };

    Wizard() {}
    Wizard(Rectangle sprite) : _wizard(sprite) {

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

    void animate(FollowCamera *camera, float deltaTime) {
        Rectangle r = camera->toScreenSpace(sprite);


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
    Entity _npc;

    enum States {
        NPC_IDLE
    };

    NPC() {}
    NPC(Rectangle sprite) : Entity (sprite) {

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

    void animate(FollowCamera *camera, float deltaTime) {
        Rectangle r = camera->toScreenSpace(sprite);

        anim.playAnimation("idle", deltaTime, r, direction);
    }
};

