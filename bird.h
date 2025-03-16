#ifndef bird_h
#define bird_h
#include "pipe.h"
#include "score.h"
using namespace std;
SDL_Texture* birdImages[2] = {nullptr, nullptr};
const int BIRD_X = 300;
const int BIRD_Y = 250;
const int birdDelay = 10;

const float GRAVITY = 0.5f; // Trọng lực kéo chim xuống
const float JUMP_FORCE = -7.0f; // Lực nhảy lên
float birdVelocityX = 0, birdVelocityY = 0; // Vận tốc chim
float birdAngle = 0;
int birdY = BIRD_Y;
int birdX = BIRD_X;
SDL_Rect birdRect = {BIRD_X, BIRD_Y, 60, 50};
bool loadMedia(SDL_Renderer* ren) {
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
        birdAngle = -10; // Khi bay lên, chim nghiêng lên trên
        }
    else if (birdVelocityY > 0)
    {
        birdAngle += 1.5; // Khi rơi xuống, dần nghiêng xuống
        if (birdAngle > 70) birdAngle = 70; // Giới hạn góc tối đa khi rơi
    }
            // Giới hạn chim không rơi quá sàn hoặc bay ra khỏi màn hình

    }
    else{
        birdVelocityY += 0.6f;  // Tăng tốc độ rơi
        birdVelocityX *= 1;   // Giảm dần tốc độ bay ngược (mô phỏng ma sát không khí)
        birdAngle -= 5;          // Chim quay nhanh hơn khi rơi
        if (birdAngle > 100) {
                birdAngle = 100;  // Giới hạn góc xoay
                die = true;
        }

        birdX += birdVelocityX;  // Cập nhật vị trí X
        birdY += birdVelocityY;
    }
     if (birdY > SCREEN_HEIGHT - margin_bottom - 50) {
                birdY = SCREEN_HEIGHT - margin_bottom - 50;
                birdVelocityY = 0;
               die = true;
            }
            if (birdY <= 0) {
                birdY = 0;
                birdVelocityY = GRAVITY;
            }

    birdRect = {birdX, birdY, 50, 50};
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    if(a.y <= 0 || a.y + 50 >= SCREEN_HEIGHT - margin_bottom) return true;
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

bool vacham(vector <Pipe> &pipes, int &birdX, int &birdY, bool &die, float &birdVelocityX, float &birdVelocityY)
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
    SDL_Rect birdRect = {birdX, birdY, 50, 50};
    SDL_Rect upperPipeRect = {nextPipe->x, 0, PIPE_WIDTH, nextPipe->y};
    SDL_Rect lowerPipeRect = {nextPipe->x, nextPipe->y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT -  (nextPipe->y + PIPE_GAP) - margin_bottom};

    if (checkCollision(birdRect, upperPipeRect) || checkCollision(birdRect, lowerPipeRect)) {
            birdVelocityX = -5; // Chim bay ngược lại
            birdVelocityY = -5;  // Chim bật lên nhẹ
            die = true;    // Bật hiệu ứng rơi
            return false;
        }

    }
    return true;
}

void checkPass(vector<Pipe> &pipes, int &score) {
    for (auto &pipe : pipes) {
        if (!pipe.passed && pipe.x + PIPE_WIDTH < BIRD_X) {
            pipe.passed = true;
            score++;
        }
    }
    updateScore(score, highScore);
}

void render_bird(SDL_Renderer* ren, SDL_Texture* birdImage, SDL_Rect &birdRect, float birdAngle) {
    SDL_Point center = {birdRect.w / 2, birdRect.h / 2};
    SDL_RenderCopyEx(ren, birdImage, NULL, &birdRect, birdAngle, &center, SDL_FLIP_NONE);
}

#endif // bird_h
