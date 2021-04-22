#ifndef _BEING_H
#define _BEING_H

#include "SFML/System.hpp"

class Being{

public:
    enum beingType{
        player_1,
        player_2,
        ghost_1,
        ghost_2,
        portal,
        enemy,
        projectile,
        treadmill,
        spears,
        boss_projectile,
        nBeingTypes
    };


private:
    static int nBeings;
protected:

    beingType type;
    int id;
    sf::Vector2<float> pos, vel;

public:

    Being(beingType type = player_1, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f});
    virtual ~Being();

    void setPos(const sf::Vector2<float>& pos);
    void setVel(const sf::Vector2<float>& vel);

    const int getId() const;
    const beingType getType() const;
    const sf::Vector2<float> getPos() const;
    const sf::Vector2<float> getVel() const;

};
#endif
