#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "text.h"
#include "bgr_wait.h"
#include "pipe.h"
#include "bird.h"
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

      SDL_Event e;

    bool running = true;

        if (TTF_Init() == -1 || !loadMedia(ren)) {
            SDL_Log("Lỗi khởi tạo SDL_ttf: %s", TTF_GetError());
            return -1;
        }

     TTF_Font* font = TTF_OpenFont("Data/FONT/Consolas.ttf", 24);
    if (!font) {
            SDL_Log("Không thể tải font: %s", TTF_GetError());
            SDL_Quit();
            return 0;
        }

//    SDL_RenderCopy( ren, bgr, NULL, NULL);
//
//    SDL_RenderPresent( ren );
    int bgX = 0, ok = 0;
    bool showT = true, toggleText = true;
    Uint32 lastTime = SDL_GetTicks();

    SDL_Texture* textTex = createText(ren, font, "Press Enter to Start, Esc to Quit", textColor, outlineColor);
    while (running) {
            waitPress(e,running, ok);
     //   SDL_DestroyTexture(outlineTex);
            rStart(lastTime, toggleText, bgr, ren, textTex);

    }
    //bdau background trôi -> hiện chim

    srand(time(0));
    if(ok == 1)
    {
        int frame = 0;
        running = true;
        bgr = loadTexture("Data/Image/background2.jpg", ren);
        rebegin(bgr, ren, running, e);
        SDL_Texture* nen = loadTexture("Data/Image/nendat.jpg", ren);
        int check = 1;
        Uint32 lastFrameTime = SDL_GetTicks();
        initPipes(pipes);
        loadHighScore();
//        renderPipes(ren, upperPipeTex, lowerPipeTex, pipes);
//        SDL_RenderPresent( ren );
//
        bool die = false;
        SDL_Rect textRect;
        TTF_Font* font2 = TTF_OpenFont("Data/FONT/Consolas.ttf", 24);
        if (!font2) {
            SDL_Log("Không thể tải font: %s", TTF_GetError());
            SDL_DestroyTexture(bgr);
            SDL_Quit();
            return 0;
        }
        while(running)
        {
        waitPress2(running, e, birdVelocity, JUMP_FORCE);

        update_bird(birdVelocity, birdY, birdRect, birdAngle);
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

           SDL_Texture* currentBird = birdImages[(frame / birdDelay) % 2];


            render_bird(ren, currentBird, birdRect, birdAngle);
            SDL_Delay(16);
            checkPass(pipes, score);
             if(!vacham(pipes, birdY)) running = false, die = true;
              // Màu trắng
//              //in điểm hiện tại
        SDL_Texture* textTexture = createText(ren, font2, to_string(score), white, white);
        SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
        SDL_Rect textRect = {(SCREEN_WIDTH - textW * 2) / 2, 20, textW*2, 50};
        SDL_RenderCopy(ren, textTexture, NULL, &textRect);
        textTexture = createText(ren, font2, "BEST SCORE: " + to_string(highScore), lightPink, lightPink);
         SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
        textRect = {20, 10, textW, 15};
        SDL_RenderCopy(ren, textTexture, NULL, &textRect);
            SDL_RenderPresent(ren);

                frame++;



        }
            if(die)
            {

            }
    }



//        if(check)
//        {
//
//        }





      TTF_CloseFont(font);
// day la ket thuc

    Exit(birdImages, window, ren, bgr, upperPipeTex, lowerPipeTex);
    return 0;
}



