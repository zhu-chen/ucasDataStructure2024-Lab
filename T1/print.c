#include "chess.h"

const int SQUARE_SIZE = 80; // 每个棋盘格的大小
const int BOARD_SIZE = 8;   // 棋盘的大小

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
TTF_Font* font = NULL;

int init() {
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // 创建窗口
    window = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 获取窗口表面
    screenSurface = SDL_GetWindowSurface(window);
    if (screenSurface == NULL) {
        printf("Could not get window surface! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 初始化SDL_ttf库
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    font = TTF_OpenFont("Roboto-Black.ttf", 32);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    return 0;
}

void print() {
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

            // 在格子中间显示数字
            if (chessboard[i][j] != 0) { // 0表示未访问过的格子，不显示数字
                SDL_Color textColor = {0, 0, 0};
                if ((i + j) % 2 == 0) {
                    textColor.r = 0;
                    textColor.g = 0;
                    textColor.b = 0; // 白色字体
                } else {
                    textColor.r = 255;
                    textColor.g = 255;
                    textColor.b = 255; // 黑色字体
                }

                // 创建文本
                char text[3]; // 存放单个字符数字 + 终止符
                snprintf(text, sizeof(text), "%d", chessboard[i][j]);

                // 使用SDL_ttf库加载字体文件和设置字体大小
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
                if (textSurface == NULL) {
                    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
                } else {
                    // 将文本表面复制到屏幕表面上，位置居中
                    SDL_Rect textRect;
                    textRect.x = rect.x + (SQUARE_SIZE - textSurface->w) / 2;
                    textRect.y = rect.y + (SQUARE_SIZE - textSurface->h) / 2;
                    textRect.w = textSurface->w;
                    textRect.h = textSurface->h;

                    SDL_BlitSurface(textSurface, NULL, screenSurface, &textRect);
                    //SDL_FreeSurface(textSurface); // 释放文本表面资源
                }

                //TTF_CloseFont(font); // 关闭字体
            }
        }
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(1000); // 等待两秒

    // 清理SDL和SDL_ttf
    //TTF_Quit();
    //SDL_DestroyWindow(window);
    //SDL_Quit();
}
