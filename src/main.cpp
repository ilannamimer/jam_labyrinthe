#include <iostream>
#include "maze.hpp"
#include "menu.hpp"
#include "settings.hpp"
#include "resolution.hpp"
#include "game_context.hpp"

int main(int argc, char **argv)
{
    GameContext context;

    if (!context.initializeGame(argc, argv)) {
        return EXIT_FAILURE;
    }
    while (context.window.isOpen()) {
        context.processEvents();
        context.render();
    }
    return EXIT_SUCCESS;
}
