#ifndef _LEVEL_H
#define _LEVEL_H

#include <fstream> 

#include "Graphics.h"
#include "Entity.h"
#include "Player.h"
#include "Zombie.h"
#include "Map.h"
#include "Physics.h"
#include "List.h"

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

    Managers::Graphics* pGraphicsManager;
    List<Entities::Entity*> entities;
    Map map;
    Physics LevelPhysics;

public:
    Level(Managers::Graphics* pGraphicsManager);
    ~Level();

    void update(float dt, Managers::Events* pEvents);//chama update de todas as entidades no vetor
    void render();//desenha todas as entidades no vetor (e futuramente o mapa)

    //template <class entityClass> void addEntity(sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, Managers::textureID idT = -1, Managers::spriteID idS = -1){//adiciona uma entidade do tipo entityClass no vetor de entidades
    //    if(std::is_base_of<Entities::Entity, entityClass>::value){
    //        entityClass* newEntityInstance = new entityClass(pGraphicsManager, pos, vel, rect, idT, idS);
    //        Entities::Entity* newEntity = static_cast<Entities::Entity*>(newEntityInstance);
    //        entities.push_back(newEntity);
    //    }
    //}
    
    void startLevel(int n);
    void loadMap(const char* arquivo);
    //void salvar(char* arquivo);


};
}

#endif
