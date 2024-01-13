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
        300,300
    };

    Rectangle p = {
        1500,500,
        180,120
    };

    Rectangle b = {
    100,100,
    200,200
    };

    Rectangle n = {
        1700, 500,
        94 * 1.5, 91 * 1.5
    };


    t->slime[0] = Slime(s0);
    t->slime[0].loadAnimations();
    t->slime[0].hurtbox.r *= 1.2;

    t->slime[1] = Slime(s1);
    t->slime[1].loadAnimations();
    t->slime[0].hurtbox.r *= 1.2;

    t->slime[2] = Slime(s2);
    t->slime[2].loadAnimations();
    t->slime[0].hurtbox.r *= 1.2;

    t->player = Player(p);
    t->player.loadPlayerAnimations();
    t->slime[0].hurtbox.r *= 1.5;

    t->wizard = Wizard();
    t->wizard.loadWizardAnimations();

    t->bossSlime = Slime(b);
    t->bossSlime.loadAnimations();
    t->slime[0].hurtbox.r *= 3.5;
    
    t->npc = NPC(n);
    t->npc.loadNPC();
    t->slime[0].hurtbox.r *= 1.5;
   
    t->comp = compass(c);
    t->comp.loadCompass();

    r.x += 100;

    t->c = FollowCamera(&t->player.sprite, 1280,720);
    t->backrect = {-300,-300, 2400,2400};
    return t;
}


void testLoop(TestData *t, float deltaTime){
    t->player.resolveChanges();
}

void testFixedLoop(TestData *t, float deltaTime){
    
    t->npc.update(deltaTime);
    t->slime[0].update(deltaTime);
    t->slime[1].update(deltaTime);
    t->slime[2].update(deltaTime);
    t->bossSlime.update(deltaTime);
    t->player.update(deltaTime);
    t->comp.update(deltaTime);

    if (circleCircleCollisionCheck(t->bossSlime.hurtbox, t->player.hurtbox)) {
        Vector2 r = resolveCircleCollision(t->bossSlime.hurtbox, t->player.hurtbox);
        t->bossSlime.updatePos(r);
        printf("bossSlime");
    }

    if (circleCircleCollisionCheck(t->npc.hurtbox, t->player.hurtbox)) {
        Vector2 r = resolveCircleCollision(t->player.hurtbox, t->npc.hurtbox);
        t->player.updatePos(r);
    }
}

void displaySlime(TestData* t, float deltaTime) {
    t->slime[0].animate(&t->c, deltaTime);
    t->slime[1].animate(&t->c, deltaTime);
    t->slime[2].animate(&t->c, deltaTime);

    t->wizard.animate(&t->c, deltaTime);

    t->npc.animate(&t->c, deltaTime);

    t->comp.animate( deltaTime);

    t->bossSlime.animate(&t->c, deltaTime);
}

TestData::~TestData()
{
    delete[] slime;
}
