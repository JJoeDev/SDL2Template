#include <iostream>
#include <SDL_image.h>

#include "RenderWindow.h"

// This will simply init SDL window and renderer with error handeling
// The renderer will use the GPU and Vsync
RenderWindow::RenderWindow(const char* title, const int xSize, const int ySize) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xSize, ySize, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "WINDOW CREATION FAILED: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "RENDERER CREATION FAILED: " << SDL_GetError() << std::endl;
        return;
    }
}

// This is the deconstructor that will destroy and quit everything
RenderWindow::~RenderWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

// This will try to get the texture at a given file path
SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(renderer, filePath);

    if (tex == nullptr)
        std::cerr << "FAILED TO LOAD IMAGE: " << SDL_GetError() << std::endl;

    return tex;
}

// This will clear everyting from the GPU
void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

// This will render a texture with a X and Y position. It will just the textures width and height and times your own width and height on it
void RenderWindow::renderTex(SDL_Rect transform, SDL_Texture* texture) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = transform.x;
    dst.y = transform.y;
    dst.w = src.w * transform.w;
    dst.h = src.h * transform.h;

    SDL_RenderCopy(renderer, texture, &src, &dst);
}

// This will render an entity, it takes the address of an entity and uses the entities position and scale to render at the right position
void RenderWindow::renderEntity(Entity& entity) {
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = entity.getPos().x - src.w * entity.getScale().x / 2;
    dst.y = entity.getPos().y - src.h * entity.getScale().y / 2;
    dst.w = src.w * entity.getScale().x;
    dst.h = src.h * entity.getScale().y;

    // This will render the position, scale, and rotation
    SDL_RenderCopyEx(renderer, entity.getTexture(), &src, &dst, entity.getAngle(), nullptr, SDL_FLIP_NONE);
}

// This will render a background color
void RenderWindow::renderBackgroundColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A) {
    SDL_SetRenderDrawColor(renderer, R, G, B, A);
}

// This will display everything to the screen
void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}