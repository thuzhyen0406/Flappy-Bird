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
#include <SDL_mixer.h>

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


    int bgX = 0, ok = 0;
    bool showT = true, toggleText = true;
    Uint32 lastTime = SDL_GetTicks();

    pii textTex = createText(ren, font, "Press Enter to Start, Esc to Quit", textColor, brown, 2, 1);
    while (running) {
            waitPress(e,running, ok);
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

        bool die = false;

        TTF_Font* font2 = TTF_OpenFont("Data/FONT/Consolas.ttf", 24);
        if (!font2) {
            SDL_Log("Không thể tải font: %s", TTF_GetError());
            SDL_DestroyTexture(bgr);
            SDL_Quit();
            return 0;
        }

    while(running)
        {
        if(!die){
              waitPress2(running, e, birdVelocityY, JUMP_FORCE);
            }

        update_bird(birdVelocityX, birdVelocityY, birdX, birdY, birdRect, birdAngle, die);
        if(birdY >= SCREEN_HEIGHT - margin_bottom - 50)
        {
            die = true;
        }
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
             if(!vacham(pipes, birdX, birdY, die, birdVelocityX, birdVelocityY))
             {
                 update_bird(birdVelocityX, birdVelocityY, birdX, birdY, birdRect, birdAngle, die);
             }

        pii textTexture = createText(ren, font2, to_string(score), white, white, 0, 1);
        Paint_text_score1(textTexture, ren, 1);

        textTexture = createText(ren, font2, "BEST SCORE: " + to_string(highScore), lightPink, lightPink, 0, 1);

        Paint_text_score1(textTexture, ren, 2);
        SDL_RenderPresent(ren);

        frame++;

          if(die)
        {
           gDie(ren, running, e, score, highScore);
           if(running)
           {
            birdX = 200; birdY = 250;
            birdVelocityX = 0; birdVelocityY = 0;
            pipes.clear();
            initPipes(pipes);
            die = false;
            rebegin(bgr, ren, running, e);
           }

        }
    }


}




      TTF_CloseFont(font);

    //end
    Exit(birdImages, window, ren, bgr, upperPipeTex, lowerPipeTex);
    return 0;
}



