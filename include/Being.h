#ifndef _BEING_H
#define _BEING_H

#include "SFML/System.hpp"

class Being{
private:
    static int nBeings;
protected:
    int id;
    sf::Vector2<float> pos, vel;

public:

    Being(const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f});
    virtual ~Being();

    void setPos(const sf::Vector2<float>& pos);
    void setVel(const sf::Vector2<float>& vel);

    const int getId() const;
    const sf::Vector2<float> getPos() const;
    const sf::Vector2<float> getVel() const;

};
#endif