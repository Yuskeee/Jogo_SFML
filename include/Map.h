#ifndef _MAP_H
#define _MAP_H

#include "Graphics.h"
#include <fstream>

namespace World{

#define MAP_WIDTH  40 //largura do mapa em blocos
#define MAP_HEIGHT 30 //altura do mapa em blocos

#define TILE_WIDTH  16 //largura do bloco em pixels
#define TILE_HEIGHT 16 //altura do bloco em pixels

class Map{
public:
    enum Tiles{
        airTile,        //bloco vazio               letra a no txt
        groundTile,     //chao                      letra b
        groundTopTile,  //parte superior do chao    c
        brickTile,      //tijolo                    d

        nTileTypes      //numero total de tipos de blocos
    };
private:

    bool isSolid[nTileTypes] = {
        false,
        true,
        true,
        true
    };

    char TileTextureFiles[nTileTypes][30] = {//vetor das strings dos arquivos das texturas dos blocos

    "../assets/air.png",        //letra a no txt
    "../assets/ground.png",     //letra b
    "../assets/ground_top.png", //c
    "../assets/brick.png"       //d

    };

    char** map;
    Managers::spriteID tileset[nTileTypes];//vetor de sprites

public:
    Map(Managers::Graphics* pGraphicsManager = NULL);
    ~Map();

    void load(const char* file);//carrega uma matriz de letras de um txt
    void draw(Managers::Graphics* pGraphicsManager);//constroi e desenha o mapa com base na matriz de letras (cada letra representa um bloco diferente)
    const bool isPositionSolid(float x, float y)const;

    inline const int getWidth()const{return MAP_WIDTH;}
    inline const int getHeight()const{return MAP_HEIGHT;}

};
}

#endif
