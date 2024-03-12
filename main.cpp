#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Text.h"

const int screenHeight = 720;
const int screenWidth = 1280;

int leftCurrentVelocity = 0;
const int leftMaxVel = 5;
int leftPosY = 20;

int rightCurrentVelocity = 0;
const int rightMaxVel = 5;
int rightPosY = 20;

int ballPosY = 360;
int ballPosX = 640;
const int ballVelX = 3;
const int ballVelY = 3;
//kanske ändrar ballVelY under spelets gång

int leftPoints = 0;
int rightPoints = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_PixelFormat* pixelFormat = NULL;
Text leftScoreText;
Text rightScoreText;
Text gameOverText;
SDL_Color textColor = {0, 255, 0};

SDL_Rect playerLeft, playerRight, ball, upperWall, lowerWall;

enum BallDirectionHorizontal{ // samling av konstanter helt enkelt
    LEFT,
    RIGHT
};

enum BallDirectionVertical{
    UP,
    DOWN
};

BallDirectionHorizontal directionHorizontal;
BallDirectionVertical directionVertical;

void handleInput(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w: leftCurrentVelocity -= leftMaxVel; break;
            case SDLK_s: leftCurrentVelocity += leftMaxVel; break;
            case SDLK_UP: rightCurrentVelocity -= rightMaxVel; break;
            case SDLK_DOWN: rightCurrentVelocity += rightMaxVel; break;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w: leftCurrentVelocity += leftMaxVel; break;
            case SDLK_s: leftCurrentVelocity -= leftMaxVel; break;
            case SDLK_UP: rightCurrentVelocity += rightMaxVel; break;
            case SDLK_DOWN: rightCurrentVelocity -= rightMaxVel; break;
        }
    }
}

void movePlayerLeft()
{
    leftPosY += leftCurrentVelocity;
    if((leftPosY + playerLeft.h > screenHeight) || leftPosY < 0){
        leftPosY -= leftCurrentVelocity;
    }
}

void movePlayerRight()
{
    rightPosY += rightCurrentVelocity;
    if((rightPosY + playerRight.h > screenHeight) || rightPosY < 0){
        rightPosY -= rightCurrentVelocity;
    }
}

void moveBall(){

    if(SDL_HasIntersection(&ball, &playerLeft)){
        directionHorizontal = RIGHT;
    }
    else if (SDL_HasIntersection(&ball, &playerRight)){
        directionHorizontal = LEFT;
    }
    
    if(SDL_HasIntersection(&ball, &upperWall)){
        directionVertical = DOWN;
    }
    else if (SDL_HasIntersection(&ball, &lowerWall)){
        directionVertical = UP;
    }

    switch (directionHorizontal)
    {
    case LEFT:
        ballPosX -= ballVelX;
        break;

    case RIGHT:
        ballPosX += ballVelX;
        break;
    default:
        break;
    }

    switch(directionVertical){
        case UP:
        ballPosY -= ballVelY;
        break;

        case DOWN:
        ballPosY += ballVelY;
        break;

        default:
        break;
    }

    if(ballPosX < 0){ 
        rightPoints++;
        ballPosX = 640;
        rightScoreText.loadFromRenderedText(std::to_string(rightPoints), textColor, renderer);
    }

    else if (ballPosX > screenWidth){ 
        leftPoints++;
        ballPosX = 640;
        leftScoreText.loadFromRenderedText(std::to_string(leftPoints), textColor, renderer);
    }
}

int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    directionHorizontal = LEFT;
    directionVertical = UP;
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    //vsync aktiverat, spelet kör på 60fps
    pixelFormat = SDL_GetWindowSurface(window)->format;
    
    bool exit = false;
    SDL_Event event;
    leftScoreText.loadFromRenderedText(std::to_string(leftPoints), textColor, renderer);
    rightScoreText.loadFromRenderedText(std::to_string(rightPoints), textColor, renderer);

    while(!exit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                exit = true;
            }
            handleInput(event);
        }
        movePlayerLeft();
        movePlayerRight();
        moveBall();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // bakgrund
        SDL_RenderClear(renderer);

        // Kan kanske göra detta i en funktion
        playerLeft.x = 10;
        playerLeft.y = leftPosY;
        playerLeft.h = 60;
        playerLeft.w = 20;

        playerRight.x = 1250;
        playerRight.y = rightPosY;
        playerRight.h = 60;
        playerRight.w = 20;

        ball.x = ballPosX;
        ball.y = ballPosY;
        ball.w = 30;
        ball.h = 30;

        upperWall.x = 0;
        upperWall.y = 0;
        upperWall.w = screenWidth;
        upperWall.h = 2;

        lowerWall.x = 0;
        lowerWall.y = screenHeight;
        lowerWall.w = screenWidth;
        lowerWall.h = 2;
        
        SDL_SetRenderDrawColor(renderer, 0,255,0, 255);
        SDL_RenderDrawLine(renderer, 640, 0, 640, 720);
        SDL_RenderFillRect(renderer, &playerLeft);
        SDL_RenderFillRect(renderer, &playerRight);
        SDL_RenderFillRect(renderer, &ball);
        SDL_RenderFillRect(renderer, &upperWall);
        SDL_RenderFillRect(renderer, &lowerWall);
        
        leftScoreText.render(100, 10, renderer);
        rightScoreText.render(1180, 10, renderer);
        SDL_RenderPresent(renderer);
        
        if(rightPoints == 10){
            gameOverText.loadFromRenderedText("Game Over", textColor, renderer);
            gameOverText.render((screenWidth - gameOverText.getWidth()) / 2, (screenHeight - gameOverText.getHeight()) / 2, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            exit = true;
        }
        else if (leftPoints == 10){
            gameOverText.render((screenWidth - gameOverText.getWidth()) / 2, (screenHeight - gameOverText.getHeight()) / 2, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            exit = true;
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}

