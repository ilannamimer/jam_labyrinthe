#include "labyrinthe.hpp"

labyrinthe::labyrinthe()
{
    _window.create(sf::VideoMode(1500, 750), "SFML");
    _font.loadFromFile("./arial.ttf");
}

void labyrinthe::create_lab()
{
    int rows = 20;
    int cols = 40;
    float cellSize = 30.0f;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            sf::RectangleShape fly(sf::Vector2f(cellSize, cellSize));
            fly.setPosition(j * cellSize, i * cellSize);
            fly.setFillColor(sf::Color::White);
            fly.setOutlineColor(sf::Color::Black);
            fly.setOutlineThickness(1.0f);
            all_case.push_back(fly);
        }
}

void labyrinthe::create_lab(std::string lab)
{
    std::ifstream file(lab);
    if (!file.is_open())
        return;

    std::string line;
    int row = 0;
    float cellSize = 30.0f;

    while (std::getline(file, line)) {
        for (size_t col = 0; col < line.size(); col++) {
            sf::RectangleShape fly(sf::Vector2f(cellSize, cellSize));
            fly.setPosition(col * cellSize, row * cellSize);

            if (line[col] == '#')
                fly.setFillColor(sf::Color::Yellow); // mur
            else if (line[col] == 'E'){
                fly.setFillColor(sf::Color::Green); // entrée
                fly.setOutlineColor(sf::Color::Black);
                fly.setOutlineThickness(1.0f);
                this->perso = fly;
                continue;
            }
            else if (line[col] == 'S')
                fly.setFillColor(sf::Color::Red);   // sortie
            else
                fly.setFillColor(sf::Color::White); // vide

            fly.setOutlineColor(sf::Color::Black);
            fly.setOutlineThickness(1.0f);
            all_case.push_back(fly);
        }
        row++;
    }
    file.close();
}

void labyrinthe::take_commande()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed)
            switch (_event.key.code) {
                case sf::Keyboard::Up:{
                    perso.setPosition(perso.getPosition().x, perso.getPosition().y - 30.0f);
                    break;
                }
                case sf::Keyboard::Down:{
                    perso.setPosition(perso.getPosition().x, perso.getPosition().y + 30.0f);
                    break;
                }
                case sf::Keyboard::Left:{
                    perso.setPosition(perso.getPosition().x - 30.0f, perso.getPosition().y);
                    break;
                }
                case sf::Keyboard::Right:{
                    perso.setPosition(perso.getPosition().x + 30.0f, perso.getPosition().y);
                    break;
                }
                default: 
                    break;
            }
    }
}

bool labyrinthe::display()
{
    if (!_window.isOpen())
        return false;
    _window.clear();
    for (auto &cell : all_case)
        _window.draw(cell);

    _window.draw(perso);
    _window.display();
    return true;
}
