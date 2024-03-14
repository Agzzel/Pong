#include "Ball.h"
#include <iostream>

Ball::BallDirectionHorizontal directionHorizontal;
Ball::BallDirectionVertical directionVertical;

// Sets the coordinates, width and height for the rectangle representing the ball.
// Also sets initial values for direction.
Ball::Ball(int rectX, int rectY, int rectH, int rectW){
    ballRect.x = rectX;
    ballRect.y = rectY;
    ballRect.h = rectH;
    ballRect.w = rectW;

    directionHorizontal = LEFT;
    directionVertical = UP;
}

SDL_Rect* Ball::getRect(){
    return &ballRect;
}

/*
    Applies velocity to the ball's X and Y position based on direction.
    This function also handles collisions, if the ball hits a player or a wall it simply changes
    to the opposite direction.
*/ 
void Ball::moveBall(SDL_Rect* left, SDL_Rect* right, SDL_Rect* upperWall, SDL_Rect* lowerWall){
    if(SDL_HasIntersection(&ballRect, left)){
        directionHorizontal = RIGHT;
    }
    else if (SDL_HasIntersection(&ballRect, right)){
        directionHorizontal = LEFT;
    }

    if(SDL_HasIntersection(&ballRect, upperWall)){
        directionVertical = DOWN;
    }

    else if (SDL_HasIntersection(&ballRect, lowerWall)){
        directionVertical = UP;
    }

    switch (directionHorizontal)
    {
    case LEFT:
        ballRect.x -= ballVelX;
        break;

    case RIGHT:
        ballRect.x += ballVelX;
        break;
    default:
        break;
    }

    switch(directionVertical){
        case UP:
        ballRect.y -= ballVelY;
        break;

        case DOWN:
        ballRect.y += ballVelY;
        break;

        default:
        break;
    }
}

float Ball::getX(){
    return ballRect.x;
}

float Ball::setX(float newX){
    ballRect.x = newX;
}