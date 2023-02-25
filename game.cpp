// This will be where the whole game takes place, instead of the main.cpp file

#include "game.h"
#include "Entity.h"
#include <iostream>
#include <SDL_image.h>

SDL_Renderer* Game::renderer{ nullptr }; // Initialize the renderer as a null pointer
 
namespace textures {
    SDL_Texture* somePNG{ nullptr };
    SDL_Texture* manTex{ nullptr };
    SDL_Texture* JJoeTex{ nullptr };
}

namespace entities {
    Entity* man{ nullptr };
    Entity* jjoe{ nullptr };
}

Game::Game(const char* Title, int Width, int Height) : displaySize(Width, Height) {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 0) { // SDL_Init() and SDL_InitSubSystem() is the same thing, if its == 0 it was a success
        window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!window && !renderer) {
            std::cerr << "FAILED TO INIT WINDOW OR RENDERER: " << SDL_GetError() << std::endl;
            return;
        }

        if (!IMG_Init(IMG_INIT_JPG)) {
            std::cerr << "IMG INIT FAILED: " << SDL_GetError() << std::endl;
            return;
        }
    }

    running = true;
}

Game::~Game() {
    delete[] entities::man;
    delete[] entities::jjoe;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit;
}

SDL_Texture* Game::texLoader(const char* texturePath) {
    SDL_Texture* tempTex{ nullptr };

    tempTex = IMG_LoadTexture(renderer, texturePath);

    if (!tempTex) {
        std::cerr << "FAILED TO LOAD TEXTURE: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return tempTex;
}

void Game::awakeInit() {
    textures::somePNG = texLoader("image.png"); // Loads all the needed textures
    textures::manTex = texLoader("15PXman.png");
    textures::JJoeTex = texLoader("JJOE.png");

    entities::man = new Entity(Vector2f(300, 300), 0, textures::manTex); // Initializes man and jjoe entity
    entities::jjoe = new Entity(Vector2f(130, 130), 0, textures::JJoeTex);

    entities::man->setScale(Vector2f(3.0, 3.0)); // Sets the scale of the man and jjoe entity
    entities::jjoe->setScale(Vector2f(0.08, 0.08));
}

void Game::clear() {
    SDL_RenderClear(renderer);
}

void Game::eventHandler() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        }
    }
}

void Game::update(double& delta) {
    entities::man->setAngle(entities::man->getAngle() += 0.1 * delta);

    // You could say using namespace entities here, you could also just not use namespaces in this case, but I like to have them
    if (entities::jjoe->getPos().x < displaySize.x) {
        entities::jjoe->setPos(Vector2f(entities::jjoe->getPos().x += 0.15 * delta, entities::jjoe->getPos().y));
    }
}

void Game::graphics() { // This gives the back buffer a background color and then tells it to render the two entities
    SDL_SetRenderDrawColor(renderer, 0, 160, 160, 255);

    entities::man->renderEntity();
    entities::jjoe->renderEntity();
}

void Game::display() {
    SDL_RenderPresent(renderer);
}