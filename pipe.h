#ifndef pipe_h
#define pipe_h
#include <vector>
#include "overall.h"
const int PIPE_WIDTH = 65;
const int PIPE_HEIGHT = 373;
const int PIPE_GAP = 160;
const int PIPE_SPEED = 3;
using namespace std;

const  int randMax = SCREEN_HEIGHT - margin_bottom - PIPE_GAP - 10;
const int randMin = 30;
struct Pipe {
    int x, y;
    bool passed;
};

int Rand(int l, int r)
{
    return l + rand() % (r - l + 1);
}


void initPipes(vector<Pipe> &pipes) {
   // pipes.push_back({SCREEN_WIDTH, Rand(30, (SCREEN_HEIGHT - PIPE_GAP - 150)), false});
   pipes.push_back({SCREEN_WIDTH,  (Rand(randMin, randMax)), false});
}

void updatePipes(vector<Pipe> &pipes, const float speedF) {
    for (auto &pipe : pipes) {
        pipe.x -= PIPE_SPEED * speedF;
    }
    if (!pipes.empty() && pipes.front().x + PIPE_WIDTH < 0) {
        pipes.erase(pipes.begin());
    }
    if (pipes.empty() || pipes.back().x < SCREEN_WIDTH - 250) {
        initPipes(pipes);
    }
}

void renderPipes(SDL_Renderer* ren, SDL_Texture* upperPipeTex, SDL_Texture* lowerPipeTex, vector<Pipe> &pipes) {
    int texW, texH;
    SDL_QueryTexture(upperPipeTex, NULL, NULL, &texW, &texH);
    for (const auto &pipe : pipes) {
        SDL_Rect upperPipe = {pipe.x, 0, PIPE_WIDTH, pipe.y};
        SDL_Rect lowerPipe = {pipe.x, pipe.y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - (pipe.y + PIPE_GAP) - margin_bottom};
        SDL_Rect URect = {0, texH - pipe.y, texW, pipe.y};
        SDL_Rect LRect = {0, 0, texW, SCREEN_HEIGHT - (pipe.y + PIPE_GAP) - margin_bottom};
        SDL_RenderCopy(ren, upperPipeTex, &URect, &upperPipe);
        SDL_RenderCopy(ren, lowerPipeTex, &LRect, &lowerPipe);
    }
}



#endif // pipe_h
