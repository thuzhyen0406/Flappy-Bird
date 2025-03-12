#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "background.h"
#include "overall.h"
#include <SDL_ttf.h>
#include "text.h"

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

    SDL_Color textColor = {255, 255, 102, 255}, outlineColor = {0, 0, 0, 255};

     SDL_Texture* textTex = createText(ren, font, "Press Enter to Start, Esc to Quit", textColor, outlineColor);

    SDL_Rect textRect = {200, 350, 320, 25};

    bool showT = true;
    while (running) {

     //   SDL_DestroyTexture(outlineTex);
     if (SDL_GetTicks() - lastTime > 800) {
            toggleText = !toggleText;
            lastTime = SDL_GetTicks();
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bgr, NULL, NULL);
        if (toggleText && showT) {
            SDL_RenderCopy(ren, textTex, NULL, &textRect);
        }

        SDL_RenderPresent(ren);


        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }

                if (e.key.keysym.sym == SDLK_RETURN) {
                     //ren = createRenderer(window);
                     SDL_RenderClear(ren);
                        SDL_DestroyTexture(bgr);
                          bgr = loadTexture("Data/Image/background2.jpg", ren);
                            SDL_RenderCopy( ren, bgr, NULL, NULL);
                            SDL_RenderPresent( ren );
                            showT = false;
                }


            }
        }



    }

      TTF_CloseFont(font);
// day la ket thuc
    SDL_DestroyTexture(bgr);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
