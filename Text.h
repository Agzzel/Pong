#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Text{
public:
    Text();
    ~Text();

    void loadFromRenderedText(std::string text, SDL_Color textColor, SDL_Renderer* renderer);
    void render(int x, int y, SDL_Renderer* renderer);

    int getHeight();
    int getWidth();

private:
    SDL_Texture* textTexture;
    TTF_Font* font;
    int imgWidth, imgHeight;

};