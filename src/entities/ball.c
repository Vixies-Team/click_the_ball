#include <stdio.h>
#include "ball.h"

bool BallIsHovered(Ball *ball) {
    return CheckCollisionPointCircle(
        GetMousePosition(),
        ball->position,
        ball->radius
    );
}

bool BallIsColliding(Ball *a, Ball *b) {
    return CheckCollisionCircles(
        a->position,
        a->radius,
        b->position,
        b->radius
    );
}

void BallInit(Ball* ball, Vector2 position, float radius, Color color) {
    ball->position = position;
    ball->velocity = (Vector2){0, 0};
    ball->radius = radius;
    ball->color = color;
}

void BallBounce(Ball* ball1, Ball* ball2) {
    Vector2 temp = ball1->velocity;
    ball1->velocity = ball2->velocity;
    ball2->velocity = temp;
}

BallEvent BallUpdate(Ball* ball) {
    ball->position = (Vector2) {
        ball->position.x + ball->velocity.x,
        ball->position.y + ball->velocity.y
    };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && BallIsHovered(ball)) return BALL_EVENT_CLICKED;
    else return BALL_EVENT_NONE;
    
}
void BallDrawing(Ball* ball) {
    DrawCircleV(ball->position, ball->radius, ball->color);
}

void BallDeinit() {
}