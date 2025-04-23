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
#include <iostream>

vector<Pipe> pipes;
using namespace std;
 bool amthanh = true, getHelp = false;
 float speedF;
int main(int argc, char *argv[])
{

    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    SDL_Renderer* ren = createRenderer(window);

    SDL_Texture* upperPipeTex = loadTexture("Data/Image/pipe_up.png", ren);
    SDL_Texture* lowerPipeTex = loadTexture("Data/Image/pipe_down.png", ren);

      SDL_Event e;

    bool running = true;

        if (TTF_Init() == -1 || !loadMedia1(ren) || !loadMedia2(ren) || !loadMedia0(ren)) {
            SDL_Log("loi khoi tao: %s", TTF_GetError());
            return -1;
        }

     TTF_Font* font = TTF_OpenFont("Data/FONT/Consolas.ttf", 24);
    if (!font) {
            SDL_Log("Không thể tải font: %s", TTF_GetError());
            SDL_Quit();
            return 0;
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
       logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                        Mix_GetError() );
    }

    int bgX = 0, ok = 0;
    bool showT = true, toggleText = true;
    Uint32 lastTime = SDL_GetTicks();

    Mix_Music *RBG = loadMusic("Data/SOUND/rbg.mp3");
    SDL_Texture* bg1 = loadTexture("Data/Image/Start.png", ren);
    SDL_Texture* bg2 = loadTexture("Data/Image/Help.png", ren);
    SDL_Texture* bg3 = loadTexture("Data/Image/return.png", ren);
     SDL_Texture* bom = loadTexture("Data/Image/bom.png", ren);
      SDL_Texture* gift = loadTexture("Data/Image/gift.png", ren);
    pii textTex1 = createText(ren, font, "Press Enter to Start, Esc to Quit", textColor, brown, 2, 1);
    pii textTex2 = createText(ren, font, "Press M to turn sound on/off", textColor, brown, 2, 1);
    pii textTex3 = createText(ren, font, "Press S to stop/continue", textColor, brown, 2, 1);
    pii textTex4 = createText(ren, font, "Press R to Restart", textColor, brown, 2, 1);

     SDL_Texture* bgr1 = loadTexture("Data/Image/begin_BR.jpg", ren);
    SDL_Texture* bgr = loadTexture("Data/Image/bgrt1.jpg", ren);

    while (running) {
            waitPress(e,running, ok, amthanh, getHelp);
            if(getHelp)
                {
                    gHelp(bgr, bg3, ren, getHelp, textTex1, textTex2, textTex3, textTex4);
                }
            else
            rStart(bgr1, bg1, bg2, ren);
            if(amthanh) play(RBG);
            else if(!Mix_PausedMusic())
            {
                 Mix_PauseMusic();
            }

    }
    //bdau background trôi -> hiện chim

    srand(time(0));
    if(ok == 1)
    {
        int frame = 0;
        running = true;
     //   bgr = loadTexture("Data/Image/background2.jpg", ren);
         rebegin(bgr, ren, running, e);
        //sau khi nhan phim ->bdau
        stopMusic(RBG);
        SDL_Texture* nen = loadTexture("Data/Image/nendat.jpg", ren);
        int chay = 0;
        Uint32 lastFrameTime = SDL_GetTicks();
        initPipes(pipes);
        loadHighScore();

        bool die = false;

        TTF_Font* font2 = TTF_OpenFont("Data/FONT/arial.ttf", 24);
        if (!font2) {
            SDL_Log("Không thể tải font: %s", TTF_GetError());
            SDL_DestroyTexture(bgr);
            SDL_Quit();
            return 0;
        }


    Mix_Chunk *gJump = loadSound("Data/SOUND/bay.mp3"); //tai tieng bay
    Mix_Chunk *gD = loadSound("Data/SOUND/vacham.wav"); //tai tieng dap vao cot
    Mix_Chunk *gScore = loadSound("Data/SOUND/addscore.mp3");
    int index = 0, tmp = 0 ,res = 0, cur = 0;
    while(running)
        {
            if(GRAVITY < 0)
            {
                cur = 1;
            }
            else cur =0;
        if(birdY >= SCREEN_HEIGHT - margin_bottom - 50)
        {
            die = true;

        }
        if(score / 10 > tmp)
        {
            tmp++;
            index = (index + 1) % 2;
        }
        if(!cur) // truong hop 1
        {
            if(score > 5) {
                    PIPE_SPACE = Rand(200, 400);
            }
                if((score / 10) % 2 == 1)
            {
                PIPE_GAP = Rand(140, 180);
            }
            speedF = min(1.0f + score * 0.03f, 3.0f);

        }
        else
        {
            PIPE_SPACE = 350;
            PIPE_GAP = 200;
            speedF = 1.5f;
        }
        bgr = bgrt[index];
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

            if(!die)
             bgX -= BG_SPEED * deltaTime * 60 * speedF;

                if (bgX <= -SCREEN_WIDTH) {
                       bgX += SCREEN_WIDTH;  // Reset khi chạy hết ảnh

                }

                SDL_Rect bgRect1 = {bgX, SCREEN_HEIGHT - 76, SCREEN_WIDTH, 76};
                SDL_Rect bgRect2 = {bgX + SCREEN_WIDTH, SCREEN_HEIGHT - 76, SCREEN_WIDTH, 76};
             SDL_RenderClear(ren);
            SDL_RenderCopy(ren, bgr, NULL, NULL);
            SDL_RenderCopy(ren, nen, NULL, &bgRect1);
            SDL_RenderCopy(ren, nen, NULL, &bgRect2);
            SDL_Texture* currentBird = birdImages[(frame / birdDelay) % 2];
            if(speedF >= 2.5f) {
                    GRAVITY = 0.7f;
                      JUMP_FORCE = -10.0f;
            }
            render_bird(ren, currentBird, birdRect, birdAngle); //ve len
            if(!die){
            updatePipes(pipes, speedF);
            renderPipes(ren, upperPipeTex, lowerPipeTex, pipes, gift, bom);

            SDL_Delay(16);

               checkPass(pipes, score, gScore, amthanh);
             if(!vacham(pipes, birdX, birdY, die, birdVelocityX, birdVelocityY))
             {
                 if(amthanh) play(gD);
                 update_bird(birdVelocityX, birdVelocityY, birdX, birdY, birdRect, birdAngle, die);

             }
        }

        else {
            renderPipes(ren, upperPipeTex, lowerPipeTex, pipes, gift, bom);

        }

        pii textTexture = createText(ren, font2, to_string(score), white, white, 0, 1);
        Paint_text_score1(textTexture, ren, 1);

        textTexture = createText(ren, font, "BEST SCORE: " + to_string(highScore), lightPink, lightPink, 0, 1);

        Paint_text_score1(textTexture, ren, 2);
                if(!die){
              waitPress2(ren, chay, running, e, birdVelocityY, JUMP_FORCE, gJump, amthanh);
              SDL_RenderCopy(ren, btrs[chay], NULL, &posbtrs); //nut tam dung hay tiep tuc
            }
         // ve hinh tiep tuc
        update_bird(birdVelocityX, birdVelocityY, birdX, birdY, birdRect, birdAngle, die);

        SDL_RenderPresent(ren);

        frame++;

          if(die && birdY >= SCREEN_HEIGHT - margin_bottom - 50)
        {
           Mix_Chunk *gEnd = loadSound("Data/SOUND/roidat.mp3");
           if(amthanh)
            play(gEnd);

            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, bgr, NULL, NULL);
            SDL_RenderCopy(ren, nen, NULL, &bgRect1);
            SDL_RenderCopy(ren, nen, NULL, &bgRect2);
            SDL_Texture* currentBird = birdImages[(frame / birdDelay) % 2];
            render_bird(ren, currentBird, birdRect, birdAngle);
            renderPipes(ren, upperPipeTex, lowerPipeTex, pipes, gift, bom);
           gDie(ren, running, e, score, highScore);
           if(running)
           {
            birdX = 200; birdY = 250;
            PIPE_GAP = 180;
            PIPE_SPACE = 300;
            birdVelocityX = 0; birdVelocityY = 0;
            pipes.clear();
            initPipes(pipes);
            die = false;
            tmp = 0, cur = 0;
            GRAVITY = 0.5f;
            JUMP_FORCE = -7.0f;
            Mix_Music *RBG = loadMusic("Data/SOUND/rbg.mp3");
            if(amthanh) play(RBG);
            //rebegin(bgr, bg3, ren, running, e);
            rebegin(bgr, ren, running, e);
            stopMusic(RBG);
            chay = 0;
           }

        }
    }
        TTF_CloseFont(font2);
         SDL_DestroyTexture(nen);

}




        TTF_CloseFont(font);


    ///ket thuc
     Mix_Quit();
     SDL_DestroyTexture(bg1);
        SDL_DestroyTexture(bg2);
        SDL_DestroyTexture(bg3);
        SDL_DestroyTexture(bgr1);

    Exit(birdImages, window, ren, bgr, upperPipeTex, lowerPipeTex);
    SDL_DestroyTexture(textTex1.first);
    SDL_DestroyTexture(textTex2.first);
    SDL_DestroyTexture(textTex3.first);
    SDL_DestroyTexture(textTex4.first);

    TTF_Quit();

    IMG_Quit();
    SDL_Quit();

    return 0;
}



