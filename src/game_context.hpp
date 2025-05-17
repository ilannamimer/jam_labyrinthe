#ifndef GAME_CONTEXT_HPP
    #define GAME_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "game_state.hpp"

class Menu;
class maze;
class Settings;

struct GameContext {
    sf::RenderWindow window;
    GameState gameState;
    GameState previousState;
    Menu* menu;
    maze* gameMaze;
    Settings* settings;
    bool resolutionChanged;
    std::string mapFile;
    bool mazeInitialized;
    sf::Music gameMusic;
    bool musicInitialized;

    GameContext();
    ~GameContext();
};

#endif
