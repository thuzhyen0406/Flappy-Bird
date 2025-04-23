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
      //  SDL_RenderCopy(ren, bg3, NULL, &RTpos);
          SDL_RenderPresent( ren );
          if(!waitUntilKeyPressed(e))
          {
              running = false;
          }
}


void rStart(SDL_Texture* bgr, SDL_Texture* bg1, SDL_Texture* bg2, SDL_Renderer* ren)
{
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgr, NULL, NULL);
      SDL_RenderCopy(ren, bg1, NULL, &Stpos);
      SDL_RenderCopy(ren, bg2, NULL, &Hlpos);

        SDL_RenderPresent(ren);
}


void gHelp(SDL_Texture* bgr, SDL_Texture* bg3, SDL_Renderer* ren, bool &getHelp, pii textTex1, pii textTex2, pii textTex3, pii textTex4)
{
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bgr, NULL, NULL);
    SDL_RenderCopy(ren, bg3, NULL, &RTpos);
    SDL_RenderCopy(ren, textTex1.first, NULL, &textRect1);
    SDL_RenderCopy(ren, textTex1.second, NULL, &textRect1);

    SDL_RenderCopy(ren, textTex2.first, NULL, &textRect2);
    SDL_RenderCopy(ren, textTex2.second, NULL, &textRect2);

      SDL_RenderCopy(ren, textTex3.first, NULL, &textRect3);
    SDL_RenderCopy(ren, textTex3.second, NULL, &textRect3);

      SDL_RenderCopy(ren, textTex4.first, NULL, &textRect4);
    SDL_RenderCopy(ren, textTex4.second, NULL, &textRect4);
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
    SDL_RenderCopy(ren, btrs[1], NULL, &posbtrs); //nut tam dung

    SDL_RenderPresent(ren);
    if(waitPress3(e))
    {
        score = 0;
    }
    else
        running = false;
}
#endif
