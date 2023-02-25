#undef main
#include "game.h"
#include <memory>

namespace deltaVars { // Define a namespace for the delta variables to be sure they might not get mixed up with any other libraries
    Uint64 curTick = SDL_GetPerformanceCounter();
    Uint64 lastTick{ 0 };
    double delta{ 0 };
}

using namespace deltaVars; // Use that namespace so we dont have to say deltaVars:: to everything (deltaVars::curTick = SDL_Get...)

int main(int argc, char* argv[]) { // The main function where this application will execute
    std::unique_ptr<Game> game = std::make_unique<Game>("SDL2 Template Title", 1280, 720); // Make a pointer to the game file so we can easily get the functions inside

    if (game->isRunning()) // Check if we successfully initialized Game. If so run the awakeInit function
        game->awakeInit();

    while (game->isRunning()) { // Main loop that starts by calculating deltaTime
        lastTick = curTick;
        curTick = SDL_GetPerformanceCounter();
        delta = (double)((curTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

        // Game functions that will get called every time
        game->clear();
        game->eventHandler();
        game->update(delta);
        game->graphics();
        game->display();
    }

    return 0;
}