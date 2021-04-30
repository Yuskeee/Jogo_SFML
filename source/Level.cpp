#include "Level.h"

using namespace World;

Level::Level(Managers::Graphics* pGraphicsManager):map(pGraphicsManager), LevelPhysics(&map), LevelGenerator(this, &map), thread_initiated(false){
    this->pGraphicsManager = pGraphicsManager;
    currentLevel = -1;
    backgroundSprite = -1;
    players = -1;
    changeRequested = false;
    isExitOpen = false;
    levelScore = 0;

    bossThread = NULL;
}

Level::~Level(){
    deleteBossThread();
    int id;
    PlayerStats::eraseInstance();
    for(int i = 0; i < entities.size(); i++){
        id = entities[i]->getId();
        LevelPhysics.removeBody(id);
        delete entities[i];
    }
}

void Level::update(float dt, Managers::Events* pEvents){

/* PARA THREADS----------------------------------*/
    if(currentLevel == 3){
        this->dt = dt;

        if(!bossThread){
            bossThread = new Entities::BossThread(pGraphicsManager, this);
            //addEntity(static_cast<Entities::Entity*>(bossThread));//alternativa não tomada
            addBody(static_cast<Body*>(bossThread));
        }

        if(thread_initiated == false){
            Entities::BossThread::setpdt(this->dt);
            bossThread->start();
            thread_initiated = true;
        }
    }

/* PARA THREADS----------------------------------*/

    for(auto i = entities.begin(); i != entities.end(); i++){//da para fazer esses loops com iterator tambem (talvez seja melhor)
        i->update(dt, pEvents);
    }

    for(auto i = entities.begin(); i != entities.end(); i++)//remove da lista as entidades com 0 ou menos vida
        if(i->getLives() <= 0){
            if(i->getType() == Being::player_1){
                Entities::Enemy::setPlayer1(NULL); //tira a referencia do player 1 do inimigo
                PlayerStats::setPlayer1(NULL);

                Entities::Ghost* g1 = new Entities::Ghost(pGraphicsManager, this, i->getPos(), sf::Vector2f(0, 0), true);
                addEntity(static_cast<Entities::Entity*>(g1));//cria o fantasma do player 1

                players--;
            }
            else if(i->getType() == Being::player_2){
                Entities::Enemy::setPlayer2(NULL); //tira a referencia do player 2 do inimigo
                PlayerStats::setPlayer2(NULL);

                Entities::Ghost* g2 = new Entities::Ghost(pGraphicsManager, this, i->getPos(), sf::Vector2f(0, 0), false);
                addEntity(static_cast<Entities::Entity*>(g2));//cria o fantasma do player 2

                players--;
            }
            removeBody(i->getId());
            removeEntity(i->getId());
        }

/* PARA THREADS----------------------------------*/
    if(bossThread)
        if(bossThread->getLives() <= 0 && bossThread->isAlive()){
            deleteBossThread();
            //removeEntity(bossThread->getId());
        }
/* PARA THREADS----------------------------------*/

    if(playersStats)
        playersStats->update();

    LevelGenerator.update(dt);

    if(bossThread)//caso haja thread do boss
        bossThread->lock();//deve parar o processamento da thread
    /*
        Essa é uma regiao critica do codigo, o processameto da fisica feito pelas
      funcoes abaixo acessa e possivelmente modifica os atributos de posicao e velocidade
      dos corpos, bem como possivelmente outros dependendo de cada entidade.
      Se o update do boss for executado junto com alguma dessas funcoes,
      uma "race condition" pode ocorrer.
    */

    LevelPhysics.applyGravity(dt);
    LevelPhysics.collideMap();
    LevelPhysics.collideBodies(dt);

    if(bossThread)//caso haja thread do boss
        bossThread->unlock();

    if(levelScore >= EXIT_SCORE + currentLevel*EXIT_SCORE)
        openExit();//abre um portal de saida com base no score total

    if(changeRequested)//ao final do processamento, muda o nivel caso tenha sido requisitado
        changeLevel();
}

void Level::render(){
    map.draw(pGraphicsManager);
    for(int i = 0; i < entities.size(); i++)
        entities[i]->draw();

    if(playersStats)
        playersStats->draw();

/* PARA THREADS----------------------------------*/
    if(currentLevel == 3 && bossThread && bossThread->isAlive())
        bossThread->draw();
/* PARA THREADS----------------------------------*/

}

void Level::addEntity(Entities::Entity* pEntity){//adiciona uma entidade no vetor de entidades
        entities.push_back(pEntity);
}

void Level::removeEntity(int id){


    for(auto i = entities.begin(); i != entities.end(); i++){
        if(i->getId() == id){
            if(!dynamic_cast<Entities::BossThread*>(*i))
                delete *i;
            entities.erase(i);
            break;
        }
    }
}

void Level::addBody(Body* pBody){
    LevelPhysics.addBody(pBody);
}
void Level::removeBody(int id){
    LevelPhysics.removeBody(id);
}

void Level::startLevel(int n, int players){
    currentLevel = n;
    totalPlayers = players;
    isExitOpen = false;
    changeRequested = false;

    loadMap(levelMapFiles[n]);
    this->players = players;

    Entities::Player* p1 = new Entities::Player(pGraphicsManager, this, sf::Vector2f(20, 20), sf::Vector2f(0, 0));
    addEntity(static_cast<Entities::Entity*>(p1));//adiciona o player na lista de entidades da fase
    addBody(static_cast<Body*>(p1));//adiciona o player na lista de corpos da fisica

    if(players > 1){
        Entities::Player* p2 = new Entities::Player(pGraphicsManager, this, sf::Vector2f(50, 20), sf::Vector2f(0, 0), false);
        addEntity(static_cast<Entities::Entity*>(p2));//adiciona o player na lista de entidades da fase
        LevelPhysics.addBody(static_cast<Body*>(p2));//adiciona o player na lista de corpos da fisica
        Entities::Enemy::setPlayer1(p1);
        Entities::Enemy::setPlayer2(p2);
        playersStats = PlayerStats::getPlayerStatsInstance(pGraphicsManager, this, p1, p2);
    }
    else{
        Entities::Enemy::setPlayer1(p1);
        Entities::Enemy::setPlayer2(NULL);
        playersStats = PlayerStats::getPlayerStatsInstance(pGraphicsManager, this, p1);
    }
    if(n == 2){
        Entities::Boss* b = new Entities::Boss(pGraphicsManager, this, sf::Vector2f(500, 400), sf::Vector2f(0, 0));
        addEntity(static_cast<Entities::Entity*>(b));
        LevelPhysics.addBody(static_cast<Body*>(b));
    }

    backgroundSprite = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(levelBackgroundFiles[n]));
    pGraphicsManager->setBackground(backgroundSprite);

    LevelGenerator.generateObstacles();
}

const bool Level::startLevel(int _shouldLoad){
    if(_shouldLoad == 1)
        if(!load())
            return false;

    return true;
}

void Level::loadMap(const char* arquivo){
    map.load(arquivo);
}

void Level::requestLevelChange(){
    changeRequested = true;
}

void Level::changeLevel(){

/* PARA THREADS----------------------------------*/
    if(bossThread){
        if(thread_initiated == true){
            deleteBossThread();
        }
    }

/* PARA THREADS----------------------------------*/

    if(currentLevel == nLevels-1)
        players = 0;//se for o ultimo nivel, game over

    else{
        currentLevel++;

        Entities::Enemy::setPlayer1(NULL); //tira as referencias do player 1
        PlayerStats::setPlayer1(NULL);
        Entities::Enemy::setPlayer2(NULL); //tira as referencias do player 2
        PlayerStats::setPlayer2(NULL);

        //limpa o que sera reiniciado no novo nivel
        PlayerStats::eraseInstance();

        for(auto i = entities.begin(); i != entities.end(); i = entities.erase(i)){
            LevelPhysics.removeBody(i->getId());
            delete *i;
        }

        startLevel(currentLevel, totalPlayers);//inicia um novo nivel

    }
}

void Level::openExit(){
    if(!isExitOpen){
        LevelGenerator.spawnExitPortal();
        isExitOpen = true;
    }
}

void Level::setScore(int score){
    levelScore = score;
}

int Level::getScore(){
    return levelScore;
}

Generator* Level::getGenerator(){
    return &LevelGenerator;
}

Managers::Graphics* Level::getGraphicsManager(){
    return pGraphicsManager;
}

Managers::spriteID Level::getBackground(){
    return backgroundSprite;
}

int Level::getPlayers(){
    return players;
}

World::Physics* Level::getPhysics(){
    return &LevelPhysics;
}

/* PARA THREADS----------------------------------*/
Entities::BossThread* Level::getBossThread(){
    return bossThread;
}

void Level::deleteBossThread(){
    if(bossThread){
        bossThread->stop();
        removeBody(bossThread->getId());

        delete bossThread;
        bossThread = NULL;
        thread_initiated = false;
    }
}
/* PARA THREADS----------------------------------*/

bool Level::save(){
    std::ofstream file(SAVE_FILE, std::ios::out | std::ios::trunc | std::ios::binary);
    List<Entities::Entity*>::Iterator aux_iterator = entities.begin();

    if(file.is_open()){

        //salva propriedades de level
        file << currentLevel    << " " <<
                players         << " " <<
                totalPlayers    << " " <<
                isExitOpen      << " " <<
                changeRequested << " " <<
                levelScore      /*<< std::endl*/;

        //salva entidades
        while(aux_iterator != entities.end()){

            try{
                file << std::endl;
                file << *(*aux_iterator);
            }
            catch(std::invalid_argument e){
                std::cerr << "Error: Entity could not be saved!" << std::endl;
                std::remove(SAVE_FILE);//deleta o arquivo corrompido
                return false;//nao foi possivel gravar
            }

            aux_iterator++;
        }

        //como o BossThread não pertence à lista de entidades, devemos lidar com ele manualmente
        if(bossThread)
            file << std::endl;
            file << *bossThread;

        file.close();
    }
    else{
        std::cerr << "Error: File could not be open while saving game!\n";
        std::remove(SAVE_FILE);//deleta o arquivo corrompido
        return false;//nao foi possivel gravar
    }
    return true;
}

bool Level::load(){
    std::ifstream file(SAVE_FILE, std::ios::in | std::ios::binary);

    if(file.is_open()){
        if(file.peek() == std::ifstream::traits_type::eof()){//verifica se o arquivo esta vazio
            std::cerr << "Saved game file is Empty!\n";
            return false;
        }

        Entities::Player *p1 = NULL, *p2 = NULL;

        //carrega primeiramente o level
        bool _level_loaded = loadLevel(file);

        while(file.good() && _level_loaded){
            int type;


            try{
                file >> type;
                std::cout << type << std::endl;
                switch(type){
                    case 0:
                    case 1:
                        {
                            Entities::Player* pEntity = new Entities::Player(pGraphicsManager, this, (type == 0) ? true: false);//player_1 e player_2
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));

                            if(type == 0){
                                Entities::Enemy::setPlayer1(pEntity);
                                p1 = pEntity;
                            }
                            else{
                                Entities::Enemy::setPlayer2(pEntity);
                                p2 = pEntity;
                            }
                            std::cout << "success players!" << std::endl;
                            break;
                        }
                    case 2:
                    case 3:
                        {
                            Entities::Ghost* pEntity = new Entities::Ghost(pGraphicsManager, this, (type == 2) ? true: false);//ghost_1 e ghost_2
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            std::cout << "success ghosts!" << std::endl;
                            break;
                        }
                    case 4:
                        {
                            Entities::GoodPortal* pEntity = new Entities::GoodPortal(pGraphicsManager, this);//good_portal
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success gportal!" << std::endl;
                            break;
                        }
                    case 5:
                        {
                            Entities::BadPortal* pEntity = new Entities::BadPortal(pGraphicsManager, this);//bad_portal
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            std::cout << "success bportal!" << std::endl;
                            break;
                        }
                    case 6:
                        {
                            Entities::Zombie* pEntity = new Entities::Zombie(pGraphicsManager, this);//zombie
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success zombie!" << std::endl;
                            break;
                        }
                    case 7:
                        {
                            Entities::Flower* pEntity = new Entities::Flower(pGraphicsManager, this);//flower
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success flower!" << std::endl;
                            break;
                        }
                    case 8:
                        {
                            //como o BossThread não pertence à lista de entidades, devemos lidar com ele manualmente
                            if(currentLevel == 3){
                                Entities::BossThread* pEntity = new Entities::BossThread(pGraphicsManager, this);//bossthread
                                file >> *pEntity;
                                addBody(static_cast<Body*>(pEntity));
                                bossThread = pEntity;
                            }
                            else{
                                Entities::Boss* pEntity = new Entities::Boss(pGraphicsManager, this);//boss
                                file >> *pEntity;
                                addEntity(static_cast<Entities::Entity*>(pEntity));
                                addBody(static_cast<Body*>(pEntity));
                            }

                            std::cout << "success boss!" << std::endl;
                            break;
                        }
                    case 9:
                    case 13:
                        {
                            Entities::Projectile* pEntity = new Entities::Projectile(pGraphicsManager, this, (type == 9) ? false: true);//projectile and projectile_boss
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success proj!" << std::endl;
                            break;
                        }
                    case 10:
                        {
                            Entities::Obstacles::Treadmill* pEntity = new Entities::Obstacles::Treadmill(pGraphicsManager, this);//treadmill
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success treadmill!" << std::endl;
                            break;
                        }
                    case 11:
                        {
                            Entities::Obstacles::Spears* pEntity = new Entities::Obstacles::Spears(pGraphicsManager, this);//spears
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success spears!" << std::endl;
                            break;
                        }
                    case 12:
                        {
                            Entities::Obstacles::Saw* pEntity = new Entities::Obstacles::Saw(pGraphicsManager, this);//saw
                            file >> *pEntity;
                            addEntity(static_cast<Entities::Entity*>(pEntity));
                            addBody(static_cast<Body*>(pEntity));
                            std::cout << "success saw!" << std::endl;
                            break;
                        }
                    default://não há entidade desse tipo -> erro
                        {
                            std::cerr << "Error: Entity type not recognized!" << std::endl;
                            std::remove(SAVE_FILE);//deleta o arquivo corrompido
                            return false;//nao foi possivel gravar
                        }
                }
            }
            catch(std::invalid_argument e){

            }
        }

        if(!file.eof() || !_level_loaded){
            std::cerr << "Error: the file was corrupted!" << std::endl;
            std::remove(SAVE_FILE);//deleta o arquivo corrompido
            return false;//nao foi possivel gravar
        }

        else{
            PlayerStats::eraseInstance();
            //dealing with Players
            if(p1 && !p2){
                std::cout << "PlayerStats 1\n";
                playersStats = PlayerStats::getPlayerStatsInstance(pGraphicsManager, this, p1);
            }
            else if(!p1 && p2){
                std::cout << "PlayerStats 2\n";
                playersStats = PlayerStats::getPlayerStatsInstance(pGraphicsManager, this, p2);
            }
            else if(players == 2 && p1 && p2){
                std::cout << "PlayerStats 1 e 2\n";
                playersStats = PlayerStats::getPlayerStatsInstance(pGraphicsManager, this, p1, p2);
            }
        }

        file.close();
    }
    else{
        std::cerr << "Error: File could not be open while loading the saved game! (There may be no file)\n";
        std::remove(SAVE_FILE);//deleta o arquivo corrompido
        return false;//nao foi possivel gravar
    }

    return true;
}

bool Level::loadLevel(std::ifstream& in){
    std::string content;

    try{
        getline(in, content, ' ');
        this->currentLevel = std::stoi(content);
        getline(in, content, ' ');
        this->players = std::stoi(content);
        getline(in, content, ' ');
        this->totalPlayers = std::stoi(content);
        getline(in, content, ' ');
        this->isExitOpen = (content == "1") ? true: false;
        getline(in, content, ' ');
        this->changeRequested = (content == "1") ? true: false;
        getline(in, content, '\n');
        this->levelScore = std::stoi(content);

        loadMap(levelMapFiles[currentLevel]);

        backgroundSprite = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(levelBackgroundFiles[currentLevel]));
        pGraphicsManager->setBackground(backgroundSprite);

    }
    catch(std::invalid_argument e){
        return false;
    }

    return true;
}
