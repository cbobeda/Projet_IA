#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "GOAPEnemy.h"
#include "FSMEnemy.hpp"
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);

    
    std::vector<GOAPEnemy> goapEnemies = { GOAPEnemy(100, 100), GOAPEnemy(700, 100) };

    
    std::vector<FSMEnemy> fsmEnemies = { FSMEnemy(sf::Vector2f(100, 100), 150.0f, 20.0f), FSMEnemy(sf::Vector2f(700, 100), 150.0f, 20.0f) };

    Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
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
