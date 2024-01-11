#include "tests.h"
#include "../core/animation.h"


AnimationSheet slimeAnimate(){
    AnimationSheet slime ("./assets/slime-Sheet.png", 32, 25);
    slime.addAnimation("idle", 0, 4);
    slime.setFPS(6);
    return slime;
}


TestData testInit(){
    TestData t;
    t.slime = slimeAnimate();
    return t;
}


void testLoop(TestData *t, float deltaTime){
    Rectangle r = {
        0,0,
        200,150
    };
    t->slime.playAnimation("idle", deltaTime, r);
}

