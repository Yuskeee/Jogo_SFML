#ifndef _ENEMY_H
#define _ENEMY_H

#include "Entity.h"
#include "Body.h"
#include "Player.h"

namespace Entities{

class Enemy: public Entity, public Body{
protected:
    static const Player *p1, *p2; //conhece 1(ou 2) jogadores estaticamente
    const float acceleration;
    const float velMax;

public:
    Enemy(Managers::Graphics* pGraphicsManager = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const sf::Vector2<float>& rect = {0.0f, 0.0f}, Managers::textureID idT = -1, Managers::spriteID idS = -1, const float accel = 0, const float mVel = 0);
    virtual ~Enemy();

    virtual void loseLife(const int damage);//dano recebido

    virtual void update(float dt, Managers::Events* pEventsManager) = 0;
    virtual void attack() = 0;
    virtual void onCollide(Entity* other) = 0;

    static void setPlayers(const Player *p1, const Player *p2 = NULL);

    static const Player* getP1();
    static const Player* getP2();
};

}

#endif
