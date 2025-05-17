#include "labyrinthe.hpp"
#include <iostream>

labyrinthe::labyrinthe() : _cellSize(30.0f)
{
    _window.create(sf::VideoMode(1500, 750), "LABYRINTH");
    if (!_font.loadFromFile("./assets/font/arial.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police arial.ttf" << std::endl;
        if (!_font.loadFromFile("arial.ttf")) {
            std::cerr << "Erreur: Impossible de charger la police de secours" << std::endl;
        }
    }
}

void labyrinthe::create_lab()
{
    _rows = 20;
    _cols = 40;
    _grid.resize(_rows, std::vector<CellType>(_cols, EMPTY));

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            sf::RectangleShape fly(sf::Vector2f(_cellSize, _cellSize));
            fly.setPosition(j * _cellSize, i * _cellSize);
            if (i == 0 || j == 0 || i == _rows-1 || j == _cols-1) {
                fly.setFillColor(sf::Color::Yellow);
                _grid[i][j] = WALL;
            } else {
                fly.setFillColor(sf::Color::White);
                _grid[i][j] = EMPTY;
            }
            fly.setOutlineColor(sf::Color::Black);
            fly.setOutlineThickness(1.0f);
            all_case.push_back(fly);
        }
    }
    perso = sf::RectangleShape(sf::Vector2f(_cellSize * 0.8f, _cellSize * 0.8f));
    perso.setPosition(_cellSize + (_cellSize - perso.getSize().x) / 2,
    _cellSize + (_cellSize - perso.getSize().y) / 2);
    perso.setFillColor(sf::Color::Blue);
}

std::vector<std::string> labyrinthe::load_map_file(const std::string& filename)
{
    std::vector<std::string> mapData;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        return mapData;
    }
    std::string line;
    while (std::getline(file, line))
        mapData.push_back(line);
    file.close();
    if (mapData.empty())
        std::cerr << "Erreur: Fichier vide" << std::endl;
    return mapData;
}

void labyrinthe::create_lab_from_data(const std::vector<std::string>& mapData)
{
    char cell;
    int row = 0;
    _rows = mapData.size();
    _cols = 0;

    for (const auto& l : mapData)
        _cols = std::max(_cols, (int)l.size());
    _grid.resize(_rows, std::vector<CellType>(_cols, EMPTY));
    all_case.clear();
    for (const auto& line : mapData) {
        for (size_t col = 0; col < line.size(); col++) {
            sf::RectangleShape fly(sf::Vector2f(_cellSize, _cellSize));
            fly.setPosition(col * _cellSize, row * _cellSize);
            cell = line[col];
            if (cell == '#') {
                fly.setFillColor(sf::Color::Yellow);
                _grid[row][col] = WALL;
            } else if (cell == 'E') {
                fly.setFillColor(sf::Color::Green);
                _grid[row][col] = ENTRANCE;
                perso = sf::RectangleShape(sf::Vector2f(_cellSize * 0.8f, _cellSize * 0.8f));
                perso.setPosition(col * _cellSize + (_cellSize - perso.getSize().x) / 2,
                row * _cellSize + (_cellSize - perso.getSize().y) / 2);
                perso.setFillColor(sf::Color::Blue);
                all_case.push_back(fly);
                continue;
            } else if (cell == 'S') {
                fly.setFillColor(sf::Color::Red);
                _grid[row][col] = EXIT;
            } else {
                fly.setFillColor(sf::Color::White);
                _grid[row][col] = EMPTY;
            }
            fly.setOutlineColor(sf::Color::Black);
            fly.setOutlineThickness(1.0f);
            all_case.push_back(fly);
        }
        row++;
    }
}

void labyrinthe::create_lab(std::string lab)
{
    std::vector<std::string> mapData = load_map_file(lab);

    if (mapData.empty()) {
        create_lab();
        return;
    }
    create_lab_from_data(mapData);
}

bool labyrinthe::isValidPosition(float x, float y)
{
    int col = static_cast<int>(x / _cellSize);
    int row = static_cast<int>(y / _cellSize);

    if (row < 0 || row >= _rows || col < 0 || col >= _cols)
        return false;
    return _grid[row][col] != WALL;
}

void labyrinthe::take_commande()
{
    int col;
    int row;
    float currentX;
    float currentY;
    float newX;
    float newY;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed) {
            currentX = perso.getPosition().x;
            currentY = perso.getPosition().y;
            newX = currentX;
            newY = currentY;
            switch (_event.key.code) {
                case sf::Keyboard::Up:
                    newY -= _cellSize;
                    break;
                case sf::Keyboard::Down:
                    newY += _cellSize;
                    break;
                case sf::Keyboard::Left:
                    newX -= _cellSize;
                    break;
                case sf::Keyboard::Right:
                    newX += _cellSize;
                    break;
                default:
                    break;
            }
            if (isValidPosition(newX + perso.getSize().x/2, newY + perso.getSize().y/2)) {
                perso.setPosition(newX, newY);
                col = static_cast<int>((newX + perso.getSize().x/2) / _cellSize);
                row = static_cast<int>((newY + perso.getSize().y/2) / _cellSize);
                if (row >= 0 && row < _rows && col >= 0 && col < _cols && _grid[row][col] == EXIT)
                    std::cout << "Bravo ! Vous avez atteint la sortie !" << std::endl;
            }
        }
    }
}

bool labyrinthe::display()
{
    if (!_window.isOpen())
        return false;
    _window.clear(sf::Color(50, 50, 50));
    for (auto &cell : all_case)
        _window.draw(cell);
    _window.draw(perso);
    _window.display();
    return true;
}
