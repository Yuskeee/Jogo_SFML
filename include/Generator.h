#ifndef _ENEMY_GENERATOR_H
#define _ENEMY_GENERATOR_H
#include "Zombie.h"
#include "Flower.h"
#include "BadPortal.h"
#include "GoodPortal.h"
#include "Treadmill.h"
#include "Spears.h"
#include "Saw.h"
#include <stdlib.h>
#include <ctime>

namespace World{
    class Level;
    class Map;
}

class Generator{
private:

    const float spawnTime = 10;
    float spawnTimer;
    World::Level* pLevel;
    World::Map* pMap;

    void spawnRandomPortal();
    void spawnRandomTreadmill();
    void spawnRandomSpears();
    void spawnRandomSaw();

public:
    Generator(World::Level* pLevel, World::Map* pMap);
    ~Generator();

    void update(float dt);
    void spawnEnemy(const sf::Vector2<float>& pos);
    void spawnExitPortal();

    void generateObstacles();

    void setMap(World::Map* pMap);


};

#endif
