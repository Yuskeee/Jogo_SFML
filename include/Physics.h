#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "Map.h"
#include "Body.h"
#include "List.h"

namespace World{

class Physics{

private:
    static const float gravity;
    const float maxVertVel = 300;

    Map* pMap;//ponteiro para o mapa (alocado em Level)
    List<Body*> bodies;//ponteiro para o vetor de entidades (alocado em Level)

    float getOffsetY(Body* bd);//calcula quanto uma corpo entrou verticalmente em um bloco solido do mapa
    float getOffsetX(Body* bd);//calcula quanto uma corpo entrou verticalmente em um bloco solido do mapa

    const bool checkBodyCollision(const Body* a, const Body* b) const;

public:
    Physics(Map* pMap = NULL);
    ~Physics();

    void collideMap();//colide todas as corpos com o mapa
    void collideBodies(float dt);//colide todas as corpos entre si

    void applyGravity(float dt);

    void addBody(Body* bd);
    const bool isLocationOcupied(const sf::Vector2<float>& pos, const sf::Vector2<float>& rect);
    void removeBody(int id);

    void setMap(World::Map* pMap);

    static const float getGravityValue();

};
}

#endif
