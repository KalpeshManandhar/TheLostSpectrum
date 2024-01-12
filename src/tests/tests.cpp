#include "tests.h"
#include "../core/animation.h"
#include "../core/slime.h"
#include "../core/collision.h"


AnimationSheet slimeAnimate(){
    AnimationSheet slime ("./assets/slime-Sheet.png", 32, 25);
    slime.addAnimation("idle", 0, 4);
    slime.setFPS(6);
    return slime;
}


TestData testInit(){
    TestData t;
    Rectangle r = {
        0,0,
        200,150
    };
    // t.slime = slimeAnimate();
    t.slime1 = Slime(r);
    r.x += 100;
    t.slime2 = Slime(r);
    return t;
}


void testLoop(TestData *t, float deltaTime){
    t->slime1.resolveChanges();

    if (circleCircleCollisionCheck(t->slime1.hurtbox, t->slime2.hurtbox)){
        printf("Overlap");
        Vector2 r = resolveCircleCollision(t->slime1.hurtbox, t->slime2.hurtbox);
        t->slime1.updatePos(r);
    }

}

void testDisplay(TestData *t, float deltaTime){
    t->slime1.animate(deltaTime);
    t->slime2.animate(deltaTime);
}

void testFixedLoop(TestData *t, float deltaTime){
    t->slime1.update(deltaTime);
    t->slime2.update(deltaTime);
}

