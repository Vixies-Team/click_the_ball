#ifndef BALL_H
#define BALL_H

#include "../../vendor/raylib/include/raylib.h"

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} Ball;

typedef enum {
    BALL_EVENT_NONE,
    BALL_EVENT_CLICKED
} BallEvent;

void BallInit(Ball* ball, Vector2 position, float radius, Color color);

bool BallIsHovered(Ball *ball);
bool BallIsColliding(Ball *a, Ball *b);

void BallBounce(Ball* ball1, Ball* ball2);
BallEvent BallUpdate(Ball* ball);
void BallDrawing(Ball* ball);

void BallDeinit();

#endif // BALL_H