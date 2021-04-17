#ifndef _RANKING_H
#define _RANKING_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>

#define PATH "../saves/scores.txt"

#define MAX 5

typedef std::multimap<unsigned long int, std::string> Records;

class Ranking{
private:
     Records records;
     int entries;
     Records::reverse_iterator ranking_iterator;

     static Ranking* instance;

private:
    Ranking(std::string path = "");

    void load(std::string path);

    void save(std::string path);

public:
    static Ranking* getInstance();
    ~Ranking();

    void add(unsigned long int score, std::string name);

    int getSize();//retorna quantidade de entradas

    std::string getEntry();//retorna entrada por entrada

    void clear();//apaga o ranking vigente

    static void deleteInstance();
};

#endif

