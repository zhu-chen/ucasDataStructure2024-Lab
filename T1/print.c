#include "chess.h"

const int SQUARE_SIZE = 80; // 每个棋盘格的大小
const int BOARD_SIZE = 8;   // 棋盘的大小

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
TTF_Font* font = NULL;
SDL_Surface* horseSurface = NULL;

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

     // 初始化SDL_image库
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void print() {
    int max = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (chessboard[i][j] > max)
                max = chessboard[i][j];

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

            if (chessboard[i][j] == max) {
                SDL_Surface* loadedSurface = IMG_Load("horse.png");
                if (loadedSurface == NULL) {
                    printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
                } else {
                    // 缩放马的图像大小为原始大小的1/5
                    SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, loadedSurface->w / 4, loadedSurface->h / 4, 32, 0, 0, 0, 0);
                    SDL_BlitScaled(loadedSurface, NULL, scaledSurface, NULL);

                    // 将缩放后的马的图像转换为窗口表面的格式
                    SDL_Surface* optimizedSurface = SDL_ConvertSurface(scaledSurface, screenSurface->format, 0);
                    if (optimizedSurface == NULL) {
                        printf("Unable to optimize image surface! SDL Error: %s\n", SDL_GetError());
                    } else {
                        // 设置马的位置
                        SDL_Rect horseRect;
                        horseRect.x = rect.x + (SQUARE_SIZE - optimizedSurface->w) / 2;
                        horseRect.y = rect.y + (SQUARE_SIZE - optimizedSurface->h) / 2;
                        horseRect.w = optimizedSurface->w;
                        horseRect.h = optimizedSurface->h;

                        // 将马的图像绘制到屏幕表面上
                        SDL_BlitSurface(optimizedSurface, NULL, screenSurface, &horseRect);
                    }

                SDL_FreeSurface(scaledSurface);
                SDL_FreeSurface(optimizedSurface);
                SDL_FreeSurface(loadedSurface); // 释放加载的图片表面
                }  
            }
            else {
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
    }

    SDL_UpdateWindowSurface(window);
    if (max != 64)
        SDL_Delay(1000); // 等待一秒
    else if (max == 64)
        SDL_Delay(10000); // 等待十秒

    // 清理SDL和SDL_ttf
    //TTF_Quit();
    //SDL_DestroyWindow(window);
    //SDL_Quit();
}
