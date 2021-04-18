#include "EnemyGenerator.h"
#include "Level.h"
#include "Map.h"

EnemyGenerator::EnemyGenerator(World::Level* pLevel, World::Map* pMap){
    this->pLevel = pLevel;
    this->pMap = pMap;
    spawnTimer = 0;
    srand(time(NULL));

}
EnemyGenerator::~EnemyGenerator(){

}

void EnemyGenerator::update(float dt){
    spawnTimer += dt;

    if(spawnTimer > spawnTime){
        spawnRandomPortal();
        spawnTimer = 0;
    }

}

void EnemyGenerator::spawnEnemy(const sf::Vector2<float>& pos){
    if(rand()%2){
        Entities::Zombie* z1 = new Entities::Zombie(pLevel->getGraphicsManager(), pLevel, pos, sf::Vector2f(0, 0));
        pLevel->addEntity(static_cast<Entities::Entity*>(z1));//adiciona o zumbi na lista de entidades da fase
        pLevel->addBody(static_cast<Body*>(z1));//adiciona o zumbi na lista de corpos da fisica
    }
    else{
        Entities::Flower* f1 = new Entities::Flower(pLevel->getGraphicsManager(), pLevel, pos);
        pLevel->addEntity(static_cast<Entities::Entity*>(f1));//adiciona a flor na lista de entidades da fase
        pLevel->addBody(static_cast<Body*>(f1));//adiciona a flor na lista de corpos da fisica
    }

}

void EnemyGenerator::spawnRandomPortal(){
    int portalPosX = rand()%pMap->getWidth()*TILE_WIDTH;
    int portalPosY = rand()%pMap->getHeight()*TILE_HEIGHT;

    while(pMap->isPositionSolid(portalPosX, portalPosY) || pMap->isPositionSolid(portalPosX + BAD_PORTAL_WIDTH, portalPosY + BAD_PORTAL_HEIGHT)){
        portalPosX = rand()%pMap->getWidth();
        portalPosY = rand()%pMap->getHeight();
    }

    Entities::BadPortal *p = new Entities::BadPortal(pLevel->getGraphicsManager(), pLevel, {(float)portalPosX, (float)portalPosY});
    pLevel->addEntity(static_cast<Entities::Entity*>(p));

}

void EnemyGenerator::spawnExitPortal(){
    int portalPosX = rand()%(pMap->getWidth()-2)*TILE_WIDTH + rand()%TILE_WIDTH;
    int portalPosY = rand()%(pMap->getHeight()-2)*TILE_HEIGHT + rand()%TILE_HEIGHT;

    //sorteia uma posicao para o portal até que ele esteja fora de um bloco mas proximo do chao
    while(pMap->isPositionSolid(portalPosX, portalPosY) || pMap->isPositionSolid(portalPosX + GOOD_PORTAL_WIDTH, portalPosY + GOOD_PORTAL_HEIGHT)
        ||!pMap->isPositionSolid(portalPosX + (GOOD_PORTAL_WIDTH/2), portalPosY + GOOD_PORTAL_HEIGHT + 8)){
        portalPosX = rand()%(pMap->getWidth()-2)*TILE_WIDTH + rand()%TILE_WIDTH;
        portalPosY = rand()%(pMap->getHeight()-2)*TILE_HEIGHT + rand()%TILE_HEIGHT;
    }
   
    Entities::GoodPortal *p = new Entities::GoodPortal(pLevel->getGraphicsManager(), pLevel, {(float)portalPosX, (float)portalPosY});
    pLevel->addEntity(static_cast<Entities::Entity*>(p));
    pLevel->addBody(static_cast<Body*>(p));

}

void EnemyGenerator::setMap(World::Map* pMap){
    this->pMap = pMap;
}