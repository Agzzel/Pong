#include <SDL2/SDL.h>

class Player{
public:
    int currentVelocity = 0;
    const int maxVel = 5;

    Player(int rectX, int rectY, int rectH, int rectW); // Coordinates for the rectangle that represents the player
    SDL_Rect* getRect();
    void move();
    int setCurrentVelocity(int newVel);
    
private:
    SDL_Rect playerRect;
};