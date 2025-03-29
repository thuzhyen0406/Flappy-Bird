#ifndef TEXT_H
#define TEXT_H
//#include "background.h"
#define pii pair<SDL_Texture*, SDL_Texture*>
using namespace std;

SDL_Color white = {255, 255, 255, 255};
SDL_Color brown = {139, 69, 19, 255};
int textW = 200, textH = 35;
int tw = 100, th = 20;
SDL_Color lightPink = {255, 182, 193, 255};
SDL_Color textColor = {255, 255, 102, 255}, outlineColor = {0, 0, 0, 255};
SDL_Rect textRect = {230, 400, 400, 28};
//SDL_Color yellowD = {230, 200, 20, 255};
SDL_Color yellowD = {255, 255, 0, 255};
SDL_Color black = {0, 0, 0, 255};
SDL_Color blueblack = {0, 0, 128, 255};
pair<SDL_Texture*, SDL_Texture*> createText(SDL_Renderer* ren, TTF_Font* font, const string& text, SDL_Color textColor, SDL_Color outlineColor, int ol, int il)
{
    TTF_SetFontOutline(font, ol);
    SDL_Surface* outlineSur = TTF_RenderText_Blended(font, text.c_str(), outlineColor);

    SDL_Texture* outlineTex = SDL_CreateTextureFromSurface(ren, outlineSur);
    SDL_FreeSurface(outlineSur); //giai phong bo nho

    TTF_SetFontOutline(font, il);
    SDL_Surface* textSur = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(ren, textSur);
    SDL_FreeSurface(textSur);
    pair<SDL_Texture*, SDL_Texture*> ans = make_pair(outlineTex, textTex);
    return ans;
}

SDL_Texture* createText1(SDL_Renderer* ren, TTF_Font* font, const string& text, SDL_Color textColor) {

    SDL_Surface* textSur = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(ren, textSur);
    SDL_FreeSurface(textSur);

    return textTex;
}

void Paint_text_score1(pii textTex, SDL_Renderer* ren, int res)
{
 //  // vien
    SDL_Rect textRect;
    int SCREEN_WIDTH = 850;
    if(res <= 2)
     SDL_QueryTexture(textTex.first, NULL, NULL, &textW, &textH);
     else
         SDL_QueryTexture(textTex.first, NULL, NULL, &tw, &th);
     switch(res)
     {
     case 1:
        textRect = {(SCREEN_WIDTH - textW * 2) / 2, 20, textW*2, 50};
        break;
     case 2:
        textRect = {20, 10, textW, 15};
        break;
     case 3:
        textRect = {(SCREEN_WIDTH - tw - 60) / 2, 230, tw + 60, th + 5};
        break;
     case 4:
        textRect = {(SCREEN_WIDTH - tw- 40) / 2, 256, tw + 40, th + 5};
        break;
     default:
        textRect = {(SCREEN_WIDTH - tw) / 2, 350, tw + 10, th + 5};
     }

    SDL_RenderCopy(ren, textTex.first, NULL, &textRect);

    //chu
    if(res <= 2)
     SDL_QueryTexture(textTex.second, NULL, NULL, &textW, &textH);
     else
         SDL_QueryTexture(textTex.second, NULL, NULL, &tw, &th);
    switch(res)
     {
     case 1:
        textRect = {(SCREEN_WIDTH - textW * 2) / 2, 20, textW*2, 50};
        break;
     case 2:
        textRect = {20, 10, textW, 15};
        break;
     case 3:
        textRect = {(SCREEN_WIDTH - tw - 60) / 2, 230, tw + 60, th + 5};
        break;
     case 4:
        textRect = {(SCREEN_WIDTH - tw - 40) / 2, 256, tw + 40, th + 5};
        break;
     default:
        textRect = {(SCREEN_WIDTH - tw) / 2, 350, tw + 10, th + 5};
     }

    SDL_RenderCopy(ren, textTex.second, NULL, &textRect);

}
#endif // TEXT_H
