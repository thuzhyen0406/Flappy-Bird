#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "text.h"
#include "bgr_wait.h"
#include "pipe.h"
#include <ctime>
#include <cstdlib>

vector<Pipe> pipes;

int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    SDL_Renderer* ren = createRenderer(window);

    SDL_Texture* bgr = loadTexture("Data/Image/begin_BR.jpg", ren);
    SDL_Texture* upperPipeTex = loadTexture("Data/Image/pipe_up.png", ren);
    SDL_Texture* lowerPipeTex = loadTexture("Data/Image/pipe_down.png", ren);
//    int width, height;
//    SDL_QueryTexture(upperPipeTex, NULL, NULL, &width, &height);
//printf("Kích thước upperPipeTex: %d x %d\n", width, height);
//
//SDL_QueryTexture(lowerPipeTex, NULL, NULL, &width, &height);
//printf("Kích thước lowerPipeTex: %d x %d\n", width, height);


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
    srand(time(0));
    if(ok == 1)
    {
        running = true;
        bgr = loadTexture("Data/Image/background2.jpg", ren);
        rebegin(bgr, ren, running, e);
        SDL_Texture* nen = loadTexture("Data/Image/nendat.jpg", ren);
        int check = 1;
        Uint32 lastFrameTime = SDL_GetTicks();
        initPipes(pipes);
        renderPipes(ren, upperPipeTex, lowerPipeTex, pipes);
          SDL_RenderPresent( ren );
        while(running)
        {
        waitPress(e, running, check); // can doi 1 ham khac
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

             bgX -= BG_SPEED * deltaTime * 60;

                if (bgX <= -SCREEN_WIDTH) {
                       bgX += SCREEN_WIDTH;  // Reset khi chạy hết ảnh

                }

                SDL_Rect bgRect1 = {bgX, SCREEN_HEIGHT - 76, SCREEN_WIDTH, 76};
                SDL_Rect bgRect2 = {bgX + SCREEN_WIDTH, SCREEN_HEIGHT - 76, SCREEN_WIDTH, 76};
             SDL_RenderClear(ren);
            SDL_RenderCopy(ren, bgr, NULL, NULL);
            SDL_RenderCopy(ren, nen, NULL, &bgRect1);
            SDL_RenderCopy(ren, nen, NULL, &bgRect2);
            updatePipes(pipes);
            renderPipes(ren, upperPipeTex, lowerPipeTex, pipes);

            SDL_Delay(16);

                SDL_RenderPresent( ren );
            }
        }



//        if(check)
//        {
//
//        }





      TTF_CloseFont(font);
// day la ket thuc
    SDL_DestroyTexture(bgr);
    SDL_DestroyTexture(upperPipeTex);
    SDL_DestroyTexture(lowerPipeTex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}



