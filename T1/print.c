#include "chess.h"

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
                }
             }

            SDL_UpdateWindowSurface(window);

            // 等待两秒
            SDL_Delay(2000);
         }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

     return 0;
}
void print(){
    //TODO: ADD YOUR CODE HERE

}