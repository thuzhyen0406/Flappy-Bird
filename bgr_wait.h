#ifndef bgr_wait
#define bgr_wait
#include "overall.h"
#include "background.h"
void rebegin(SDL_Texture* bgr, SDL_Renderer* ren, bool &running, SDL_Event &e)
{

        SDL_Texture *bdau = loadTexture("Data/Image/ready.png", ren);
         // Uint32 lastFrameTime = SDL_GetTicks();
        SDL_RenderCopy(ren, bgr, NULL, NULL);
        renderTexture(bdau, 270, 120, ren);
          SDL_RenderPresent( ren );
          if(!waitUntilKeyPressed(e))
          {
              running = false;
          }
}

SDL_Color textColor = {255, 255, 102, 255}, outlineColor = {0, 0, 0, 255};



SDL_Rect textRect = {200, 350, 320, 25};
void rStart(Uint32 &lastTime, bool &toggleText, SDL_Texture* bgr, SDL_Renderer* ren, SDL_Texture* textTex )
{
    if (SDL_GetTicks() - lastTime > 800) {
            toggleText = !toggleText;
            lastTime = SDL_GetTicks();
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgr, NULL, NULL);
        if (toggleText) {
            SDL_RenderCopy(ren, textTex, NULL, &textRect);
        }

        SDL_RenderPresent(ren);
}
#endif // bgr_wait
