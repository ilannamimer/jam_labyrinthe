#ifndef SETTINGS_HPP
    #define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "menu.hpp"
#include "resolution.hpp"

class VolumeControl {
private:
    sf::RectangleShape bar;
    sf::CircleShape knob;
    sf::Vector2f baseBarPosition;
    float baseBarWidth;
    float level;
    bool dragging;

public:
    VolumeControl();
    ~VolumeControl() = default;

    bool initialize();
    void update(sf::Music& music, float newVolume);
    void handleInteraction(sf::Music& music, const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window);
    void updateForResolution();

    bool isDragging() const { return dragging; }
    void setDragging(bool drag) { dragging = drag; }
};

class Settings {
private:
    sf::Sprite background;
    sf::Texture backgroundTexture;
    std::unique_ptr<Button> resolution1Button;
    std::unique_ptr<Button> resolution2Button;
    VolumeControl volumeControl;
    sf::Music* musicRef;

public:
    Settings(sf::Music& menuMusic);
    ~Settings() = default;

    bool initialize();
    void handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& state, bool& resolutionChanged);
    void display(sf::RenderWindow& window);
    void setResolution(sf::RenderWindow& window, ResolutionPreset preset);
    void updateForResolution();

    void handleMouseButtonRelease(sf::Event& event);
    void updateButtonStates(const sf::Vector2i& mousePos);
};

#endif