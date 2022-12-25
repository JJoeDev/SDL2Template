#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

// Initialise SDL and SDL_Image to use both
bool sdlInit() {
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cerr << "SDL INIT FAILED: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cerr << "SDL IMG INIT FAILED: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// This calls the init function for SDL, and checks if the init was successfull. If it was successfull running will be true
bool isInit = sdlInit();
bool running = true ? isInit : !isInit;

// Set a screen width and height. Then initialize the SDL window with a title and width and height
const int x = 1280;
const int y = 720;
RenderWindow window("SDL2 Template", x, y);

// Store textures here for use in the graphics and update loops. Also used to make entities
SDL_Texture* somePNG = window.loadTexture("image.png");
SDL_Texture* manTex = window.loadTexture("15PXman.png");
SDL_Texture* JJoeTex = window.loadTexture("JJOE.png");

// These are entities. They use a Vector2 loat, an angle (rotation) and a texture
Entity man(Vector2f(300, 300), 0, manTex);
Entity jjoe(Vector2f(130, 130), 0, JJoeTex);

// Ticks are used for calculating delta time, so we can get consistant movement and rotation across different framerates
Uint64 curTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

// An event to get inputs from the user
SDL_Event event;

void update() {
    // This will calculate delta time every frame
    lastTick = curTick;
    curTick = SDL_GetPerformanceCounter();
    deltaTime = (double)((curTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

    // This loop will only run if there is an event, this will handle all input
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        }
    }

    // This will rotate the entity named man
    man.setAngle(man.getAngle() += 0.1 * deltaTime);

    // This will move the entity named jjoe untill its X position is no longer less than the window width
    if (jjoe.getPos().x < x) {
        jjoe.setPos(Vector2f(jjoe.getPos().x += (double)1.5f, jjoe.getPos().y));
    }
        
}

// This is a graphics loop used to render everything
void graphics() {
    // The clear function will clear all graphics data from the previous run from the GPU
    window.clear();

    // All rendering should be between clear and display. This changes the background color
    window.renderBackgroundColor(107, 46, 181, 80);

    // these functions will render a texture, with a X, Y, W, H, and a texture
    window.renderTex({ 50, 50, 3, 3 }, somePNG);

    // This will render an Entity we made earlier
    window.renderEntity(man);
    window.renderEntity(jjoe);

    // This will diplay all textures and entities to the display
    window.display();
}

int main(int argc, char* args[]) {
    // This is where the application will start
    std::cout << "Hello SDL2!" << std::endl;

    // We set the scale of our entities before running our loop
    man.setScale(Vector2f(3, 3));
    jjoe.setScale(Vector2f(0.08f, 0.08f));

    // This will run the graphics and update loop
    while (running) {
        update();
        graphics();
    }

    return 0;
}