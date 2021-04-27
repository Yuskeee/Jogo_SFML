#include "Level.h"
#include "Boss.h"

using namespace Entities;

Boss::BossRunState::BossRunState(SM::StateMachine* pStateMachine, Boss *b):State(pStateMachine){
    this->b = b;
}

Boss::BossRunState::~BossRunState(){

}

void Boss::BossRunState::enter(void* arg){
    b->lastPosX = -1;//reinicia ultima posicao em x
    b->vulnerability = true;
    b->frame = b->to_right ? Managers::spriteRect(BOSS_RUN1_RIGHT) : Managers::spriteRect(BOSS_RUN1_LEFT);
}

void Boss::BossRunState::update(float dt, Managers::Events* pEventsManager){

    b->vel.x = (b->to_right) ? b->velMax:-b->velMax;

    b->cycleTimer += dt;
    if(b->cycleTimer >= b->cycleTime){
        b->cycleTimer = 0;
        if(b->to_right)
            b->frame = b->frame == Managers::spriteRect(BOSS_RUN1_RIGHT) ? Managers::spriteRect(BOSS_RUN2_RIGHT) : Managers::spriteRect(BOSS_RUN1_RIGHT);
        else
            b->frame = b->frame == Managers::spriteRect(BOSS_RUN1_LEFT) ? Managers::spriteRect(BOSS_RUN2_LEFT) : Managers::spriteRect(BOSS_RUN1_LEFT);
    }

    if(b->pos.x == b->lastPosX){
        b->to_right = !b->to_right;
        pStateMachine->changeState(BossChargingStateID, NULL);
    }

    b->lastPosX = b->pos.x;

}

void Boss::BossRunState::render(Managers::Graphics* pGraphicsManager){

}

//BossChargingState-------------------

Boss::BossChargingState::BossChargingState(SM::StateMachine* pStateMachine, Boss *b): State(pStateMachine){
    this->b = b;
}

Boss::BossChargingState::~BossChargingState(){

}

void Boss::BossChargingState::enter(void* arg){
    b->fire_timer = 0;
    b->run_timer = 0;
    b->frame = b->to_right ? Managers::spriteRect(BOSS_DEFAULT_RIGHT) : Managers::spriteRect(BOSS_DEFAULT_LEFT);
    b->vulnerability = false;
}

void Boss::BossChargingState::update(float dt, Managers::Events* pEventsManager){
    b->fire_timer += dt;
    b->run_timer += dt;

    if(b->fire_timer >= CHARGING_TIME){//chamada para atacar dado certo tempo
        b->attack();
        b->fire_timer = 0;
    }

    if(pow(b->DeltaX, 2) + pow(b->DeltaY, 2) < 10000 || b->run_timer >= RUN_TIME){//se jogador estiver muito proximo
        pStateMachine->changeState(BossRunStateID, NULL);
    }
}

void Boss::BossChargingState::render(Managers::Graphics* pGraphicsManager){

}

//BossStateMachine--------------------

Boss::BossStateMachine::BossStateMachine(Boss *b){
    SM::State* state = static_cast<SM::State*>(new BossRunState(static_cast<StateMachine*>(this), b));
    addState(state);
    state = static_cast<SM::State*>(new BossChargingState(static_cast<StateMachine*>(this), b));
    addState(state);
    currentStateID = BossChargingStateID;
}

Boss::BossStateMachine::~BossStateMachine(){

}

//Boss---------------------------------

Boss::Boss(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel):
Enemy(pGraphicsManager, pLevel, pos, vel, {BOSS_WIDTH, BOSS_HEIGHT}), Being(enemy, pos, vel), DeltaX(), DeltaY(), to_right(false), lastPosX(0), fire_timer(0), run_timer(0){
    this->pGraphicsManager = pGraphicsManager;
    this->pLevel = pLevel;

    if(pGraphicsManager){
        idTextura = pGraphicsManager->loadTexture(BOSS_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        frame = Managers::spriteRect(BOSS_DEFAULT_LEFT);
        pGraphicsManager->setSpriteRect(idSprite, frame);

        BossSM = new BossStateMachine(this);
    }
}

Boss::~Boss(){
    delete BossSM;
}

void Boss::attack(){
    float velY = -(DeltaY + World::Physics::getGravityValue() * DeltaX * DeltaX * 0.5 / (projectile_velX * projectile_velX)) * projectile_velX / fabs(DeltaX);
    float velX = (DeltaX > 0) ? projectile_velX:-projectile_velX;

    Projectile* proj = new Projectile(pLevel->getGraphicsManager(), pLevel, pos, {velX, velY}, false, true);

    pLevel->addEntity(static_cast<Entities::Entity*>(proj));
    pLevel->addBody(static_cast<Body*>(proj));
}

void Boss::update(float dt, Managers::Events* pEventsManager){
    setTarget();

    DeltaX = getTarget()->getPos().x - pos.x;
    DeltaY = fabs(getTarget()->getPos().y - pos.y);

    if(BossSM)
        BossSM->update(dt, pEventsManager);

    pos += vel*dt;

    if(pGraphicsManager)
        pGraphicsManager->setSpriteRect(idSprite, frame);
}

void Boss::onCollide(Body* other, float dt){
    if(vulnerability){
        if((dynamic_cast<Projectile*>(other) && dynamic_cast<Projectile*>(other)->fromPlayer())){
            lives -= 1;
            if(lives == 0)
                pLevel->setScore(pLevel->getScore() + BOSS_SCORE_VALUE);
        }
    }
}

void Boss::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    saveBodyInfo(out);
    out << DeltaX << " " <<
           DeltaY << " " <<
           to_right << " " <<
           lastPosX << " " <<
           cycleTimer << " " <<
           run_timer << " " <<
           fire_timer << " " <<
           BossSM->getCurrentState() << std::endl;

}
