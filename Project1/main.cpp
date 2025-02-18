#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "GOAPEnemy.h"
#include "Pathfinding.h"
#include "FSMEnemy.hpp"
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
    //Grid grid;

    
    std::vector<GOAPEnemy> goapEnemies = { GOAPEnemy(100, 100)};

    
    std::vector<FSMEnemy> fsmEnemies = { FSMEnemy(sf::Vector2f(100, 100), 150.0f, 20.0f), FSMEnemy(sf::Vector2f(700, 100), 150.0f, 20.0f) };


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

        
        for (auto& enemy : goapEnemies) {
            enemy.update(deltaTime, grid, enemy);
        }

        
        for (auto& enemy : fsmEnemies) {
            enemy.update(player.getPosition(), deltaTime);
        }

        window.clear();

        
        grid.draw(window);

       
        window.draw(player.shape);

        for (const auto& enemy : goapEnemies) {
            window.draw(enemy.shape);
        }

      
        for (const auto& enemy : fsmEnemies) {
            window.draw(enemy.circle);  
        }

        window.display();
    }

    return 0;
}
