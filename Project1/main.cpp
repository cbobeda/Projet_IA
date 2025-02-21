#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "GOAPEnemy.h"
#include "Pathfinding.h"
#include "FSMEnemy.hpp"
#include "BehaviourTreeSetup.hpp"
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
Blackboard blackboard;
int currentWaypoint = 0;
BTNode* behaviourTree;


std::mutex mtx;

std::vector<sf::Vector2i> res;
extern Grid grid;

void updateGame(float& deltaTime, Player& player, std::vector<GOAPEnemy>& goapEnemies, std::vector<FSMEnemy>& fsmEnemies, sf::RectangleShape& enemyShape)
{

    std::scoped_lock lock(mtx); 
    for (auto& enemy : goapEnemies) {
        enemy.update(deltaTime, grid, enemy,sf::Vector2i(player.getPosition().x / 40 , player.getPosition().y / 40));
        if (std::abs(enemy.shape.getPosition().x - player.shape.getPosition().x) < 300 && std::abs(enemy.shape.getPosition().y - player.shape.getPosition().y) < 300 )
        {
            enemy.agent.state.playerInSight = true;
        }
        else
        {
            enemy.agent.state.playerInSight = false;
        }
        if (std::abs(enemy.shape.getPosition().x - player.shape.getPosition().x) < 70 && std::abs(enemy.shape.getPosition().y - player.shape.getPosition().y) < 70 )
        {
            enemy.agent.state.playerInRange = true;
        }
        else
        {
            enemy.agent.state.playerInRange = false;
        }
        if (enemy.agent.state.health < 40)
        {
            enemy.agent.state.lowHealth = true;
        }
    }

        
    for (auto& enemy : fsmEnemies) {
        enemy.update(player.getPosition(), deltaTime);
    }

    blackboard.SetValue("player_x", static_cast<int>(player.getPosition().x));
    blackboard.SetValue("player_y", static_cast<int>(player.getPosition().y));

    NodeState state = behaviourTree->execute();

    enemyShape.setPosition(
        static_cast<float>(blackboard.GetValue("enemy_x")),
        static_cast<float>(blackboard.GetValue("enemy_y"))
    );
}
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    Player player(200, 400);
    //Grid grid;
    sf::RectangleShape enemyShape(sf::Vector2f(20.0f, 20.0f));
    enemyShape.setFillColor(sf::Color::Green);

    blackboard.SetValue("enemy_x", 300);
    blackboard.SetValue("enemy_y", 300);


    std::vector<GOAPEnemy> goapEnemies = { GOAPEnemy(100, 100)};

    
    std::vector<FSMEnemy> fsmEnemies = { FSMEnemy(sf::Vector2f(100, 100), 150.0f, 20.0f), FSMEnemy(sf::Vector2f(200, 100), 150.0f, 20.0f) };

    BehaviourTreeSetup::setup(behaviourTree, blackboard, currentWaypoint);


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

        std::thread updateThread = std::thread(updateGame,std::ref(deltaTime),std::ref(player), std::ref(goapEnemies), std::ref(fsmEnemies), std::ref(enemyShape));
        
        

        window.clear();

        
        grid.draw(window);

       
        window.draw(player.shape);

        for (const auto& enemy : goapEnemies) {
            window.draw(enemy.shape);
        }

      
        for (const auto& enemy : fsmEnemies) {
            window.draw(enemy.circle);  
        }

        window.draw(enemyShape);

        window.display();
        updateThread.join();
    }
    

    delete behaviourTree;
    return 0;
}
