#include "menu.hpp"
#include <iostream>
#include "resolution.hpp"

Menu::Menu()
    : startButton(nullptr), settingsButton(nullptr), exitButton(nullptr)
{
}

bool Menu::initialize()
{
    if (!backgroundTexture.loadFromFile("assets/menu/menu.png")) {
        std::cerr << "Error: Could not load menu background" << std::endl;
        return false;
    }
    background.setTexture(backgroundTexture);
    try {
        startButton.reset(new Button("assets/menu/start.png",
            sf::Vector2f(960 - 250, 450), sf::Vector2f(500, 150)));
        settingsButton.reset(new Button("assets/menu/setting_button.png",
            sf::Vector2f(10, 20), sf::Vector2f(300, 100)));
        exitButton.reset(new Button("assets/menu/exit.png",
            sf::Vector2f(960 - 250, 650), sf::Vector2f(500, 150)));
    } catch (const std::exception& e) {
        std::cerr << "Error creating buttons: " << e.what() << std::endl;
        return false;
    }
    updateForResolution();
    if (!music.openFromFile("assets/song/menu_song.ogg")) {
        std::cerr << "Warning: Could not load menu music" << std::endl;
    } else {
        music.setLoop(true);
        music.play();
    }
    return true;
}

void Menu::updateForResolution()
{
    const Resolution& res = ResolutionManager::getCurrentResolutionInfo();

    sf::FloatRect bounds = background.getLocalBounds();
    background.setOrigin(bounds.width / 2, bounds.height / 2);
    background.setPosition(ResolutionManager::scaleX(960), ResolutionManager::scaleY(540));
    background.setScale(res.scaleX, res.scaleY);
    
    startButton->updateForResolution();
    settingsButton->updateForResolution();
    exitButton->updateForResolution();
}

void Menu::handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& state)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool mouseClicked = (event.type == sf::Event::MouseButtonPressed &&
                         event.mouseButton.button == sf::Mouse::Left);
    
    startButton->updateState(mousePos, mouseClicked);
    settingsButton->updateState(mousePos, mouseClicked);
    exitButton->updateState(mousePos, mouseClicked);
    
    if (mouseClicked) {
        if (startButton->getState() == CLICKED) {
            state = GAME;
        } else if (settingsButton->getState() == CLICKED) {
            state = SETTINGS;
        } else if (exitButton->getState() == CLICKED) {
            state = QUIT_GAME;
            window.close();
        }
    }
}

void Menu::display(sf::RenderWindow& window)
{
    window.draw(background);
    startButton->draw(window);
    settingsButton->draw(window);
    exitButton->draw(window);
}
