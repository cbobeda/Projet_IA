#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "GOAPEnemy.h"
#include "Pathfinding.h"
#include <vector>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

std::vector<sf::Vector2i> res;
extern Grid grid;
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    Player player(200, 400);
    std::vector<GOAPEnemy> enemies = { GOAPEnemy(100, 100)};
    //Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();
        mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            grid.cells[mousePos.y / 40][mousePos.x / 40].walkable = 0;
        }
        if (res.empty())
        {
            res = Pathfinding::findPath(grid, sf::Vector2i(1,1), sf::Vector2i(5,5));
            
            for (auto path : res)
            {
                grid.cells[path.y][path.x].walkable = 0;
            }
        }*/
        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid,enemy);
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies)
            window.draw(enemy.shape);
        window.display();
    }
    return 0;
}

