#ifndef _LEVEL_H
#define _LEVEL_H

#include <fstream>

#include "Graphics.h"
#include "Map.h"
#include "Physics.h"
#include "List.h"
#include "PlayerStats.h"

#include "Entity.h"
#include "Generator.h"
#include "Flower.h"
#include "Ghost.h"
#include "Boss.h"

#include "BossThread.h"

#define EXIT_SCORE 10

#define SAVE_FILE "../saves/Save.dat"

namespace World{

//class LevelThread;

class Level{

private:

    enum Levels{
        Level1,
        Level2,
        Level3,
        Level4,
        nLevels
    };
    char levelMapFiles[nLevels][30] = {
        "../assets/map1.txt",
        "../assets/map2.txt",
        "../assets/map3.txt",
        "../assets/map3.txt"
    };
    char levelBackgroundFiles[nLevels][30] = {
        "../assets/background1.png",
        "../assets/background2.png",
        "../assets/background3.jpg",
        "../assets/background3.jpg"
    };

    int currentLevel;
    int players;
    int totalPlayers;
    bool isExitOpen;
    bool changeRequested;
    int levelScore;
    Managers::Graphics* pGraphicsManager;
    Container::List<Entities::Entity*> entities;
    Map map;
    Physics LevelPhysics;
    Generator LevelGenerator;
    Managers::spriteID backgroundSprite;
    PlayerStats* playersStats;

/* Thread---------------------------*/
    //LevelThread* pLevelThread;
    Concurrent::BossThread* bossThread;
    bool thread_initiated;

    float dt;

public:
    Level(Managers::Graphics* pGraphicsManager);
    ~Level();

    void update(float dt, Managers::Events* pEvents);//chama update de todas as entidades no vetor
    void render();//desenha todas as entidades no vetor (e futuramente o mapa)

    void addEntity(Entities::Entity* pEntity);//adiciona uma entidade no vetor de entidades
    void removeEntity(int id);
    void addBody(Body* pBody);//adiciona um corpo na lista da fisica
    void removeBody(int id);

    void startLevel(int n, int players);
    const bool startLevel(int _shouldLoad);
    void loadMap(const char* arquivo);
    void requestLevelChange();
    void changeLevel();
    void openExit();

    void setScore(int score);
    int getScore();
    int getPlayers();
    Generator* getGenerator();
    Managers::Graphics* getGraphicsManager();
    Managers::spriteID getBackground();
    World::Physics* getPhysics();

    /* PARA THREADS----------------------------------*/
    Concurrent::BossThread* getBossThread();
    void deleteBossThread();
    /* PARA THREADS----------------------------------*/

    bool save();
    bool load();

private:
    bool loadLevel(std::ifstream& in);

};
}

#endif
