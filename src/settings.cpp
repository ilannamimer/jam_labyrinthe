#include "settings.hpp"
#include <iostream>
#include "resolution.hpp"

VolumeControl::VolumeControl()
    : baseBarPosition(650, 700), baseBarWidth(600.0f), level(1.0f), dragging(false)
{
}

bool VolumeControl::initialize()
{
    updateForResolution();
    return true;
}

void VolumeControl::updateForResolution()
{
    sf::Vector2f scaledPosition = ResolutionManager::scalePosition(baseBarPosition);
    float scaledWidth = ResolutionManager::scaleX(baseBarWidth);
    float scaledHeight = ResolutionManager::scaleY(20);
    float scaledKnobRadius;
    float xPos;

    bar.setSize(sf::Vector2f(scaledWidth, scaledHeight));
    bar.setPosition(scaledPosition);
    bar.setFillColor(sf::Color(200, 200, 160, 255));
    scaledKnobRadius = ResolutionManager::scaleY(20);
    knob.setRadius(scaledKnobRadius);
    knob.setFillColor(sf::Color(180, 140, 100, 255));
    xPos = scaledPosition.x + level * scaledWidth;
    knob.setPosition(sf::Vector2f(xPos - scaledKnobRadius, scaledPosition.y - scaledKnobRadius/2));
}

void VolumeControl::update(sf::Music& music, float newVolume)
{
    float scaledWidth;
    float scaledKnobRadius;
    float xPos;

    if (newVolume < 0.0f)
        newVolume = 0.0f;
    else if (newVolume > 1.0f)
        newVolume = 1.0f;
    level = newVolume;
    sf::Vector2f scaledPosition = ResolutionManager::scalePosition(baseBarPosition);
    scaledWidth = ResolutionManager::scaleX(baseBarWidth);
    scaledKnobRadius = ResolutionManager::scaleY(20);
    xPos = scaledPosition.x + level * scaledWidth;
    knob.setPosition(sf::Vector2f(xPos - scaledKnobRadius, scaledPosition.y - scaledKnobRadius/2));
    music.setVolume(level * 100);
}

void VolumeControl::handleInteraction(sf::Music& music, const sf::Vector2i& mousePos)
{
    sf::Vector2f scaledPosition = ResolutionManager::scalePosition(baseBarPosition);
    float scaledWidth = ResolutionManager::scaleX(baseBarWidth);
    float scaledKnobRadius = ResolutionManager::scaleY(20);
    float minX = scaledPosition.x;
    float maxX = minX + scaledWidth;
    float minY = scaledPosition.y - scaledKnobRadius;
    float maxY = scaledPosition.y + scaledKnobRadius;
    float newVolume;
    
    if (dragging || 
        (mousePos.y >= minY && mousePos.y <= maxY && 
         mousePos.x >= minX && mousePos.x <= maxX)) {
        newVolume = (float)(mousePos.x - minX) / scaledWidth;
        update(music, newVolume);
    }
}

void VolumeControl::draw(sf::RenderWindow& window)
{
    window.draw(bar);
    window.draw(knob);
}

Settings::Settings(sf::Music& menuMusic)
    : resolution1Button(nullptr), resolution2Button(nullptr), musicRef(&menuMusic)
{
}

bool Settings::initialize(void)
{
    if (!backgroundTexture.loadFromFile("assets/menu/settings.png")) {
        std::cerr << "Error: Could not load settings background" << std::endl;
        return false;
    }
    background.setTexture(backgroundTexture);
    try {
        resolution1Button.reset(new Button("assets/menu/1920x1080button.png",
            sf::Vector2f(480, 380), sf::Vector2f(450, 120)));
        resolution2Button.reset(new Button("assets/menu/950x540button.png",
            sf::Vector2f(1000, 380), sf::Vector2f(450, 120)));
    } catch (const std::exception& e) {
        std::cerr << "Error creating resolution buttons: " << e.what() << std::endl;
        return false;
    }
    updateForResolution();
    if (!volumeControl.initialize()) {
        std::cerr << "Error initializing volume control" << std::endl;
        return false;
    }
    return true;
}

void Settings::updateForResolution()
{
    const Resolution& res = ResolutionManager::getCurrentResolutionInfo();

    sf::FloatRect bounds = background.getLocalBounds();
    background.setOrigin(bounds.width / 2, bounds.height / 2);
    background.setPosition(res.width / 2, res.height / 2);
    background.setScale(res.scaleX, res.scaleY);
    resolution1Button->updateForResolution();
    resolution2Button->updateForResolution();
    volumeControl.updateForResolution();
}

void Settings::handleEvents(sf::RenderWindow& window, sf::Event& event, GameState& state, bool& resolutionChanged)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::Closed) {
        window.close();
        state = QUIT_GAME;
        return;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        state = MENU;
        return;
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        volumeControl.setDragging(true);
        volumeControl.handleInteraction(*musicRef, mousePos);
        resolution1Button->updateState(mousePos, true);
        resolution2Button->updateState(mousePos, true);
        if (resolution1Button->getState() == CLICKED) {
            setResolution(window, RES_1920x1080);
            resolutionChanged = true;
            state = SETTINGS;
        } else if (resolution2Button->getState() == CLICKED) {
            setResolution(window, RES_960x540);
            resolutionChanged = true;
            state = SETTINGS;
        }
    }
    handleMouseButtonRelease(event);
    if (volumeControl.isDragging())
        volumeControl.handleInteraction(*musicRef, mousePos);
    updateButtonStates(mousePos);
}

void Settings::handleMouseButtonRelease(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Left)
        volumeControl.setDragging(false);
}

void Settings::updateButtonStates(const sf::Vector2i& mousePos)
{
    resolution1Button->updateState(mousePos, false);
    resolution2Button->updateState(mousePos, false);
}

void Settings::setResolution(sf::RenderWindow& window, ResolutionPreset preset)
{
    const Resolution& newRes = ResolutionManager::getResolution(preset);
    sf::Vector2i oldPosition = window.getPosition();
    (void)oldPosition;
    ResolutionManager::setCurrentResolution(preset);
    window.close();
    window.create(sf::VideoMode(newRes.width, newRes.height),
    "MAZE RUNNER: SHIFT CONTROL", sf::Style::Resize | sf::Style::Close);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(
        (desktop.width - newRes.width) / 2,
        (desktop.height - newRes.height) / 2
    ));
    window.setView(window.getDefaultView());
    updateForResolution();
}

void Settings::display(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);
    window.draw(background);
    resolution1Button->draw(window);
    resolution2Button->draw(window);
    volumeControl.draw(window);
    window.display();
}
