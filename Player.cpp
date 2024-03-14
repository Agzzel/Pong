#include "Player.h"

// Sets coordinates, width and height for the rectangle representing the player.
Player::Player(int rectX, int rectY, int rectH, int rectW){
    playerRect.x = rectX;
    playerRect.y = rectY;
    playerRect.h = rectH;
    playerRect.w = rectW;
}

SDL_Rect* Player::getRect(){
    return &playerRect;
}

// Moves the player by applying velocity to its position. Also checks if the player is out of bounds vertically.
void Player::move(){ 
    playerRect.y += currentVelocity;
    if(playerRect.y > 650 || playerRect.y < 0){
        playerRect.y -= currentVelocity;
    }
}

int Player::setCurrentVelocity(int newVel){
    currentVelocity = newVel;
}