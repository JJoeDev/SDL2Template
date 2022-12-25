#pragma once

#include<SDL.h>

#include "Entity.h"

class RenderWindow {
public:
    // These are the windows constructor and deconstructor
    RenderWindow(const char* title, const int xSize, const int ySize);
    ~RenderWindow();

    // This is the clear function for the graphics loop
    void clear();

    // These are the functions for loading a texture, rendering a texture, and rendering an entity
    SDL_Texture* loadTexture(const char* filePath);
    void renderTex(SDL_Rect transform, SDL_Texture* texture);
    void renderEntity(Entity& entity);

    // This is a function for making a background color
    void renderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    // This is the function for displaying everything to the display
    void display();

private:
    // These are the SDL window and renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};