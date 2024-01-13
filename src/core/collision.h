#pragma once

#include "geometry.h"

// uses xz components for circle center
static inline bool circleCircleCollisionCheck(Circle a, Circle b){
    Vector2 c1 = {a.center.x, a.center.z};
    Vector2 c2 = {b.center.x, b.center.z};
    float dist = Vector2DistanceSqr(c1,c2);
    float sumRadii = a.r + b.r;
    return dist < sumRadii * sumRadii;
}

// returns the vector to be added to pos of 'moves' to resolve collision
static inline Vector2 resolveCircleCollision(Circle moves, Circle stationary){
    Vector2 c1 = {moves.center.x, moves.center.z};
    Vector2 c2 = {stationary.center.x, stationary.center.z};
    Vector2 c1Toc2 = Vector2Normalize(Vector2Subtract(c2,c1));
    Vector2 c2Toc1 = Vector2Negate(c1Toc2);

    Vector2 boundary1 = Vector2Add(c1, Vector2Scale(c1Toc2, moves.r));
    Vector2 boundary2 = Vector2Add(c2, Vector2Scale(c2Toc1, stationary.r));
    float dist = Vector2Distance(boundary1, boundary2);
    return Vector2Scale(c2Toc1, dist);
}

//bool circleRect(Circle c, float rx, float ry, float rw, float rh) {
//
//    // temporary variables to set edges for testing
//    float testX = c.center.x;
//    float testY = c. center.y;
//
//    // which edge is closest?
//    if (c.center.x < rx)         testX = rx;      // test left edge
//    else if (c.center.x > rx + rw) testX = rx + rw;   // right edge
//    if (cy < ry)         testY = ry;      // top edge
//    else if (cy > ry + rh) testY = ry + rh;   // bottom edge
//
//    // get distance from closest edges
//    float distX = c.center.x - testX;
//    float distY = cy - testY;
//    float distance = sqrt((distX * distX) + (distY * distY));
//
//    // if the distance is less than the radius, collision!
//    if (distance <= c.r) {
//        return true;
//    }
//    return false;
//}