#ifndef _ENEMY_H
#define _ENEMY_H

#include "Entity.h"
#include "Body.h"
#include "Player.h"

namespace World{
    class Level;
}

namespace Entities{

class Enemy: public Entity, public Body{
protected:
    static const Player *p1, *p2; //conhece 1(ou 2) jogadores estaticamente
    const float acceleration;
    const float velMax;
    const Player* target;

public:
    Enemy(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const sf::Vector2<float>& rect = {0.0f, 0.0f}, const float accel = 0, const float mVel = 0);
    virtual ~Enemy();

    virtual void update(float dt, Managers::Events* pEventsManager) = 0;
    virtual void attack() = 0;
    virtual void onCollide(Body* other, float dt) = 0;

    void setTarget();

    virtual void saveEntity(std::ofstream& out) const {};

    static void setPlayer1(const Player *p1);
    static void setPlayer2(const Player *p2);

    const Player* getTarget();

    static const Player* getP1();
    static const Player* getP2();
};

}

#endif
