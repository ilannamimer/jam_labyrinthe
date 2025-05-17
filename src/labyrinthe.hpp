#ifndef LABYRINTH_H_
    #define LABYRINTH_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <vector>
#include <string>

enum CellType {
    EMPTY,
    WALL,
    ENTRANCE,
    EXIT
};

class labyrinthe
{
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Font _font;
        std::vector<sf::RectangleShape> all_case;
        sf::RectangleShape perso;
        std::vector<std::vector<CellType>> _grid;
        float _cellSize;
        int _rows, _cols;

        bool isValidPosition(float x, float y);
        std::vector<std::string> load_map_file(const std::string& filename);
        void create_lab_from_data(const std::vector<std::string>& mapData);
        
    public:
        labyrinthe();
        ~labyrinthe() = default;

        void create_lab();
        void create_lab(std::string lab);
        bool display();
        void take_commande();
};
#endif