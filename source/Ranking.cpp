#include "Ranking.h"

Ranking* Ranking::instance = NULL;

Ranking::Ranking(std::string path): records(), entries(0), ranking_iterator(){
    load(path);
    ranking_iterator = records.rbegin();
}

void Ranking::load(const std::string path){
    std::ifstream file(path, std::ios::in);

    if(file.is_open()){
        if(file.peek() == std::ifstream::traits_type::eof()){//verifica se o arquivo esta vazio
            std::cerr << "Records File is Empty\n";
            return;
        }

        std::string score, name;

        while(!file.eof() && entries <= MAX){
            getline(file, score, ';');//score
            getline(file, name, '\n');//nome

            //std::cout << score << " - " << name << std::endl;

            try{
            records.insert(Records::value_type(std::stoul(score), name));//insere os valores no map (automaticamente ordenados)
            entries++;
            }
            catch(std::invalid_argument e){
                //std::cerr << "Error: Invalid Argument!" << std::endl;
            }
        }

        file.close();
    }
    else
        std::cerr << "Error: File could not be open while loading records! (There may be no file)\n";
}

void Ranking::save(const std::string path){
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    Records::iterator aux_iterator = records.begin();//iterador temporario no inicio

    if(file.is_open()){
        std::string score, name;

        while(aux_iterator != records.end()){
            score = std::to_string(aux_iterator->first);

            name = aux_iterator->second;

            file << score
                 << ";"
                 << name
                 << std::endl;

            aux_iterator++;
        }

        file.close();
    }
    else
        std::cerr << "Error: File could not be open while saving records!\n";
}

Ranking* Ranking::getInstance(){
    if(instance == NULL){
        instance = new Ranking(PATH);
    }

    return instance;
}

Ranking::~Ranking(){
    instance = NULL;
}

void Ranking::add(unsigned long int score, std::string name){
    if(records.size() == MAX && score < records.begin()->first)//se o ranking estiver cheio e o score inserido é muito baixo
        return;
    if(records.size() == MAX)//se o ranking estiver cheio e o score é mais alto que a entrada mais baixa
        records.erase(records.begin());

    records.insert(Records::value_type(score, name));
    entries++;
}

const int Ranking::getSize()const{
    return entries;
}

const std::string Ranking::getEntry(){
    if(ranking_iterator != records.rend()){
        std::string aux;

        aux += std::to_string(ranking_iterator->first);//score
        aux += " - ";
        aux += ranking_iterator->second;//nome

        ranking_iterator++;//incrementa o iterador para proxima chamada

        //std::cout << aux << std::endl;

        return aux;
    }
    ranking_iterator = records.rbegin();//reinicia o iterador
    return "\0";//retorna NULL avisando que acabou a contêiner
}

void Ranking::clear(){
    records.clear();
    entries = 0;
}

void Ranking::deleteInstance(){//necessario para apagar instancia
    Ranking *ranking = getInstance();
    ranking->save(PATH);
    ranking->clear();//limpa o map

    delete instance;
}
