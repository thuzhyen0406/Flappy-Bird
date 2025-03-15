#ifndef bird_h
#define bird_h
#include "pipe.h"

using namespace std;
SDL_Texture* birdImages[2] = {nullptr, nullptr};
const int BIRD_X = 300;
const int BIRD_Y = 250;
const int birdDelay = 10;

const float GRAVITY = 0.4f; // Trọng lực kéo chim xuống
const float JUMP_FORCE = -7.0f; // Lực nhảy lên
float birdVelocity = 0; // Vận tốc chim
int birdY = BIRD_Y;
SDL_Rect birdRect = {BIRD_X, BIRD_Y, 50, 50};
bool loadMedia(SDL_Renderer* ren) {
    birdImages[0] = loadTexture("Data/Image/bird3.png", ren);
    birdImages[1] = loadTexture("Data/Image/bird4.png", ren);

    return birdImages[0] && birdImages[1];
}

void update_bird(float &birdVelocity, int &birdY, SDL_Rect &birdRect)
{
    birdVelocity += GRAVITY;
    birdY += birdVelocity;

            // Giới hạn chim không rơi quá sàn hoặc bay ra khỏi màn hình
            if (birdY > SCREEN_HEIGHT - margin_bottom - 50) {
                birdY = SCREEN_HEIGHT - margin_bottom - 50;
                birdVelocity = 0;
            }
            if (birdY < 0) {
                birdY = 0;
                birdVelocity = 0;
            }
            birdRect = {BIRD_X, birdY, 50, 50};
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    if(a.y <= 0 || a.y + 50 >= SCREEN_HEIGHT - margin_bottom) return true;
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

bool vacham(vector <Pipe> &pipes, int &birdY)
{
    Pipe *nextPipe = nullptr;
   for (Pipe& pipe : pipes) {
    if (pipe.x + PIPE_WIDTH > BIRD_X) { // Chỉ xét các ống có thể va chạm
        nextPipe = &pipe;
        break;
        }
    }

// Nếu có ống cần kiểm tra, chỉ kiểm tra 1 lần
    if (nextPipe) {
    SDL_Rect birdRect = {BIRD_X, birdY, 50, 50};
    SDL_Rect upperPipeRect = {nextPipe->x, 0, PIPE_WIDTH, nextPipe->y};
    SDL_Rect lowerPipeRect = {nextPipe->x, nextPipe->y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT -  (nextPipe->y + PIPE_GAP) - margin_bottom};

    if (checkCollision(birdRect, upperPipeRect) || checkCollision(birdRect, lowerPipeRect)) {
            return false;
        }
    }
    return true;
}

#endif // bird_h
