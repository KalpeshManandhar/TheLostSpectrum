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
        180,120
    };
    Rectangle b = {
    100,100,
    97,100
    };
    // t.slime = slimeAnimate();
    t->slime1 = Slime(r);
    t->slime1.loadAnimations();

    t->player = Player(p);
    t->player.loadPlayerAnimations();


    t->wizard = Wizard(b);
    t->wizard.loadWizardAnimations();

    t->npc = NPC();
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

    t->slime1.animate(&t->c,deltaTime);
    t->wizard.animate(&t->c,deltaTime);
    
    t->npc.animate(&t->c,deltaTime);

    //t->boss.animate(&t->c, deltaTime);
    // DialogueBox db;

    // db.renderDialogue("I am mad scientist. It's so cool. Sonuvabitch", deltaTime);
}

void testFixedLoop(TestData *t, float deltaTime){
    t->slime1.update(deltaTime);
    t->wizard.update(deltaTime);
    t->player.update(deltaTime);
    t->npc.update(deltaTime);
    //t->boss.update(deltaTime);
    //t->boss.update(deltaTime);

    if (circleCircleCollisionCheck(t->slime1.hurtbox, t->player.hurtbox)) {
        Vector2 r = resolveCircleCollision(t->slime1.hurtbox, t->player.hurtbox);
        t->slime1.updatePos(r);
    }
}

