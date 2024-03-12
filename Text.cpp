#include "Text.h"

Text::Text(){
    TTF_Init();
    textTexture = nullptr;
    font = TTF_OpenFont("Font/DSEG7Classic-Regular.ttf", 72);
    if(font == nullptr){
        std::cout << "Could not load font! " << TTF_GetError() << "\n";
    }
    imgWidth = 0;
    imgHeight = 0;
}

Text::~Text(){
    SDL_DestroyTexture(textTexture);
    textTexture = nullptr;
}

void Text::loadFromRenderedText(std::string text, SDL_Color textColor, SDL_Renderer* renderer){
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if(textSurface == nullptr){
        TTF_GetError();
    }
    else{
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(textTexture == nullptr){
            std::cout << "Could not create texture: " << SDL_GetError() << "\n";
        }
        else{
        imgWidth = textSurface->w;
        imgHeight = textSurface->h;
        }
    }
    //SDL_FreeSurface(textSurface);
}

void Text::render(int x, int y, SDL_Renderer* renderer){
    SDL_Rect renderQuad = {x, y, imgWidth, imgHeight}; // texten renderas i denna rektangel
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
}

int Text::getHeight(){
    return imgHeight;
}

int Text::getWidth(){
    return imgWidth;
}