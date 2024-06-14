#include "chess.h"

#include <SDL2/SDL_ttf.h>


const int SQUARE_SIZE = 50; // 每个棋盘格的大小
const int BOARD_SIZE = 8; // 棋盘的大小

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            screenSurface = SDL_GetWindowSurface(window);

            // 初始化SDL_ttf库
            if (TTF_Init() == -1) {
                printf("TTF_Init: %s\n", TTF_GetError());
                exit(2);
            }

            // 打开字体文件
            TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
            if (font == NULL) {
                printf("TTF_OpenFont: %s\n", TTF_GetError());
                // handle error
            }

            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    SDL_Rect rect;
                    rect.x = i * SQUARE_SIZE;
                    rect.y = j * SQUARE_SIZE;
                    rect.w = SQUARE_SIZE;
                    rect.h = SQUARE_SIZE;

                    // 根据 i 和 j 的和是奇数还是偶数来决定颜色
                    if ((i + j) % 2 == 0) {
                        SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); // 白色
                    } else {
                        SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00)); // 黑色
                    }

                    // 创建一个包含数字的表面
                    char text[2];
                    sprintf(text, "%d", i * BOARD_SIZE + j);
                    SDL_Color textColor = {0, 0, 0};
                    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);

                    // 将文本表面绘制到屏幕上
                    SDL_BlitSurface(textSurface, NULL, screenSurface, &rect);

                    // 释放文本表面
                    SDL_FreeSurface(textSurface);
                }
            }

            SDL_UpdateWindowSurface(window);

            // 等待两秒
            SDL_Delay(5000);

            // 释放字体
            TTF_CloseFont(font);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
void print(){
    //TODO: ADD YOUR CODE HERE

}