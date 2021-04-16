#ifndef _LEVEL_H
#define _LEVEL_H

#include <fstream> 

#include "Graphics.h"
#include "Map.h"
#include "Physics.h"
#include "List.h"

#include "Entity.h"
#include "Player.h"
#include "Zombie.h"
#include "Flower.h"

namespace World{

class Level{

private:

    enum Levels{
        Level1,
        Level2,
        Level3,
        nLevels
    };
    char levelMapFiles[nLevels][30] = {
        "../assets/map1.txt",
        "../assets/map2.txt",
        "../assets/map3.txt"
    };
    char levelBackgroundFiles[nLevels][30] = {
        "../assets/background1.png",
        "../assets/background2.png",
        "../assets/background3.jpg"
    };

    int players;
    Managers::Graphics* pGraphicsManager;
    List<Entities::Entity*> entities;
    Map map;
    Physics LevelPhysics;
    Managers::spriteID backgroundSprite;

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
    void loadMap(const char* arquivo);
    
    //void salvar(char* arquivo);
    int getPlayers();
    Managers::Graphics* getGraphicsManager();


};
}

#endif
