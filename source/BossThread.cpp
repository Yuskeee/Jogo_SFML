#include "BossThread.h"

using namespace Concurrent;

using namespace Entities;

const float* BossThread::pdt = NULL;
float BossThread::lastpdt(-1);

void BossThread::run(){
    _shouldRun = true;

    while(_shouldRun){
        if(!_isPaused){
            lock();

            if(lastpdt != *pdt){
                //std::cout << "THREAD RODANDO! " << *pdt << std::endl;
                update(*pdt, NULL);
                //std::cout << getLives() << std::endl;
            }

            lastpdt = *pdt;

            unlock();
        }
        else
            yield();
    }
}

BossThread::BossThread(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel):
Boss(pGraphicsManager, pLevel, pos, vel), Being(boss, {500, 400}, {0.0f, 0.f}), Thread(), _isPaused(false), _shouldRun(true){
    //std::cout << this->pos.x << std::endl;
}

BossThread::~BossThread(){
    std::cout << "Instancia APAGADA!!!\n";
}

void BossThread::stop(){
    _shouldRun = false;
}

const bool BossThread::isAlive() const{
    return _shouldRun;
}

void BossThread::pause(const bool pause){
    _isPaused = pause;
}

void BossThread::setpdt(const float &dt){
    BossThread::pdt = &dt;
}
