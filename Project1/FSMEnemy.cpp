#include "FSMEnemy.hpp"

FSMEnemy::FSMEnemy(sf::Vector2f startPos, float radiusDetect, float radiusCircle) {
    circle.setRadius(radiusCircle);
    circle.setPosition(startPos);
    circle.setFillColor(sf::Color::Red);
    position = startPos;
    detectionRadius = radiusDetect;
    currentState = PATROL;
}

bool FSMEnemy::detectPlayer(sf::Vector2f playerPos) {

    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return (distance < detectionRadius);
}

void FSMEnemy::patrol() {
    static int currentWaypoint = 0;
    static sf::Vector2f waypoints[4] = { sf::Vector2f(100, 300), sf::Vector2f(500, 100), sf::Vector2f(100, 300), sf::Vector2f(500, 300) };
    sf::Vector2f target = waypoints[currentWaypoint];
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 4;
    }
    else {
        direction /= distance;
        position += direction * 0.2f;
    }
    circle.setPosition(position);
}

void FSMEnemy::chase(sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.2f;
    }

    circle.setPosition(position);
}

void FSMEnemy::search(sf::Vector2f lastPlayerPos, float deltaTime) {
    static float searchTimer = 0.0f;
    static sf::Vector2f searchDirection;

    if (searchTimer == 0.0f) {
        searchDirection = sf::Vector2f(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
        searchDirection /= std::sqrt(searchDirection.x * searchDirection.x + searchDirection.y * searchDirection.y);
    }

    searchTimer += deltaTime;
    if (searchTimer < 10.0f) {
        position += searchDirection * 5.f * deltaTime;
    }
    else {
        searchTimer = 0.0f;
        currentState = PATROL;
    }

    float distance = std::sqrt((lastPlayerPos.x - position.x) * (lastPlayerPos.x - position.x) + (lastPlayerPos.y - position.y) * (lastPlayerPos.y - position.y));
    if (distance < detectionRadius) {
        searchTimer = 0.0f;
    }

    circle.setPosition(position);
}

void FSMEnemy::update(sf::Vector2f playerPos, float deltaTime) {
    switch (currentState) {
    case PATROL:
        patrol();
        if (detectPlayer(playerPos)) currentState = CHASE;
        break;

    case CHASE:
        chase(playerPos);
        if (!detectPlayer(playerPos)) {
            lastPlayerPosition = playerPos;
            currentState = SEARCH;
        }
        break;

    case SEARCH:
        search(lastPlayerPosition, deltaTime);
        break;
    }
}


