#ifndef _ENEMY_GENERATOR_H
#define _ENEMY_GENERATOR_H
#include "Zombie.h"
#include "Flower.h"
#include "BadPortal.h"
#include <stdlib.h>
#include <ctime>

namespace World{
    class Level;
    class Map;
}

class EnemyGenerator{
private:

    const float spawnTime = 10;
    float spawnTimer;
    World::Level* pLevel;
    World::Map* pMap;

public:
    EnemyGenerator(World::Level* pLevel, World::Map* pMap);
    ~EnemyGenerator();

    void update(float dt);
    void spawnEnemy(const sf::Vector2<float>& pos);
    void spawnRandomPortal();


};

#endif