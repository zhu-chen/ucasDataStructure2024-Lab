#include "chess.h"

const int SQUARE_SIZE = 50; // 每个棋盘格的大小
const int BOARD_SIZE = 8;   // 棋盘的大小

// 假设已知的棋盘数组，用于示例
// int chessboard[8][8] = {
//     {1, 2, 3, 4, 5, 6, 7, 8},
//     {9, 10, 11, 12, 13, 14, 15, 16},
//     {17, 18, 19, 20, 21, 22, 23, 24},
//     {25, 26, 27, 28, 29, 30, 31, 32},
//     {33, 34, 35, 36, 37, 38, 39, 40},
//     {41, 42, 43, 44, 45, 46, 47, 48},
//     {49, 50, 51, 52, 53, 54, 55, 56},
//     {57, 58, 59, 60, 61, 62, 63, 64}
// };


int print(int argc, char* args[]) {
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
                printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            } else {
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
                        if(chessboard[i][j] == 0) continue; // 0表示未访问过的格子，不显示数字
                       SDL_Color textColor = {0,0,0};
if((i+j)%2==0) {
    textColor.r = 0;
    textColor.g = 0;
    textColor.b = 0; // 白色字体
} else {
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255; // 黑色字体
}
                        SDL_Surface* textSurface = NULL;
                        SDL_Texture* textTexture = NULL;

                        // 创建文本
                        char text[3]; // 存放单个字符数字 + 终止符
                        snprintf(text, sizeof(text), "%d", chessboard[i][j]);

                        // 使用SDL_ttf库加载字体文件和设置字体大小
                        TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf", 28);
                        if (font == NULL) {
                            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
                        } else {
                            textSurface = TTF_RenderText_Solid(font, text, textColor);
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
                                SDL_FreeSurface(textSurface); // 释放文本表面资源
                            }

                            TTF_CloseFont(font); // 关闭字体
                        }
                    }
                }

                SDL_UpdateWindowSurface(window);

                // 等待两秒
                SDL_Delay(500);
            }

            TTF_Quit(); // 退出SDL_ttf库
        }

        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}
