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

    t->slime = new Slime[4];
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
    0,0,
    200,150
    };

    Rectangle n = {
        1700, 500,
        94 * 1.5, 91 * 1.5
    };

    t->slime[0] = Slime(s0);
    t->slime[0].loadAnimations();
    t->slime[0].hurtbox.r *= 2;

    t->slime[1] = Slime(s1);
    t->slime[1].loadAnimations();
    t->slime[1].hurtbox.r *= 2;

    t->slime[2] = Slime(s2);
    t->slime[2].loadAnimations();
    t->slime[2].hurtbox.r *= 2;

    t->player = Player(p);
    t->player.loadPlayerAnimations();

    t->wizard = Wizard();
    t->wizard.loadWizardAnimations();

    t->slime[3] = Slime(b);
    t->slime[3].loadAnimations();
    t->slime[3].hurtbox.r *= 3;
    t->slime[3].bosslives = 30;
    
    t->npc = NPC(n);
    t->npc.loadNPC();
   
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
    t->slime[3].update(deltaTime);
    /* t->bossSlime.update(deltaTime);*/
    t->player.update(deltaTime);
    t->comp.update(deltaTime);

    if (circleCircleCollisionCheck(t->slime[3].hurtbox, t->player.hurtbox)) {
        Vector2 r = resolveCircleCollision(t->slime[3].hurtbox, t->player.hurtbox);
        //t->slime[3].updatePos(r);
       // printf("bossSlime");
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
    t->slime[3].animate(&t->c, deltaTime);
    //t->bossSlime.animate(&t->c, deltaTime);
    t->wizard.animate(&t->c, deltaTime);

    t->npc.animate(&t->c, deltaTime);

    t->comp.animate( deltaTime);

}

void updateSlimeBoss(Slime& s, float dt, Player &pl) {
    s.attackTimer += dt;
    //std::cout << "\n" << s.attackTimer << "\n";

    if (s.attackTimer >= s.attackCooldown) {

        s.isAttacking = true;
        s.state = s.SLIME_ATTACK;
        s.attackTimer = 0.0f;

    }
    else {
        s.isAttacking = false;
    }



    if (circleCircleCollisionCheck(s.hurtbox, pl.hurtbox)) {
        if (pl.isAttacking && s.isActive) {
            s.state = s.SLIME_HURT;
        }
    }

    if (s.bosslives <= 0 && s.isActive) {
        s.state = s.SLIME_DIE;
    }
}

TestData::~TestData()
{
    delete[] slime;
}
