#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "background.h"
#include "overall.h"
#include <SDL_ttf.h>


int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    // tạo cửa sổ màn hình game
    SDL_Renderer* ren = createRenderer(window);

    SDL_Texture* bgr = loadTexture("Data/Image/begin_BR.jpg", ren);
    SDL_RenderCopy( ren, bgr, NULL, NULL); //không quan tâm vị trí, kích thước ảnh
//
    SDL_RenderPresent( ren );
    //waitUntilKeyPressed();

      SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) { // Nhấn ESC để thoát
                    running = false;
                }
//                if (e.key.keysym.sym == SDLK_RETURN) { // Nhấn ENTER để chuyển ảnh
//                    currentImage = (currentImage == image1) ? image2 : image1;
//                }
            }
        }
    }
// day la code thu
if (TTF_Init() == -1) {
    SDL_Log("Lỗi khởi tạo SDL_ttf: %s", TTF_GetError());
    return -1;
}

    // 5️⃣ Tải font chữ
    TTF_Font* font = TTF_OpenFont("Consolas.ttf", 48); // Cỡ chữ 48px
    if (!font) {
        SDL_Log("Không thể tải font: %s", TTF_GetError());

        SDL_Quit();
        return -1;
    }

    // 6️⃣ Tạo màu chữ vàng
    SDL_Color textColor = {255, 255, 0, 255}; // {R, G, B, A} -> {255, 255, 0} là màu vàng

    // 7️⃣ Tạo surface từ chữ
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello", textColor);
    if (!textSurface) {
        SDL_Log("Không thể tạo surface chữ: %s", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // 8️⃣ Tạo texture từ surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
    SDL_FreeSurface(textSurface); // Giải phóng surface sau khi tạo texture

    // 9️⃣ Định vị trí vẽ chữ trên màn hình
    SDL_Rect textRect = {200, 200, 200, 100}; // (x, y, width, height)




//        // Xóa màn hình với màu đen
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);

        // Vẽ chữ lên renderer
        SDL_RenderCopy(ren, textTexture, NULL, &textRect);

        // Hiển thị nội dung đã render lên màn hình
        SDL_RenderPresent(ren);
    //}

    // 🔚 Giải phóng tài nguyên trước khi thoát




//// day la ket thuc
//    SDL_DestroyTexture(bgr);
//    SDL_DestroyRenderer(ren);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
}
