// This is a header guard, its for systems that doesn't understand pragma once

#ifndef GAME_H
#define GAME_H
#include "vector.h"
#include <SDL.h>

class Game {
public:
    Game(const char* Title, int Width, int Height);
    ~Game();

    // A static renderer so as long as we include game.h we can get the renderer
    static SDL_Renderer* renderer;

    // A refference function to see if the running is still true
    bool& isRunning() {
        return running;
    }

    // A function to load a texture that takes a path to the texture
    SDL_Texture* texLoader(const char* texturePath);

    // A void function to run before we hit the main loop
    void awakeInit();

    // Code in the main loop
    void clear(); // Clear screen
    void eventHandler(); // Handle inputs
    void update(double& delta); // Update function with delta time reference
    void graphics(); // Render graphics function
    void display(); // Display everything saved in the back buffer

private: 
    bool running { false }; // A bool so we know if we are running and initialize it as false
    Vector2i displaySize{ 0, 0 };

    SDL_Window* window { nullptr }; // A pointer to the window and initialize it as a nullptr
};

#endif