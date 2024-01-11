#include <raylib.h>
#include <raymath.h>

#include <stdint.h>

#include "tests/tests.h"

struct Window{
    int w,h;
};


int main(void){
    int width = 1280;
    int height = 720;

    Window w = {
        1280, 720,
    };
    InitWindow(width, height, "The Lost Spectrum");

    SetTargetFPS(60);
    auto testData = testInit();


    float accumulator = 0;

    while (!WindowShouldClose()){
        float deltaTime = GetFrameTime();
        accumulator += deltaTime;
        
        // fixed dt for fixed time updates
        const float FIXED_DT = 0.002f;
        while(accumulator >= FIXED_DT){
            // update physics and stuff

            accumulator -= FIXED_DT;
        }

        BeginDrawing();
        Color background = {
            255,255,0,255
        };

        ClearBackground(background);

        testLoop(&testData, deltaTime);
        
        EndDrawing();




    }
    return 0;
}
