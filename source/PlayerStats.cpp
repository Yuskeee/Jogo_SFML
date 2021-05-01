#include "PlayerStats.h"
#include "Level.h"

PlayerStats* PlayerStats::instance = NULL;
const Entities::Player* PlayerStats::p1 = NULL;
const Entities::Player* PlayerStats::p2 = NULL;

PlayerStats::PlayerStats(Managers::Graphics *pGraphicsManager, World::Level *pLevel, const Entities::Player *p1, const Entities::Player *p2): livesText_p1(-1), livesText_p2(-1){
    this->p1 = p1;
    this->p2 = p2;
    this->pLevel = pLevel;

    if(pGraphicsManager){
        Managers::textureID idTexture = pGraphicsManager->loadTexture(HEART_FILE);

        if(p1){
            livesText_p1 = pGraphicsManager->createText(0, "P1 ", 10);
            pGraphicsManager->setTextPos(livesText_p1, 50, 20);

            hearts_p1 = new Managers::spriteID[p1->getLives()];
            for(int i = 0; i < maxLives; i++){
                hearts_p1[i] = pGraphicsManager->createSprite(idTexture);
                pGraphicsManager->setSpriteRect(hearts_p1[i], Managers::spriteRect(RED_HEART));
                pGraphicsManager->setSpritePos(hearts_p1[i], 70 + 20 * i,20);
            }
        }
        else
            hearts_p1 = NULL;
        if(p2){
            livesText_p2 = pGraphicsManager->createText(0, "P2 ", 10);
            pGraphicsManager->setTextPos(livesText_p2, 450, 20);

            hearts_p2 = new Managers::spriteID[p2->getLives()];
            for(int i = 0; i < maxLives; i++){
                hearts_p2[i] = pGraphicsManager->createSprite(idTexture);
                pGraphicsManager->setSpriteRect(hearts_p2[i], Managers::spriteRect(RED_HEART));
                pGraphicsManager->setSpritePos(hearts_p2[i], 470 + 20 * i,20);
            }
        }
        else
            hearts_p2 = NULL;
    }
}

PlayerStats* PlayerStats::getPlayerStatsInstance(Managers::Graphics *pGraphicsManager, World::Level *pLevel, const Entities::Player *p1, const Entities::Player *p2){
    if(instance == NULL){
        instance = new PlayerStats(pGraphicsManager, pLevel, p1, p2);
    }
    return instance;
}

PlayerStats::~PlayerStats(){
    if(p1){
        delete[] hearts_p1;
        hearts_p1 = NULL;
    }
    if(p2){
        delete[] hearts_p2;
        hearts_p2 = NULL;
    }
}

void PlayerStats::update(){
    if(p1){
        for(int i = 0; i < maxLives; i++){
            if(i > p1->getLives() - 1)
                pLevel->getGraphicsManager()->setSpriteRect(hearts_p1[i], Managers::spriteRect(BLACK_HEART));
        }
    }
    if(p2){
        for(int i = 0; i < maxLives; i++){
            if(i > p2->getLives() - 1)
                pLevel->getGraphicsManager()->setSpriteRect(hearts_p2[i], Managers::spriteRect(BLACK_HEART));
        }
    }
}

void PlayerStats::draw(){
    if(p1){
        pLevel->getGraphicsManager()->drawText(livesText_p1);
        for(int i = 0; i < maxLives; i++)
            pLevel->getGraphicsManager()->drawSprite(hearts_p1[i]);
    }
    if(p2){
        pLevel->getGraphicsManager()->drawText(livesText_p2);
        for(int i = 0; i < maxLives; i++)
            pLevel->getGraphicsManager()->drawSprite(hearts_p2[i]);
    }
}

void PlayerStats::setPlayer1(Entities::Player *p1){
    PlayerStats::p1 = p1;
}

void PlayerStats::setPlayer2(Entities::Player *p2){
    PlayerStats::p2 = p2;
}

void PlayerStats::eraseInstance(){
    std::cout << "INSTANCIA PLAYERSTATS APAGADA" << std::endl;
    if(instance)
        delete instance;
    instance = NULL;
}
