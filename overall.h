#ifndef OVERALL_H
#define OVERALL_H

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 500;
const int margin_bottom = 74;
const int BG_SPEED = 3;
bool toggleText = true;  // Bật/Tắt chữ
unsigned int lastTime = 0;

SDL_Rect govRect = {190, -50, 490, 490};

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
                else
                    return 1;  // Nhấn phím khác -> Bắt đầu
            }
       if( e.type == SDL_MOUSEBUTTONDOWN) return 1;

        }

        SDL_Delay(100);
    }
}


void waitPress(SDL_Event &e, bool &running, int &ok)
{

    while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false, ok = 0;
                }
                else running = false, ok = 1;

            }
            else if(e.type ==  SDL_MOUSEBUTTONDOWN)
            {
                running = false, ok = 1;
            }

        }
}

void waitPress2(bool &running, SDL_Event &e,float &birdVelocity, float const JUMP_FORCE)
{
     while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                else birdVelocity = JUMP_FORCE;


            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
                 birdVelocity = JUMP_FORCE;

     }
}


bool waitPress3(SDL_Event &e)
{
    while (SDL_PollEvent(&e)) {

        if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_r) return true;
                else return false;
            }
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE) return false;
        }
        if (e.type == SDL_QUIT) {
                return false;
            }

     }

}
#endif // OVERALL_H
