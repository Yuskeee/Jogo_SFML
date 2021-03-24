#ifndef _MAP_H
#define _MAP_H

#include "Graphics.h"
#include <fstream>

#define MAP_WIDTH  40 //largura do mapa em blocos
#define MAP_HEIGHT 30 //altura do mapa em blocos

#define TILE_WIDTH  16 //largura do bloco em pixels
#define TILE_HEIGHT 16 //altura do bloco em pixels

class Map{
public:
    enum Tiles{
        airTile,        //bloco vazio
        groundTile,     //chao
        groundTopTile,  //parte superior do chao     
        brickTile,      //tijolo 
        nTileTypes      //numero total de tipos de blocos, por enquanto apenas 3
    };


private:
    char** map;
    Managers::spriteID tileset[nTileTypes];

public:
    Map(Managers::Graphics* pGraphicsManager = NULL);
    ~Map();

    void load(const char* file);
    void draw(Managers::Graphics* pGraphicsManager);

};


#endif