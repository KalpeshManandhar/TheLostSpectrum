#include "tests.h"
#include "../core/animation.h"
#include "../core/slime.h"
#include "../core/collision.h"
#include "../core/dialogue.h"





AnimationSheet slimeAnimate(){
    AnimationSheet slime ("./assets/slime-Sheet.png", 32, 25);
    slime.addAnimation("idle", 0, 4);
    slime.setFPS(6);
    return slime;
}


TestData* testInit(){
    TestData* t;
    t= new TestData;

    Rectangle r = {
        0,0,
        200,150
    };
    Rectangle p = {
        200,200,
        149,100
    };
    Rectangle b = {
    100,100,
    97,100
    };
    // t.slime = slimeAnimate();
    t->slime1 = Slime(r);
    t->slime1.loadAnimations();

    t->player = Slime(p);
    t->player.loadPlayerAnimatios();


    //t->boss = Slime(b);
    //t->player.loadBossAnimation();


    //t->p = player();
    //t->p.playerInit();

    r.x += 100;

    t->c = FollowCamera(&t->player.sprite, 400,400);
    // t->c.target = {
    //     (t->slime1.sprite.x + t->slime1.sprite.width * 0.5f),
    //     (t->slime1.sprite.y + t->slime1.sprite.height * 0.5f)
    // };

    // t->c.rotation = 0;
    // t->c.offset = {1280*0.5,720*0.5};
    // t->c.zoom = 1.0f;
    

    t->backrect = {-300,-300, 2400,2400};
    return t;
}


void testLoop(TestData *t, float deltaTime){
    //t->slime1.resolveChanges();
    //t->p.resolveChanges();/*
    //t->boss.resolveChanges();*/
    t->player.resolveChanges();
}

void testDisplay(TestData *t, float deltaTime){
    t->c.update();

    t->slime1.animate(&t->c, deltaTime);
    //t->p.animate(&t->c, deltaTime);
    t->player.animate(&t->c, deltaTime);

    // DialogueBox db;

    // db.renderDialogue("I am mad scientist. It's so cool. Sonuvabitch", deltaTime);
}

void testFixedLoop(TestData *t, float deltaTime){
    t->slime1.update(deltaTime);
   // t->p.update(deltaTime);

    /*t->slime2.update(deltaTime);*/
    t->player.update(deltaTime);
    //t->boss.update(deltaTime);

    if (circleCircleCollisionCheck(t->slime1.hurtbox, t->player.hurtbox)) {
        printf("Overlap");
        Vector2 r = resolveCircleCollision(t->slime1.hurtbox, t->player.hurtbox);
        t->slime1.updatePos(r);
    }
}

