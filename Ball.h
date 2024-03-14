#include <SDL2/SDL.h>

class Ball{

public:
    const int ballVelX = 3, ballVelY = 3;

    Ball(int rectX, int rectY, int rectH, int rectW);
    void moveBall(SDL_Rect* left, SDL_Rect* right, SDL_Rect* upperWall, SDL_Rect* lowerWall);
    // Takes the left and right player rectangles aswell as the walls as input, so the ball knows
    // which elements it can collide with.

    SDL_Rect* getRect();
    float getX();
    float setX(float newX);

    enum BallDirectionHorizontal{
    LEFT,
    RIGHT
    };

    enum BallDirectionVertical{
    UP,
    DOWN
    };

//Having two enums makes it easier to independently control the ball's horizontal and vertical movement.

private:
    SDL_Rect ballRect;
};