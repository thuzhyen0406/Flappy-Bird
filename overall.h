#ifndef OVERALL_H
#define OVERALL_H

const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 450;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

#endif // OVERALL_H
