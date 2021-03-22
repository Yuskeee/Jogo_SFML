#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entidade.h"


class Player: public Entidade{

private:
    const float acceleration = 5;
    const float velMax = 60;

public:

    Player(Graphics* pGraphics = NULL, sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, textureID idT = -1, spriteID idS = -1);
    virtual ~Player();

    virtual void update(float dt, Events* pEvents);


};




#endif