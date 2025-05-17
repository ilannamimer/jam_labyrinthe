#include <iostream>
#include "maze.hpp"
#include "menu.hpp"
#include "settings.hpp"
#include "resolution.hpp"
#include "game_context.hpp"

bool initializeGame(GameContext& context, int argc, char** argv)
{
    ResolutionManager::initialize();
    const Resolution& initialRes = ResolutionManager::getCurrentResolutionInfo();

    context.window.create(sf::VideoMode(initialRes.width, initialRes.height),
    "MAZE RUNNER: SHIFT CONTROL", sf::Style::Resize | sf::Style::Close);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    context.window.setPosition(sf::Vector2i(
        (desktop.width - initialRes.width) / 2,
        (desktop.height - initialRes.height) / 2
    ));
    if (argc == 2)
        context.mapFile = argv[1];
    context.menu = new Menu();
    context.gameMaze = new maze();
    if (!context.menu->initialize()) {
        std::cerr << "Failed to initialize menu" << std::endl;
        return false;
    }
    context.settings = new Settings(context.menu->getMusic());
    if (!context.settings->initialize()) {
        std::cerr << "Failed to initialize settings" << std::endl;
        return false;
    }
    if (!context.gameMusic.openFromFile("assets/song/game_song.ogg")) {
        std::cerr << "Warning: Could not load game music" << std::endl;
    } else {
        context.gameMusic.setLoop(true);
        context.musicInitialized = true;
    }
    return true;
}

void processEvents(GameContext& context)
{
    sf::Event event;
    
    while (context.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            context.window.close();
        switch (context.gameState) {
            case MENU:
                context.menu->handleEvents(context.window, event, context.gameState);
                break;
            case SETTINGS:
                context.settings->handleEvents(context.window, event, context.gameState, context.resolutionChanged);
                break;
            case GAME:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    context.previousState = context.gameState;
                    context.gameState = MENU;
                    if (context.musicInitialized) {
                        context.gameMusic.stop();
                        context.menu->getMusic().play();
                    }
                }
                context.gameMaze->take_commande(context.window, event);
                break;
            default:
                break;
        }
    }
    if (context.resolutionChanged) {
        context.menu->updateForResolution();
        context.resolutionChanged = false;
    }
    if (context.previousState != context.gameState) {
        if (context.gameState == GAME && context.previousState != GAME) {
            context.menu->getMusic().stop();
            if (context.musicInitialized)
                context.gameMusic.play();
        } else if (context.gameState == MENU && context.previousState == GAME) {
            if (context.musicInitialized)
                context.gameMusic.stop();
            context.menu->getMusic().play();
        }
        context.previousState = context.gameState;
    }
}

void render(GameContext& context)
{
    context.window.clear(sf::Color(50, 50, 50));
    switch (context.gameState) {
        case MENU:
            context.window.setView(context.window.getDefaultView());
            context.menu->display(context.window);
            break;
        case SETTINGS:
            context.window.setView(context.window.getDefaultView());
            context.settings->display(context.window);
            break;
        case GAME:
            if (!context.mazeInitialized) {
                context.menu->getMusic().stop();
                if (context.musicInitialized)
                    context.gameMusic.play();
                if (!context.mapFile.empty())
                    context.gameMaze->create_lab(context.mapFile);
                else
                    context.gameMaze->create_lab();
                context.mazeInitialized = true;
            }
            context.gameMaze->display(context.window);
            break;
        case QUIT_GAME:
            context.window.close();
            break;
    }
    context.window.display();
}

int main(int argc, char **argv)
{
    GameContext context;

    if (!initializeGame(context, argc, argv)) {
        return EXIT_FAILURE;
    }
    while (context.window.isOpen()) {
        processEvents(context);
        render(context);
    }
    return EXIT_SUCCESS;
}
