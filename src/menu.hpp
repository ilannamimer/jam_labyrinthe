#ifndef MENU_HPP
    #define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include <iostream>
#include "resolution.hpp"
#include "game_state.hpp"

enum ButtonState {
    NORMAL,
    HOVER,
    CLICKED
};

class Button {
private:
    sf::RectangleShape rect;
    sf::Texture texture;
    sf::Vector2f basePosition;
    sf::Vector2f baseSize;
    ButtonState state;

public:
    Button(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& size)
        : basePosition(position), baseSize(size), state(NORMAL)
    {
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Error: Could not load texture " << texturePath << std::endl;
        }
        updateForResolution();
    }
    
    ~Button() = default;

    void updateForResolution() {
        sf::Vector2f scaledPosition = ResolutionManager::scalePosition(basePosition);
        sf::Vector2f scaledSize = ResolutionManager::scaleSize(baseSize);
        rect.setPosition(scaledPosition);
        rect.setSize(scaledSize);
        rect.setTexture(&texture);
        
        if (state == HOVER) {
            rect.setScale(1.05f, 1.05f);
        } else if (state == CLICKED) {
            rect.setScale(0.95f, 0.95f);
        } else {
            rect.setScale(1.0f, 1.0f);
        }
    }
    
    void updateState(const sf::Vector2i& mousePos, bool clicked) {
        ButtonState oldState = state;
        sf::FloatRect bounds = rect.getGlobalBounds();
        
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            if (clicked) {
                state = CLICKED;
            } else {
                state = HOVER;
            }
        } else {
            state = NORMAL;
        }
        
        if (oldState != state) {
            if (state == HOVER) {
                rect.setScale(1.05f, 1.05f);
            } else if (state == CLICKED) {
                rect.setScale(0.95f, 0.95f);
            } else {
                rect.setScale(1.0f, 1.0f);
            }
        }
    }
    void draw(sf::RenderWindow& window) {
        window.draw(rect);
    }
    bool isClicked() const { return state == CLICKED; }
    ButtonState getState() const { return state; }
};

class Menu {
private:
    sf::Sprite background;
    sf::Texture backgroundTexture;
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> settingsButton;
    std::unique_ptr<Button> exitButton;
    sf::Music music;

public:
    Menu();
    ~Menu() = default;

    bool initialize();
    void handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& state);
    void display(sf::RenderWindow& window);
    void updateForResolution();
    sf::Music& getMusic() { return music; }
};

#endif
