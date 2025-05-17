#ifndef LABYRINTH_H_
    #define LABYRINTH_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>

class labyrinthe
{
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Font _font;
        std::vector<sf::RectangleShape> all_case;
        sf::RectangleShape perso;
    public:
        labyrinthe();
        ~labyrinthe() = default;

        void create_lab();
        void create_lab(std::string lab);
        bool display();
        void take_commande();
};
#endif