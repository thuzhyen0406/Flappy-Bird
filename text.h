#ifndef TEXT_H
#define TEXT_H
//#include "background.h"
using namespace std;

SDL_Color white = {255, 255, 255, 255};
int textW, textH = 200;
SDL_Color lightPink = {255, 182, 193, 255};
SDL_Color textColor = {255, 255, 102, 255}, outlineColor = {0, 0, 0, 255};
SDL_Rect textRect = {230, 400, 400, 28};

SDL_Texture* createText(SDL_Renderer* ren, TTF_Font* font, const string& text, SDL_Color textColor, SDL_Color outlineColor) {

    TTF_SetFontOutline(font, 10);
    SDL_Surface* outlineSur = TTF_RenderText_Blended(font, text.c_str(), outlineColor);

    SDL_Texture* outlineTex = SDL_CreateTextureFromSurface(ren, outlineSur);
    SDL_FreeSurface(outlineSur);

    TTF_SetFontOutline(font, 1);
    SDL_Surface* textSur = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(ren, textSur);
    SDL_FreeSurface(textSur);

    return textTex;
}

#endif // TEXT_H
