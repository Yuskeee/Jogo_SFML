#ifndef _PLAYER_STATS_H
#define _PLAYER_STATS_H

#include "Player.h"

namespace World{
class Level;
}

#define HEART_FILE "../assets/heart.png"

#define RED_HEART 0, 0, 20, 20
#define BLACK_HEART 20, 0, 20, 20

class PlayerStats{//deve ser iniciada logo após criação dos players
private:
    World::Level *pLevel;
    Managers::textID livesText_p1;
    Managers::textID livesText_p2;
    Managers::spriteID *hearts_p1;
    Managers::spriteID *hearts_p2;
    static const Entities::Player *p1, *p2;

    int maxLives_p1;
    int maxLives_p2;

    static PlayerStats* instance;

private:
    PlayerStats(Managers::Graphics *pGraphicsManager = NULL, World::Level *pLevel = NULL, const Entities::Player *p1 = NULL, const Entities::Player *p2 = NULL);

public:
    static PlayerStats* getPlayerStatsInstance(Managers::Graphics *pGraphicsManager = NULL, World::Level *pLevel = NULL, const Entities::Player *p1 = NULL, const Entities::Player *p2 = NULL);

    ~PlayerStats();

    void update();

    void draw();

    static void setPlayer1(Entities::Player *p1);
    static void setPlayer2(Entities::Player *p2);
};

#endif
