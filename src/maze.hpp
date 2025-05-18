#ifndef MAZE_H_
    #define MAZE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "resolution.hpp"

enum CellType {
    EMPTY,
    WALL,
    ENTRANCE,
    EXIT
};

class maze
{
    private:
        sf::Event _event;
        sf::Font _font;
        std::vector<sf::RectangleShape> all_case;
        sf::RectangleShape perso;
        std::vector<std::vector<CellType>> _grid;
        sf::Sprite _hors_controle;
        float _baseCellSize;
        float _cellSize;
        int _rows;
        int _cols;
        sf::Keyboard::Key _left;
        sf::Keyboard::Key _rigth;
        sf::Keyboard::Key _up;
        sf::Keyboard::Key _down;

        sf::Clock _timer;

        void change_key(sf::RenderWindow& window);
        bool isValidPosition(float x, float y);
        std::vector<std::string> load_map_file(const std::string& filename);
        void create_lab_from_data(const std::vector<std::string>& mapData);
        void adjust_view(sf::RenderWindow& window);
        void updateForResolution();
        
    public:
        maze();
        ~maze() = default;

        bool win;
        void create_lab();
        void create_lab(std::string lab);
        bool display(sf::RenderWindow& window);
        void take_commande(sf::RenderWindow& window, sf::Event& event);
};
#endif
