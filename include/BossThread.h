#ifndef _BOSS_THREAD_H
#define _BOSS_THREAD_H

#include "Thread.h"
#include "Boss.h"

namespace Concurrent{

class BossThread: public Thread, public Entities::Boss{
private:
    bool _isPaused, _shouldRun;
    static const float *pdt;//aponta para contador de tempo da main thread
    static float lastpdt;

private:
    void run();

public:
    BossThread(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f});
    ~BossThread();

    void stop();
    void pause(const bool pause);//true para pausar e false para despausar thread

    const bool isAlive() const;

    static void setpdt(const float &dt);

};

}

#endif
