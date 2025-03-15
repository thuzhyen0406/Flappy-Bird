#ifndef OVERALL_H
#define OVERALL_H

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 500;
const int margin_bottom = 74;
const int BG_SPEED = 2;
bool toggleText = true;  // Bật/Tắt chữ
unsigned int lastTime = 0;

int waitUntilKeyPressed(SDL_Event &e)
{
    while (true) {
       if (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                return 0; // Nếu đóng cửa sổ thì cũng thoát
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    return 0; // Nhấn ESC -> Thoát
                else
                    return 1;  // Nhấn phím khác -> Bắt đầu
            }
       if( e.type == SDL_MOUSEBUTTONDOWN) return 1;

        }
   //     return 2;
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
#endif // OVERALL_H
