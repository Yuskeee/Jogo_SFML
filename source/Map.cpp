#include "Map.h"

using namespace World;

Map::Map(Managers::Graphics* pGraphicsManager){

    map = new char*[MAP_HEIGHT];

    for(int i = 0; i < MAP_HEIGHT; i++)
        map[i] = new char[MAP_WIDTH+1];// +1 pois precisa armazenar o \0 fornecido pelo getline

    for(int i = 0; i < nTileTypes; i++)//cria os sprites em ordem usando o vetor de nomes de arquivo
        tileset[i] = pGraphicsManager->createSprite(pGraphicsManager->loadTexture(TileTextureFiles[i]));

}

Map::~Map(){
    for(int i = 0; i < MAP_WIDTH; i++)
        delete[] map[i];
    delete[] map;
}

void Map::load(const char* file){
    std::fstream mapFile;
    mapFile.open(file, std::fstream::in);

    if(mapFile.is_open()){
        for(int i = 0; i < MAP_HEIGHT; i++){
            mapFile.getline(map[i], MAP_WIDTH*MAP_HEIGHT);
        }

        mapFile.close();
    }
}

void Map::draw(Managers::Graphics* pGraphicsManager){

    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++){
            pGraphicsManager->setSpritePos(tileset[map[i][j]-97], j*TILE_WIDTH, i*TILE_HEIGHT);
            pGraphicsManager->drawSprite(tileset[map[i][j]-97]);//artificio para construir mapas usando letras:
                                                                //subtraindo 97 de 'a' obtemos 0, de 'b' obtemos 1.
                                                                //assim mapeamos cada letra a uma posicao do vetor de sprites
        }
    }
}

bool Map::isPositionSolid(float x, float y){
    if((map[(int)(y/TILE_HEIGHT)][(int)(x/TILE_WIDTH)] - 97) < nTileTypes)//verifica se é um bloco valido, evita problemas de acesso erroneo de memoria
        return isSolid[map[(int)(y/TILE_HEIGHT)][(int)(x/TILE_WIDTH)] - 97];
    else
        return false;
}