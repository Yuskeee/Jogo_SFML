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

void EnemyGenerator::spawnRandomTreadmill(){

    int treadmillPosX = rand()%(pMap->getWidth()-5)*TILE_WIDTH + rand()%TILE_WIDTH;
    int treadmillPosY = rand()%(pMap->getHeight()-3)*TILE_HEIGHT + rand()%TILE_HEIGHT;

    //sorteia uma posicao para o treadmill até que ele esteja fora de um bloco mas proximo do chao
    while(pMap->isPositionSolid(treadmillPosX, treadmillPosY) || pMap->isPositionSolid(treadmillPosX + TREADMILL_WIDTH/2, treadmillPosY + TREADMILL_HEIGHT/2) || pMap->isPositionSolid(treadmillPosX + TREADMILL_WIDTH, treadmillPosY + TREADMILL_HEIGHT)
        ||!pMap->isPositionSolid(treadmillPosX, treadmillPosY + TREADMILL_HEIGHT + 1) || !pMap->isPositionSolid(treadmillPosX + TREADMILL_WIDTH, treadmillPosY + TREADMILL_HEIGHT + 1)
        ||pLevel->getPhysics()->isLocationOcupied({(float)treadmillPosX, (float)treadmillPosY},{TREADMILL_WIDTH, TREADMILL_HEIGHT})){
        treadmillPosX = rand()%(pMap->getWidth()-5)*TILE_WIDTH + rand()%TILE_WIDTH;
        treadmillPosY = rand()%(pMap->getHeight()-3)*TILE_HEIGHT + rand()%TILE_HEIGHT;
    }
   
    Entities::Obstacles::Treadmill *t = new Entities::Obstacles::Treadmill(pLevel->getGraphicsManager(), pLevel, {(float)treadmillPosX, (float)treadmillPosY + 0.9f});
    pLevel->addEntity(static_cast<Entities::Entity*>(t));
    pLevel->addBody(static_cast<Body*>(t));


}

void EnemyGenerator::spawnRandomSpears(){

    int spearsPosX = rand()%(pMap->getWidth()-5)*TILE_WIDTH + rand()%TILE_WIDTH;
    int spearsPosY = rand()%(pMap->getHeight()-3)*TILE_HEIGHT + rand()%TILE_HEIGHT;

    //sorteia uma posicao para o spears até que ele esteja fora de um bloco mas proximo do chao
    while(pMap->isPositionSolid(spearsPosX, spearsPosY) || pMap->isPositionSolid(spearsPosX + SPEARS_WIDTH, spearsPosY + SPEARS_HEIGHT) 
        ||!pMap->isPositionSolid(spearsPosX, spearsPosY + SPEARS_HEIGHT+1) || !pMap->isPositionSolid(spearsPosX + SPEARS_WIDTH, spearsPosY + SPEARS_HEIGHT+1)
        ||pLevel->getPhysics()->isLocationOcupied({(float)spearsPosX, (float)spearsPosY},{SPEARS_WIDTH, SPEARS_HEIGHT})){
        spearsPosX = rand()%(pMap->getWidth()-5)*TILE_WIDTH + rand()%TILE_WIDTH;
        spearsPosY = rand()%(pMap->getHeight()-3)*TILE_HEIGHT + rand()%TILE_HEIGHT;
    }
   
    Entities::Obstacles::Spears *s = new Entities::Obstacles::Spears(pLevel->getGraphicsManager(), pLevel, {(float)spearsPosX, (float)spearsPosY + 0.9f});//deve ser colocado ligeramente mais abaixo que a posicao inteira sorteada, para que o sprite toque o chao visualmente
    pLevel->addEntity(static_cast<Entities::Entity*>(s));
    pLevel->addBody(static_cast<Body*>(s));


}

void EnemyGenerator::spawnRandomSaw(){

    int sawPosX = rand()%(pMap->getWidth()-5)*TILE_WIDTH + rand()%TILE_WIDTH;
    int sawPosY = rand()%(pMap->getHeight()-3)*TILE_HEIGHT + rand()%TILE_HEIGHT;

    //sorteia uma posicao para o saw até que ele esteja fora de um bloco mas proximo do chao
    while(pMap->isPositionSolid(sawPosX, sawPosY) || pMap->isPositionSolid(sawPosX + SAW_WIDTH, sawPosY + SAW_HEIGHT) 
        ||!pMap->isPositionSolid(sawPosX, sawPosY + SAW_HEIGHT+1) || !pMap->isPositionSolid(sawPosX + SAW_WIDTH, sawPosY + SAW_HEIGHT+1)
        ||pLevel->getPhysics()->isLocationOcupied({(float)sawPosX, (float)sawPosY},{SAW_WIDTH, SAW_HEIGHT})){
        sawPosX = rand()%(pMap->getWidth()-5)*TILE_WIDTH + rand()%TILE_WIDTH;
        sawPosY = rand()%(pMap->getHeight()-3)*TILE_HEIGHT + rand()%TILE_HEIGHT;
    }
   
    Entities::Obstacles::Saw *s = new Entities::Obstacles::Saw(pLevel->getGraphicsManager(), pLevel, {(float)sawPosX, (float)sawPosY + 0.5f});//deve ser colocado ligeramente mais abaixo que a posicao inteira sorteada, para que o sprite toque o chao visualmente
    pLevel->addEntity(static_cast<Entities::Entity*>(s));
    pLevel->addBody(static_cast<Body*>(s));


}

void EnemyGenerator::spawnExitPortal(){
    int portalPosX = rand()%(pMap->getWidth()-2)*TILE_WIDTH + rand()%TILE_WIDTH;
    int portalPosY = rand()%(pMap->getHeight()-2)*TILE_HEIGHT + rand()%TILE_HEIGHT;

    //sorteia uma posicao para o portal até que ele esteja fora de um bloco mas chao
    while(pMap->isPositionSolid(portalPosX, portalPosY) || pMap->isPositionSolid(portalPosX + GOOD_PORTAL_WIDTH, portalPosY + GOOD_PORTAL_HEIGHT)
        ||!pMap->isPositionSolid(portalPosX + (GOOD_PORTAL_WIDTH/2), portalPosY + GOOD_PORTAL_HEIGHT + 5)){
        portalPosX = rand()%(pMap->getWidth()-2)*TILE_WIDTH + rand()%TILE_WIDTH;
        portalPosY = rand()%(pMap->getHeight()-2)*TILE_HEIGHT + rand()%TILE_HEIGHT;
    }
   
    Entities::GoodPortal *p = new Entities::GoodPortal(pLevel->getGraphicsManager(), pLevel, {(float)portalPosX, (float)portalPosY});
    pLevel->addEntity(static_cast<Entities::Entity*>(p));
    pLevel->addBody(static_cast<Body*>(p));

}

void EnemyGenerator::generateObstacles(){

    int firstType, secondType;
    firstType = rand()%3;

    do secondType = rand()%3;
    while(firstType == secondType);//garante que os tipos sao diferentes

    if(firstType == 0 || secondType == 0)
        for(int i = 5 + rand()%3; i > 0; i--)//gera de 5 a 7
            spawnRandomTreadmill();
    if(firstType == 1 || secondType == 1)
        for(int i = 5 + rand()%3; i > 0; i--)//gera de 5 a 7
            spawnRandomSpears();
    if(firstType == 2 || secondType == 2)
        for(int i = 5 + rand()%3; i > 0; i--)//gera de 5 a 7
            spawnRandomSaw();
}

void EnemyGenerator::setMap(World::Map* pMap){
    this->pMap = pMap;
}
