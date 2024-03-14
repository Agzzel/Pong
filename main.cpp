#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Text.h"
#include "Player.h"
#include "Ball.h"

const int screenHeight = 720;
const int screenWidth = 1280;

int ballPosY = 360;
int ballPosX = 640;
const int ballVelX = 3;
const int ballVelY = 3;

int leftPoints = 0;
int rightPoints = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_PixelFormat* pixelFormat = NULL;
Text leftScoreText;
Text rightScoreText;
Text gameOverText;
SDL_Color textColor = {0, 255, 0};

Player leftPlayer(10, 20, 60, 20);
Player rightPlayer(1250, 20, 60, 20);
Ball ball(360, 640, 30, 30);

SDL_Rect upperWall, lowerWall;

void handleInput(SDL_Event& event)
{
    /*
    This function simply changes the velocity value for the players, the new value is then 
    used in the move()-function.
    */
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w: leftPlayer.currentVelocity -= leftPlayer.maxVel; break;
            case SDLK_s: leftPlayer.currentVelocity += leftPlayer.maxVel; break;
            case SDLK_UP: rightPlayer.currentVelocity -= rightPlayer.maxVel; break;
            case SDLK_DOWN: rightPlayer.currentVelocity += rightPlayer.maxVel; break;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w: leftPlayer.currentVelocity += leftPlayer.maxVel; break;
            case SDLK_s: leftPlayer.currentVelocity -= leftPlayer.maxVel; break;
            case SDLK_UP: rightPlayer.currentVelocity += rightPlayer.maxVel; break;
            case SDLK_DOWN: rightPlayer.currentVelocity -= rightPlayer.maxVel; break;
        }
    }
}

int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    pixelFormat = SDL_GetWindowSurface(window)->format;
    
    bool exit = false;
    SDL_Event event;
    leftScoreText.loadFromRenderedText(std::to_string(leftPoints), textColor, renderer);
    rightScoreText.loadFromRenderedText(std::to_string(rightPoints), textColor, renderer);

    while(!exit)
    {
        while(SDL_PollEvent(&event) != 0) // Polls the event queue for input events until it is empty
        {
            if(event.type == SDL_QUIT) // If the user presses the X button on the window
            {
                exit = true;
            }
            handleInput(event); // Continuously checks for user input 
        }
        
        upperWall.x = 0;
        upperWall.y = 0;
        upperWall.w = screenWidth;
        upperWall.h = 2;

        lowerWall.x = 0;
        lowerWall.y = screenHeight;
        lowerWall.w = screenWidth;
        lowerWall.h = 2;

        leftPlayer.move();
        rightPlayer.move();
        ball.moveBall(leftPlayer.getRect(), rightPlayer.getRect(), &upperWall, &lowerWall);

        // Gives a point to the right player if the ball goes out of bounds on the left side and vice-versa
        if(ball.getX() < 0.f){
            rightPoints++;
            ball.setX(640);
            rightScoreText.loadFromRenderedText(std::to_string(rightPoints), textColor, renderer);
        }
        else if (ballPosX > screenWidth){ 
            leftPoints++;
            ball.setX(640);
            leftScoreText.loadFromRenderedText(std::to_string(leftPoints), textColor, renderer);
    }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // The background colour
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0,255,0, 255);
        SDL_RenderDrawLine(renderer, 640, 0, 640, 720);
      
        SDL_RenderFillRect(renderer, leftPlayer.getRect());
        SDL_RenderFillRect(renderer, rightPlayer.getRect());
        SDL_RenderFillRect(renderer, ball.getRect());
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
            gameOverText.loadFromRenderedText("Game Over", textColor, renderer);
            gameOverText.render((screenWidth - gameOverText.getWidth()) / 2, (screenHeight - gameOverText.getHeight()) / 2, renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            exit = true;
            //Shuts down the program after 3 seconds
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}

