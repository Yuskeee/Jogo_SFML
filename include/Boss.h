#ifndef _BOSS_H
#define _BOSS_H

#include "Enemy.h"
#include "states/State.h"
#include "Body.h"
#include "Physics.h"
#include <math.h>

#define CHARGING_TIME 1.5
#define RUN_TIME 5

#define BOSS_SCORE_VALUE 50

#define BOSS_DEFAULT_LEFT     0,  0,  20, 20
#define BOSS_DEFAULT_RIGHT    20, 0, -20, 20
#define BOSS_RUN1_LEFT        20, 0,  20, 20
#define BOSS_RUN1_RIGHT       40, 0, -20, 20
#define BOSS_RUN2_LEFT        40, 0,  20, 20
#define BOSS_RUN2_RIGHT       60, 0, -20, 20

#define BOSS_WIDTH   20.0f
#define BOSS_HEIGHT  20.0f

#define BOSS_TEXTURE_FILE "../assets/boss.png"

namespace World{
class Level;
}

namespace Entities{

class Boss: public Enemy{
private:
    enum BossStates{
        BossRunStateID,
        BossChargingStateID
    };

    class BossRunState: public SM::State{
    private:
        Boss *b;

    public:
        BossRunState(SM::StateMachine* pStateMachine = NULL, Boss *b = NULL);
        ~BossRunState();

        void enter(void* arg);

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };

    class BossChargingState: public SM::State{
    private:
        Boss *b;
    public:
        BossChargingState(SM::StateMachine* pStateMachine = NULL, Boss *b = NULL);
        ~BossChargingState();

        void enter(void* arg);

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };

    class BossStateMachine: public SM::StateMachine{
    public:
        BossStateMachine(Boss *b = NULL);
        ~BossStateMachine();
    };

private:
    const float velMax = 200;
    const float projectile_velX = 200;
    float DeltaX, DeltaY;

    bool to_right;

    float lastPosX;
    const float cycleTime = 0.2;
    float cycleTimer;

    float fire_timer;
    float run_timer;

    SM::StateMachine *BossSM;

public:
    Boss(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f});
    virtual ~Boss();

    virtual void attack();

    virtual void update(float dt, Managers::Events* pEventsManager);

    virtual void onCollide(Body* other, float dt);

    virtual void saveEntity(std::ofstream& out) const;
    virtual void loadEntity(std::ifstream& in);

};

}

#endif
