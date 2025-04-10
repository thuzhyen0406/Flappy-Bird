#ifndef bird_h
#define bird_h
#include "pipe.h"
#include "score.h"
#include "music.h"
using namespace std;
SDL_Texture* birdImages[2] = {nullptr, nullptr};
const int BIRD_X = 300;
const int BIRD_Y = 250;
const int birdDelay = 10;

const float GRAVITY = 0.5f;
const float JUMP_FORCE = -7.0f; // Luc nhay
float birdVelocityX = 0, birdVelocityY = 0; // van toc
float birdAngle = 0;
int birdY = BIRD_Y;
int birdX = BIRD_X;
SDL_Rect birdRect = {BIRD_X, BIRD_Y, 45, 45};

bool loadMedia1(SDL_Renderer* ren) {
    birdImages[0] = loadTexture("Data/Image/bird3.png", ren);
    birdImages[1] = loadTexture("Data/Image/bird4.png", ren);

    return birdImages[0] && birdImages[1];
}

void update_bird(float &birdVelocityX, float &birdVelocityY, int &birdX, int &birdY, SDL_Rect &birdRect,  float &birdAngle, bool &die)
{
    if(!die){
    birdVelocityY += GRAVITY;
    birdY += birdVelocityY;
     if (birdVelocityY < 0) {
        birdAngle = -10;
        }
    else if (birdVelocityY > 0)
    {
        birdAngle += 1.5;
        if (birdAngle > 50) birdAngle = 50;
    }

    }
    else{
        birdVelocityY += 0.3f;
        birdAngle -= 3;
        if (birdAngle < -50) {
                birdAngle = -50;
                die = true;
        }

        birdX += birdVelocityX;  // Cập nhật vị trí X
        birdY += birdVelocityY;
    }
     if (birdY > SCREEN_HEIGHT - margin_bottom - 45) {
                birdY = SCREEN_HEIGHT - margin_bottom - 45;
                birdVelocityY = 0;
               die = true;
            }
    if (birdY <= 0) {
                birdY = 0;
                die = true;
            }

    birdRect = {birdX, birdY, 45, 45};
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b, const int tmp) {
    if(a.y <= 0 || a.y + 50 >= SCREEN_HEIGHT - margin_bottom) return true;
    if(tmp == 1)
    {
        if(a.x + a.w < b.x || b.x + b.w < a.x || a.y > b.y + b.h) return false;
    }
    else
    {
        if(a.x + a.w < b.x || b.x + b.w < a.x || a.y + a.h < b.y) return false;
    }
        return true;
}

bool vacham(vector <Pipe> &pipes, int &birdX, int &birdY, bool &die, float &birdVelocityX, float &birdVelocityY)
{
    Pipe *nextPipe = nullptr;
   for (Pipe& pipe : pipes) {
    if (pipe.x + PIPE_WIDTH > birdX) {
        nextPipe = &pipe;
        break;
        }

    }


    if (nextPipe) {
    SDL_Rect birdRect = {birdX, birdY, 45, 45};
    SDL_Rect upperPipeRect = {nextPipe->x, 0, PIPE_WIDTH, nextPipe->y};
    SDL_Rect lowerPipeRect = {nextPipe->x, nextPipe->y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT -  (nextPipe->y + PIPE_GAP) - margin_bottom};

    if (checkCollision(birdRect, upperPipeRect, 1)) {
            birdVelocityX = -3;
            birdVelocityY = 0;
            die = true;
            return false;
        }
        if(checkCollision(birdRect, lowerPipeRect, 2)){
             birdVelocityX = -3;
            birdVelocityY = -4;
            die = true;
            return false;
        }

    }
    return true;
}

void checkPass(vector<Pipe> &pipes, int &score,  Mix_Chunk* gScore, const bool amthanh) {
    for (auto &pipe : pipes) {
        if (!pipe.passed && pipe.x + PIPE_WIDTH < BIRD_X) {
            pipe.passed = true;
            score++;
            if(amthanh) play(gScore);
        }
    }
    updateScore(score, highScore);
}

void render_bird(SDL_Renderer* ren, SDL_Texture* birdImage, SDL_Rect &birdRect, float birdAngle) {
    SDL_Point center = {birdRect.w / 2, birdRect.h / 2};
    SDL_RenderCopyEx(ren, birdImage, NULL, &birdRect, birdAngle, &center, SDL_FLIP_NONE);
}

#endif // bird_h
