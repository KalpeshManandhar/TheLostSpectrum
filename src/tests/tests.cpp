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
    TestData* t = new TestData;

    t->slime = new Slime[3];
    t->tinySlimeHits = 0;

    Rectangle s0 = {
        2000, 700,
        100,75
    };

    Rectangle s1 = {
    2500, 900,
    100,75
    };

    Rectangle s2 = {
    3000, 800,
    100,75
    };

    Rectangle r = {
        1500,700,
        200,150    };

    Rectangle c = {
        0,0,
        100,100
    };

    Rectangle p = {
        1500,500,
        180,120
    };

    Rectangle b = {
    100,100,
    97,100
    };

    Rectangle n = {
        1700, 500,
        94 * 1.5, 91 * 1.5
    };


    t->slime[0] = Slime(s0);
    t->slime[0].loadAnimations();

    t->slime[1] = Slime(s1);
    t->slime[1].loadAnimations();

    t->slime[2] = Slime(s2);
    t->slime[2].loadAnimations();

    t->player = Player(p);
    t->player.loadPlayerAnimations();


    t->wizard = Wizard();
    t->wizard.loadWizardAnimations();

    t->npc = NPC(n);
    t->npc.loadNPC();

    //t->p = player();
    //t->p.playerInit();

    r.x += 100;

    t->c = FollowCamera(&t->player.sprite, 1280,720);
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

    t->slime[0].animate(&t->c, deltaTime);
    t->slime[1].animate(&t->c, deltaTime);
    t->slime[2].animate(&t->c, deltaTime);
    t->wizard.animate(&t->c,deltaTime);
    
    t->npc.animate(&t->c,deltaTime);

    //t->boss.animate(&t->c, deltaTime);
    // DialogueBox db;

    // db.renderDialogue("I am mad scientist. It's so cool. Sonuvabitch", deltaTime);
}

void testFixedLoop(TestData *t, float deltaTime){
    
    //t->wizard.update(deltaTime);
    t->npc.update(deltaTime);
    t->slime[0].update(deltaTime);
    t->slime[1].update(deltaTime);
    t->slime[2].update(deltaTime);
    t->player.update(deltaTime);
    //t->boss.update(deltaTime);
    //t->boss.update(deltaTime);

    if (circleCircleCollisionCheck(t->slime[0].hurtbox, t->player.hurtbox)) {
        Vector2 r = resolveCircleCollision(t->slime[0].hurtbox, t->player.hurtbox);
        //printf("sime1 collide");
        //t->slime[0].updatePos(r);
        //if (t->player.isAttacking)
        //{
        //    t->tinySlimeHits += 1;
        //    printf("hits = ", t->tinySlimeHits);
        //}
    }

    if (circleCircleCollisionCheck(t->npc.hurtbox, t->player.hurtbox)) {
        Vector2 r = resolveCircleCollision(t->player.hurtbox, t->npc.hurtbox);
        t->player.updatePos(r);
    }
}

void updateKill(bool hit) {


}

void deleteSlime(int index) {
    
}

TestData::~TestData()
{
    delete[] slime;
}
