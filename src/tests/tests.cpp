#include "tests.h"
#include "../core/animation.h"
#include "../core/slime.h"


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
    t.slime = Slime(r);
    return t;
}


void testLoop(TestData *t, float deltaTime){
    t->slime.resolveChanges();
}

void testDisplay(TestData *t, float deltaTime){
    t->slime.animate(deltaTime);
}

void testFixedLoop(TestData *t, float deltaTime){
    t->slime.update(deltaTime);
}

