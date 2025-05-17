#include "game_context.hpp"
#include "menu.hpp"
#include "maze.hpp"
#include "settings.hpp"

GameContext::GameContext()
    : gameState(MENU),
      previousState(MENU),
      menu(nullptr),
      gameMaze(nullptr),
      settings(nullptr),
      resolutionChanged(false),
      mazeInitialized(false),
      musicInitialized(false)
{
}

GameContext::~GameContext()
{
    if (menu) {
        delete menu;
        menu = nullptr;
    }
    if (gameMaze) {
        delete gameMaze;
        gameMaze = nullptr;
    }
    if (settings) {
        delete settings;
        settings = nullptr;
    }
}
