#ifndef FSMENEMY
#define FSMENEMY
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class FSMEnemy {
public:
    sf::Vector2f position;
    float detectionRadius;
    sf::CircleShape circle;
    sf::Vector2f lastPlayerPosition;
    enum State { PATROL, CHASE, SEARCH };
    State currentState;



    FSMEnemy(sf::Vector2f startPos, float radius, float radiusCircle);

    bool detectPlayer(sf::Vector2f playerPos);
    void patrol(Grid& grid);
    void chase(sf::Vector2f playerPos, Grid& grid);
    void update(sf::Vector2f playerPos, float deltaTime, Grid& grid);
    bool isWalkable(float x, float y, Grid& grid);
    void search(sf::Vector2f lastPlayerPos, float deltaTime, Grid& grid);
    
};

#endif
