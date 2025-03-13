#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "overall.h"
#include <SDL_ttf.h>
#include "text.h"
#include "bgr_wait.h"


int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    SDL_Renderer* ren = createRenderer(window);

    SDL_Texture* bgr = loadTexture("Data/Image/begin_BR.jpg", ren);
    SDL_RenderCopy( ren, bgr, NULL, NULL);

    SDL_RenderPresent( ren );


      SDL_Event e;

    bool running = true;

        if (TTF_Init() == -1) {
            SDL_Log("Lỗi khởi tạo SDL_ttf: %s", TTF_GetError());
            return -1;
        }
          TTF_Font* font = TTF_OpenFont("Consolas.ttf", 24);

    if (!font) {
        SDL_Log("Không thể tải font: %s", TTF_GetError());
        SDL_Quit();
        return 0;
    }


    int bgX = 0, ok = 0;
    bool showT = true, toggleText = true;
    Uint32 lastTime = SDL_GetTicks();
    SDL_Texture* textTex = createText(ren, font, "Press Enter to Start, Esc to Quit", textColor, outlineColor);
    while (running) {
            waitPress(e,running, ok);
     //   SDL_DestroyTexture(outlineTex);
            rStart(lastTime, toggleText, bgr, ren, textTex);

    }

    if(ok == 1)
    {
        running = true;
        bgr = loadTexture("Data/Image/background2.jpg", ren);
        rebegin(bgr, ren, running, e);
        SDL_Texture* nen = loadTexture("Data/Image/nendat.jpg", ren);
        int check = 1;
        Uint32 lastFrameTime = SDL_GetTicks();
        while(running)
        {
        waitPress(e, running, check);
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

             bgX -= BG_SPEED * deltaTime * 60;

                if (bgX <= -SCREEN_WIDTH) {
                       bgX += SCREEN_WIDTH;  // Reset khi chạy hết ảnh

                }


             SDL_RenderClear(ren);
            SDL_RenderCopy(ren, bgr, NULL, NULL);
            SDL_RenderCopy(ren, nen, NULL, &bgRect1);
            SDL_RenderCopy(ren, nen, NULL, &bgRect2);

            SDL_Delay(16);

                SDL_RenderPresent( ren );
            }
        }



//        if(ok)
//        {

//        }





      TTF_CloseFont(font);
// day la ket thuc
    SDL_DestroyTexture(bgr);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}


