#include "game_context.hpp"
#include "menu.hpp"
#include "maze.hpp"
#include "settings.hpp"

bool GameContext::initializeGame(int argc, char **argv)
{
    ResolutionManager::initialize();
    const Resolution& initialRes = ResolutionManager::getCurrentResolutionInfo();

    window.create(sf::VideoMode(initialRes.width, initialRes.height),
    "MAZE RUNNER: SHIFT CONTROL", sf::Style::Resize | sf::Style::Close);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(
        (desktop.width - initialRes.width) / 2,
        (desktop.height - initialRes.height) / 2
    ));
    if (argc == 2)
        mapFile = argv[1];
    menu = new Menu();
    if (!menu->initialize()) {
        std::cerr << "Failed to initialize menu" << std::endl;
        return false;
    }
    settings = new Settings(menu->getMusic());
    if (!settings->initialize()) {
        std::cerr << "Failed to initialize settings" << std::endl;
        return false;
    }
    if (!gameMusic.openFromFile("assets/song/game_song.ogg")) {
        std::cerr << "Warning: Could not load game music" << std::endl;
    } else {
        gameMusic.setLoop(true);
        musicInitialized = true;
    }
    return true;
}

void GameContext::processEvents()
{
    sf::Event event;
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        switch (gameState) {
            case MENU:
                menu->handleEvents(window, event, gameState);
                break;
            case SETTINGS:
                settings->handleEvents(window, event, gameState, resolutionChanged);
                break;
            case GAME:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    previousState = gameState;
                    gameState = MENU;
                    if (musicInitialized) {
                        gameMusic.stop();
                        menu->getMusic().play();
                    }
                }
                gameMaze->take_commande(window, event);
                break;
            default:
                break;
        }
    }
    if (resolutionChanged) {
        menu->updateForResolution();
        resolutionChanged = false;
    }
    if (previousState != gameState) {
        if (gameState == GAME && previousState == MENU) {
            if (!mazeInitialized) {
                gameMaze = new maze();
                if (!mapFile.empty())
                    gameMaze->create_lab(mapFile);
                else
                    gameMaze->create_lab();
                mazeInitialized = true;
            }

            menu->getMusic().stop();
            if (musicInitialized)
                gameMusic.play();

        } else if (gameState == MENU && previousState == GAME) {
            if (musicInitialized)
                gameMusic.stop();
            menu->getMusic().play();
        }

        previousState = gameState;
    }
}

void GameContext::render()
{
    window.clear(sf::Color(50, 50, 50));
    switch (gameState) {
        case MENU:
            window.setView(window.getDefaultView());
            menu->display(window);
            break;
        case SETTINGS:
            window.setView(window.getDefaultView());
            settings->display(window);
            break;
        case GAME:
            if (!mazeInitialized) {
                menu->getMusic().stop();
                if (musicInitialized)
                    gameMusic.play();
                if (!mapFile.empty())
                    gameMaze->create_lab(mapFile);
                else
                    gameMaze->create_lab();
                mazeInitialized = true;
            }
            gameMaze->display(window);
            if (gameMaze->win){
                menu->win = true;
                gameState = MENU;
            }
            break;
        case QUIT_GAME:
            window.close();
            break;
    }
    window.display();
}

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
