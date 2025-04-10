#ifndef bgr_wait
#define bgr_wait
#include "background.h"
bool loadMedia2(SDL_Renderer* ren) {
    btrs[0] = loadTexture("Data/Image/playing.png", ren);
    btrs[1] = loadTexture("Data/Image/stopping.png", ren);

    return btrs[0] && btrs[1];
}

void rebegin(SDL_Texture* bgr, SDL_Renderer* ren, bool &running, SDL_Event &e)
{

        SDL_Texture *bdau = loadTexture("Data/Image/ready.png", ren);

        SDL_RenderCopy(ren, bgr, NULL, NULL);
        renderTexture(bdau, 300, 120, ren);
          SDL_RenderPresent( ren );
          if(!waitUntilKeyPressed(e))
          {
              running = false;
          }
}


void rStart(Uint32 &lastTime, bool &toggleText, SDL_Texture* bgr, SDL_Renderer* ren, pii textTex )
{
    if (SDL_GetTicks() - lastTime > 800) {
            toggleText = !toggleText;
            lastTime = SDL_GetTicks();
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgr, NULL, NULL);
        if (toggleText) {
            SDL_RenderCopy(ren, textTex.first, NULL, &textRect);
            SDL_RenderCopy(ren, textTex.second, NULL, &textRect);
        }

        SDL_RenderPresent(ren);
}

void gDie(SDL_Renderer* ren, bool &running, SDL_Event &e, int &score, int highScore){

    TTF_Font* font = TTF_OpenFont("Data/FONT/font_game.ttf", 28);
    SDL_Texture* gov = loadTexture("Data/Image/gameover.png", ren);
    SDL_RenderCopy(ren, gov, NULL, &govRect);

       pii textTexture = createText(ren, font, "CURRENT SCORE: " + to_string(score), yellowD, brown, 1, 0);
       Paint_text_score1(textTexture, ren, 3);

       textTexture = createText(ren, font, "BEST SCORE: " + to_string(highScore),yellowD, brown, 1, 0);
       Paint_text_score1(textTexture, ren, 4);

    font = TTF_OpenFont("Data/FONT/Consolas.ttf", 25);
    textTexture = createText(ren, font, "Press R to Restart", yellowD, blueblack, 2, 1);
    Paint_text_score1(textTexture, ren, 5);
    SDL_RenderCopy(ren, btrs[1], NULL, &posbtrs);

    SDL_RenderPresent(ren);
    if(waitPress3(e))
    {
        score = 0;
    }
    else
        running = false;
}
#endif
