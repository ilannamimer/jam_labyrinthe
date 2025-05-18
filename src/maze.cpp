#include "maze.hpp"
#include <iostream>
#include <algorithm>
#include "resolution.hpp"

void maze::loadTextures()
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile("assets/player/hors_cotrole.png")) {
        _hors_controle.setTexture(*texture);
        
        _baseHorsControleSize = sf::Vector2f(texture->getSize().x, texture->getSize().y);
        _baseHorsControlePosition = sf::Vector2f(960 - _baseHorsControleSize.x/2, 540 - _baseHorsControleSize.y/2);
        
        _hors_controle.setOrigin(_baseHorsControleSize.x/2, _baseHorsControleSize.y/2);
    } else {
        std::cerr << "Erreur: Impossible de charger hors_cotrole.png" << std::endl;
    }
    
    if (!_wallTexture.loadFromFile("assets/player/wall.jpg"))
        std::cerr << "Erreur: Impossible de charger mur.jpg" << std::endl;

    if (!_pathTexture.loadFromFile("assets/player/path.jpg"))
        std::cerr << "Erreur: Impossible de charger shemin.jpg" << std::endl;
    
    if (!_enterTexture.loadFromFile("assets/player/enter.jpg"))
        std::cerr << "Erreur: Impossible de charger shemin.jpg" << std::endl;
    
    sf::Texture texDown1, texDown2, texDown3;
    if (texDown1.loadFromFile("assets/player/perso/perso1.png"))
        _playerTextureDown.push_back(texDown1);
    else
        std::cerr << "Erreur: Impossible de charger perso1.png" << std::endl;
    
    if (texDown2.loadFromFile("assets/player/perso/perso2.png"))
        _playerTextureDown.push_back(texDown2);
    else
        std::cerr << "Erreur: Impossible de charger perso2.png" << std::endl;
    
    if (texDown3.loadFromFile("assets/player/perso/perso3.png"))
        _playerTextureDown.push_back(texDown3);
    else
        std::cerr << "Erreur: Impossible de charger perso3.png" << std::endl;
    
    if (!_playerTextureIdle.loadFromFile("assets/player/perso/perso2.png"))
        std::cerr << "Erreur: Impossible de charger perso2.png pour la pose statique" << std::endl;
    
    sf::Texture texUp1, texUp2;
    if (texUp1.loadFromFile("assets/player/perso/perso_avant1.png"))
        _playerTextureUp.push_back(texUp1);
    else
        std::cerr << "Erreur: Impossible de charger perso_avant1.png" << std::endl;
    
    if (texUp2.loadFromFile("assets/player/perso/perso_avant2.png"))
        _playerTextureUp.push_back(texUp2);
    else
        std::cerr << "Erreur: Impossible de charger perso_avant2.png" << std::endl;
    
    sf::Texture texRight1, texRight2, texRight3;
    if (texRight1.loadFromFile("assets/player/perso/perso_droite1.png"))
        _playerTextureRight.push_back(texRight1);
    else
        std::cerr << "Erreur: Impossible de charger perso_droite1.png" << std::endl;
    
    if (texRight2.loadFromFile("assets/player/perso/perso_droite2.png"))
        _playerTextureRight.push_back(texRight2);
    else
        std::cerr << "Erreur: Impossible de charger perso_droite2.png" << std::endl;
    
    if (texRight3.loadFromFile("assets/player/perso/perso_droite3.png"))
        _playerTextureRight.push_back(texRight3);
    else
        std::cerr << "Erreur: Impossible de charger perso_droite3.png" << std::endl;
    
    sf::Texture texLeft1, texLeft2, texLeft3;
    if (texLeft1.loadFromFile("assets/player/perso/perso_gauche1.png"))
        _playerTextureLeft.push_back(texLeft1);
    else
        std::cerr << "Erreur: Impossible de charger perso_gauche1.png" << std::endl;
    
    if (texLeft2.loadFromFile("assets/player/perso/perso_gauche2.png"))
        _playerTextureLeft.push_back(texLeft2);
    else
        std::cerr << "Erreur: Impossible de charger perso_gauche2.png" << std::endl;
    
    if (texLeft3.loadFromFile("assets/player/perso/perso_gauche3.png"))
        _playerTextureLeft.push_back(texLeft3);
    else
        std::cerr << "Erreur: Impossible de charger perso_gauche3.png" << std::endl;

    playerSprite.setTexture(_playerTextureIdle);
    sf::Vector2u textureSize = _playerTextureIdle.getSize();
    playerSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
}
maze::maze() : _baseHorsControlePosition(960, 540), 
               _baseHorsControleSize(500, 500), 
               _baseCellSize(30.0f), currentDirection(IDLE), currentFrame(0), isMoving(false)
{
    if (!_font.loadFromFile("./assets/font/arial.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police arial.ttf" << std::endl;
        if (!_font.loadFromFile("arial.ttf")) {
            std::cerr << "Erreur: Impossible de charger la police de secours" << std::endl;
        }
    }
    updateForResolution();
    _up = sf::Keyboard::Up;
    _down = sf::Keyboard::Down;
    _rigth = sf::Keyboard::Right;
    _left = sf::Keyboard::Left;
    _timer.restart();
    
    loadTextures();
    
    animationClock.restart();
    idleClock.restart();
    win = false;
}

void maze::updateAnimation()
{
    if (!isMoving && idleClock.getElapsedTime().asMilliseconds() > 500) {
        playerSprite.setTexture(_playerTextureIdle);
        currentDirection = IDLE;
        return;
    }
    
    if (isMoving && animationClock.getElapsedTime().asMilliseconds() > 200) {
        animationClock.restart();
        
        std::vector<sf::Texture>* currentTextures = nullptr;
        
        switch (currentDirection) {
            case DOWN:
                currentTextures = &_playerTextureDown;
                break;
            case RIGHT:
                currentTextures = &_playerTextureRight;
                break;
            case LEFT:
                currentTextures = &_playerTextureLeft;
                break;
            case UP:
                currentTextures = &_playerTextureUp;
                break;
            case IDLE:
                playerSprite.setTexture(_playerTextureIdle);
                return;
        }
        
        if (currentTextures && !currentTextures->empty()) {
            currentFrame = (currentFrame + 1) % currentTextures->size();
            playerSprite.setTexture((*currentTextures)[currentFrame]);
        }
    }
    
    isMoving = false;
}

void maze::updateForResolution()
{
    _cellSize = ResolutionManager::scaleY(_baseCellSize);
    sf::Vector2f scaledPosition = ResolutionManager::scalePosition(_baseHorsControlePosition);
    float scaleFactorX = ResolutionManager::scaleX(1.0f);
    float scaleFactorY = ResolutionManager::scaleY(1.0f);
    _hors_controle.setPosition(scaledPosition);
    _hors_controle.setScale(scaleFactorX, scaleFactorY);
    int col;
    int row;

    if (!all_case.empty()) {
        all_case.clear();
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                sf::Sprite fly;
                fly.setPosition(j * _cellSize, i * _cellSize);

                switch (_grid[i][j]) {
                    case WALL:
                        fly.setTexture(_wallTexture);
                        fly.setScale(_cellSize / _wallTexture.getSize().x, _cellSize / _wallTexture.getSize().y);
                        break;
                    case ENTRANCE:
                        fly.setTexture(_enterTexture);
                        fly.setScale(_cellSize / _enterTexture.getSize().x, _cellSize / _enterTexture.getSize().y);
                        break;
                    case EXIT:
                        fly.setTexture(_enterTexture);
                        fly.setScale(_cellSize / _enterTexture.getSize().x, _cellSize / _enterTexture.getSize().y);
                        break;
                    default:
                        fly.setTexture(_pathTexture);
                        fly.setScale(_cellSize / _pathTexture.getSize().x, _cellSize / _pathTexture.getSize().y);
                        break;
                }

                all_case.push_back(fly);
            }
        }
        perso.setSize(sf::Vector2f(_cellSize * 0.8f, _cellSize * 0.8f));
        col = static_cast<int>((perso.getPosition().x + perso.getSize().x / 2) / (_cellSize / 0.8f));
        row = static_cast<int>((perso.getPosition().y + perso.getSize().y / 2) / (_cellSize / 0.8f));
        perso.setPosition(
            col * _cellSize + (_cellSize - perso.getSize().x) / 2,
            row * _cellSize + (_cellSize - perso.getSize().y) / 2
        );
        playerSprite.setPosition(
            col * _cellSize + _cellSize / 2,
            row * _cellSize + _cellSize / 2
        );
        playerSprite.setScale(
            _cellSize / 32.0f * 0.8f,
            _cellSize / 32.0f * 0.8f
        );
    }
}

void maze::create_lab()
{
    _rows = 20;
    _cols = 40;
    _grid.resize(_rows, std::vector<CellType>(_cols, EMPTY));

    all_case.clear();
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            sf::Sprite fly;
            fly.setPosition(j * _cellSize, i * _cellSize);
            fly.setScale(_cellSize / _wallTexture.getSize().x, _cellSize / _wallTexture.getSize().y);
            if (i == 0 || j == 0 || i == _rows-1 || j == _cols-1) {
                fly.setTexture(_wallTexture);
                _grid[i][j] = WALL;
            } else {
                fly.setTexture(_pathTexture);
                _grid[i][j] = EMPTY;
            }
            all_case.push_back(fly);
        }
    }
    perso = sf::RectangleShape(sf::Vector2f(_cellSize * 0.8f, _cellSize * 0.8f));
    perso.setPosition(_cellSize + (_cellSize - perso.getSize().x) / 2,
    _cellSize + (_cellSize - perso.getSize().y) / 2);
    perso.setFillColor(sf::Color::Blue);
    playerSprite.setPosition(
        _cellSize + _cellSize / 2, 
        _cellSize + _cellSize / 2
    );
    playerSprite.setScale(
        _cellSize / 32.0f * 0.8f,
        _cellSize / 32.0f * 0.8f
    );
}

std::vector<std::string> maze::load_map_file(const std::string& filename)
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

void maze::create_lab_from_data(const std::vector<std::string>& mapData)
{
    _rows = mapData.size();
    _cols = 0;
    char cell;
    int row = 0;

    for (const auto& l : mapData)
        _cols = std::max(_cols, (int)l.size());
    _grid.resize(_rows, std::vector<CellType>(_cols, EMPTY));
    all_case.clear();
    for (const auto& line : mapData) {
        for (size_t col = 0; col < line.size(); col++) {
            sf::Sprite fly;
            fly.setPosition(col * _cellSize, row * _cellSize);

            cell = line[col];
            if (cell == '#') {
                fly.setTexture(_wallTexture);
                _grid[row][col] = WALL;
            } else if (cell == 'E') {
                fly.setTexture(_enterTexture);
                _grid[row][col] = ENTRANCE;
                perso = sf::RectangleShape(sf::Vector2f(_cellSize * 0.8f, _cellSize * 0.8f));
                perso.setPosition(col * _cellSize + (_cellSize - perso.getSize().x) / 2,
                row * _cellSize + (_cellSize - perso.getSize().y) / 2);
                perso.setFillColor(sf::Color::Blue);
                playerSprite.setPosition(
                    col * _cellSize + _cellSize / 2,
                    row * _cellSize + _cellSize / 2
                );
                playerSprite.setScale(
                    _cellSize / 32.0f * 0.8f,
                    _cellSize / 32.0f * 0.8f
                );
                all_case.push_back(fly);
                continue;
            } else if (cell == 'S') {
                fly.setTexture(_enterTexture);
                _grid[row][col] = EXIT;
            } else {
                fly.setTexture(_pathTexture);
                _grid[row][col] = EMPTY;
            }
            all_case.push_back(fly);
        }
        row++;
    }
}

void maze::adjust_view(sf::RenderWindow& window)
{
    sf::View view;
    float totalWidth = _cols * _cellSize;
    float totalHeight = _rows * _cellSize;
    float zoomX;
    float zoomY;
    float zoom;

    zoomX = window.getSize().x / totalWidth;
    zoomY = window.getSize().y / totalHeight;
    zoom = std::min(zoomX, zoomY);
    view.setSize(window.getSize().x / zoom, window.getSize().y / zoom);
    view.setCenter(totalWidth / 2, totalHeight / 2);
    window.setView(view);
}

void maze::create_lab(std::string lab)
{
    std::vector<std::string> mapData = load_map_file(lab);

    if (mapData.empty()) {
        create_lab();
        return;
    }
    create_lab_from_data(mapData);
}

void maze::change_key(sf::RenderWindow& window)
{
    std::vector<sf::Keyboard::Key> all_keys = {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right};

    _rigth = sf::Keyboard::Unknown;
    _left = sf::Keyboard::Unknown;
    _up = sf::Keyboard::Unknown;
    _down = sf::Keyboard::Unknown;

    sf::View currentView = window.getView();
    window.setView(window.getDefaultView());
    window.draw(_hors_controle);
    window.setView(currentView);
    if (_timer.getElapsedTime().asSeconds() >= 10.0f){

        _rigth = all_keys[rand() % 4];

        _left = all_keys[rand() % 4];
        while (_left == _rigth)
            _left = all_keys[rand() % 4];

        _up = all_keys[rand() % 4];
        while (_up == _left || _up == _rigth)
            _up = all_keys[rand() % 4];

        _down = all_keys[rand() % 4];
        while (_down == _up || _down == _left || _down == _rigth)
            _down = all_keys[rand() % 4];
        _timer.restart();
    }
}

bool maze::isValidPosition(float x, float y)
{
    int col = static_cast<int>(x / _cellSize);
    int row = static_cast<int>(y / _cellSize);

    if (row < 0 || row >= _rows || col < 0 || col >= _cols)
        return false;
    return _grid[row][col] != WALL;
}

void maze::take_commande(sf::RenderWindow& window, sf::Event& event)
{
    int col;
    int row;
    float currentX;
    float currentY;
    float newX;
    float newY;
    bool moved = false;

    (void)window;
    if (event.type == sf::Event::KeyPressed) {
        currentX = perso.getPosition().x;
        currentY = perso.getPosition().y;
        newX = currentX;
        newY = currentY;
        if (_up == event.key.code) {
            newY -= _cellSize;
            currentDirection = UP;
            moved = true;
        }
        if (_down == event.key.code) {
            newY += _cellSize;
            currentDirection = DOWN;
            moved = true;
        }
        if (_left == event.key.code) {
            newX -= _cellSize;
            currentDirection = LEFT;
            moved = true;
        }
        if (_rigth == event.key.code) {
            newX += _cellSize;
            currentDirection = RIGHT;
            moved = true;
        }
        if (isValidPosition(newX + perso.getSize().x/2, newY + perso.getSize().y/2)) {
            perso.setPosition(newX, newY);
            playerSprite.setPosition(newX + perso.getSize().x/2, newY + perso.getSize().y/2);
            col = static_cast<int>((newX + perso.getSize().x/2) / _cellSize);
            row = static_cast<int>((newY + perso.getSize().y/2) / _cellSize);
            if (moved) {
                isMoving = true;
                animationClock.restart();
                idleClock.restart();
                currentFrame = (currentFrame + 1) % 3;
                if (currentDirection == DOWN && !_playerTextureDown.empty())
                    playerSprite.setTexture(_playerTextureDown[currentFrame % _playerTextureDown.size()]);
                else if (currentDirection == UP && !_playerTextureUp.empty())
                    playerSprite.setTexture(_playerTextureUp[currentFrame % _playerTextureUp.size()]);
                else if (currentDirection == LEFT && !_playerTextureLeft.empty())
                    playerSprite.setTexture(_playerTextureLeft[currentFrame % _playerTextureLeft.size()]);
                else if (currentDirection == RIGHT && !_playerTextureRight.empty())
                    playerSprite.setTexture(_playerTextureRight[currentFrame % _playerTextureRight.size()]);
            }
            if (row >= 0 && row < _rows && col >= 0 && col < _cols && _grid[row][col] == EXIT)
                win = true;
            else win = false;
        }
    }
}

bool maze::display(sf::RenderWindow& window)
{
    adjust_view(window);
    window.clear(sf::Color(50, 50, 50));
    for (auto &cell : all_case)
        window.draw(cell);
    updateAnimation();
    window.draw(playerSprite);
    if (_timer.getElapsedTime().asSeconds() >= 8.0f)
        change_key(window);
    return true;
}
