#ifndef OVERALL_H
#define OVERALL_H
#include "music.h"

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 500;
const int margin_bottom = 74;
const int BG_SPEED = 3 ;
bool toggleText = true;  // Bật/Tắt chữ
unsigned int lastTime = 0;

SDL_Rect govRect = {190, -50, 490, 490};
SDL_Texture* btrs[2] = {nullptr, nullptr};
SDL_Rect posbtrs = {SCREEN_WIDTH - 100, 0, 35, 35};
SDL_Rect Stpos = {350, 400, 64, 60};
SDL_Rect Hlpos = {420, 400, 70, 70};
SDL_Rect RTpos = {0, 0, 70, 70};
void Exit(SDL_Texture* birdImages[2], SDL_Window* window, SDL_Renderer* ren, SDL_Texture* bgr, SDL_Texture* upperPipeTex, SDL_Texture* lowerPipeTex)
{
    for (int i = 0; i < 2; i++) {
            SDL_DestroyTexture(birdImages[i]);
            birdImages[i] = nullptr;
    }
    SDL_DestroyTexture(bgr);
    SDL_DestroyTexture(upperPipeTex);
    SDL_DestroyTexture(lowerPipeTex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}
int waitUntilKeyPressed(SDL_Event &e)
{
    while (true) {
       if (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                return 0; // nhấn x
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    return 0; // Nhấn ESC -> Thoát
                else if(e.key.keysym.sym != SDLK_m)
                    return 1;  // Nhấn phím khác -> Bắt đầu
            }
       if( e.type == SDL_MOUSEBUTTONDOWN) return 1;

        }

        SDL_Delay(100);
    }
}

bool inSide(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}


void waitPress(SDL_Event &e, bool &running, int &ok, bool &amthanh, bool &getHelp)
{

    while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false, ok = 0;
                }
                else if(e.key.keysym.sym == SDLK_m)
                {
                    amthanh = !amthanh;
                }
                else if(!getHelp){
                        running = false, ok = 1;
                }

            }
            else if(e.type ==  SDL_MOUSEBUTTONDOWN)
            {
                if(inSide(e.button.x, e.button.y, Stpos))
                {
                    running = false;
                    ok = 1;
                }
                else if(inSide(e.button.x, e.button.y, Hlpos))
                {
                    getHelp = 1;
                }
                 else if(getHelp && inSide(e.button.x, e.button.y, RTpos))
                 {
                     getHelp = 0;
                 }

            }

        }
}

void waitPress2(SDL_Renderer* ren, int &chay, bool &running, SDL_Event &e,float &birdVelocity, float const JUMP_FORCE, Mix_Chunk *gJump, bool &amthanh)
{
     while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                else if(e.key.keysym.sym == SDLK_s)
                {
                    chay = 1;

                      SDL_RenderCopy(ren, btrs[chay], NULL, &posbtrs);
                      SDL_RenderPresent(ren);
                    if(!waitUntilKeyPressed(e)) running = false;
                    else {
                            chay = 0;
                            continue;
                    }
                }
                else if(e.key.keysym.sym == SDLK_m)
                {
                    amthanh = !amthanh;
                }
                else {
                        birdVelocity = JUMP_FORCE;
                       if(amthanh) play(gJump);
                }


            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
                 {
                     birdVelocity = JUMP_FORCE;
                      if(amthanh) play(gJump);
                     }

     }
}


bool waitPress3(SDL_Event &e)
{
    while(true){
    if (SDL_PollEvent(&e)) {

        if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_r) return true;

            if (e.key.keysym.sym == SDLK_ESCAPE) return false;
        }

        if (e.type == SDL_QUIT) {
                return false;
            }

     }
    }

}
#endif // OVERALL_H
