#ifndef RESOLUTION_HPP
    #define RESOLUTION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

enum ResolutionPreset {
    RES_1920x1080,
    RES_960x540,
    RES_COUNT
};

struct Resolution {
    unsigned int width;
    unsigned int height;
    float scaleX;
    float scaleY;

    Resolution(unsigned int w, unsigned int h) : width(w), height(h) {
        scaleX = static_cast<float>(w) / 1920.0f;
        scaleY = static_cast<float>(h) / 1080.0f;
    }
};

class ResolutionManager {
private:
    static ResolutionPreset currentResolution;
    static std::vector<Resolution> availableResolutions;
    
public:
    static void initialize() {
        if (availableResolutions.empty()) {
            availableResolutions.push_back(Resolution(1920, 1080));
            availableResolutions.push_back(Resolution(960, 540));
        }
        currentResolution = RES_1920x1080;
    }
    static ResolutionPreset getCurrentResolution() {
        return currentResolution;
    }
    static void setCurrentResolution(ResolutionPreset preset) {
        if (preset < RES_COUNT) {
            currentResolution = preset;
        }
    }
    static const Resolution& getResolution(ResolutionPreset preset) {
        if (preset < RES_COUNT) {
            return availableResolutions[preset];
        }
        return availableResolutions[0];
    }
    static const Resolution& getCurrentResolutionInfo() {
        return availableResolutions[currentResolution];
    }
    static sf::Vector2f scalePosition(const sf::Vector2f& position) {
        const Resolution& res = getCurrentResolutionInfo();
        return sf::Vector2f(position.x * res.scaleX, position.y * res.scaleY);
    }
    static sf::Vector2f scaleSize(const sf::Vector2f& size) {
        const Resolution& res = getCurrentResolutionInfo();
        return sf::Vector2f(size.x * res.scaleX, size.y * res.scaleY);
    }
    static float scaleX(float x) {
        return x * getCurrentResolutionInfo().scaleX;
    }
    static float scaleY(float y) {
        return y * getCurrentResolutionInfo().scaleY;
    }
    static sf::Vector2f unscalePosition(const sf::Vector2f& scaledPosition) {
        const Resolution& res = getCurrentResolutionInfo();
        return sf::Vector2f(scaledPosition.x / res.scaleX, scaledPosition.y / res.scaleY);
    }
};

#endif
