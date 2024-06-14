#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "chess.h"

void drawText(SDL_Renderer* renderer, const char* text, int x, int y) {
    // 加载字体
    TTF_Font* font = TTF_OpenFont("path/to/your/font.ttf", 24); // 设置合适的字体路径和大小
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // 创建颜色（黑色）
    SDL_Color color = {0, 0, 0, 255};

    // 创建表面
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    // 创建纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    // 获取纹理宽度和高度
    int text_width = surface->w;
    int text_height = surface->h;

    // 设置目标矩形
    SDL_Rect renderQuad = {x, y, text_width, text_height};

    // 渲染纹理到渲染器
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);

    // 清理
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void printChessboard(int chessboard[8][8]) {
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // 初始化SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow("Chessboard",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // 绘制棋盘
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            }
            SDL_Rect rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            SDL_RenderFillRect(renderer, &rect);

            // 绘制棋盘格上的数字
            char num[3];
            snprintf(num, sizeof(num), "%d", chessboard[y][x]);
            drawText(renderer, num, x * SQUARE_SIZE + 20, y * SQUARE_SIZE + 20); // 设置合适的偏移量
        }
    }

    // 更新渲染器
    SDL_RenderPresent(renderer);

    // 等待退出事件
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // 清理
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
