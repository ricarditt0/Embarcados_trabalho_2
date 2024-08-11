/*
    Arquivo principal que contém as implementações dos algoritmos solicitados
*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<queue>
#include<unordered_set>
#include<iomanip>
#include"Nodo.cpp"
#include<chrono>
#include<cmath>
#include"energia.h"

using namespace std;

int comprimento_solucao = 0;
int heuristica_inicial = 0;
auto inicio = std::chrono::high_resolution_clock::now();
auto resultado = std::chrono::high_resolution_clock::now() - inicio;

void delete_nodos(vector<Nodo*> &nos_alocados)
{
    resultado = std::chrono::high_resolution_clock::now() - inicio;

    nos_alocados[0]->clear_id();
    for(int i = 0 ; i < nos_alocados.size(); i++){
        delete nos_alocados[i];
    }
}

void readInputs(vector<vector<short int>>& inputs ,int argc ,char* argv[])
{
    vector<short int> input;
    for(int i = 1;i < argc; i++){
        if(strlen(argv[i]) == 2){
            input.push_back(atoi(argv[i]));
            inputs.push_back(input);
            input.clear();
        }
        else{
            input.push_back(atoi(argv[i]));
        }
    }   
    inputs.push_back(input);
}

void gbfs(vector<short int> init_estate)
{
    nos_expandidos = 0;
    comprimento_solucao = 0;

    unordered_set<string> explorados;
    priority_queue<Nodo*,vector<Nodo*>, CompareGBFS> fronteira;
    vector<Nodo*> sucessores;
    vector<Nodo*> nos_alocados;
    vector<string> caminho;
    Nodo* solucao;

    int stop = 0;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    nos_alocados.push_back(init);
    init->distanceManhatan();
    heuristica_inicial = init->h;
    if(init->e_Solucao()){
        delete init;
        return ;
    }
    
    fronteira.push(init);
    while(!fronteira.empty()){

        Nodo *atual = fronteira.top();
        fronteira.pop();

        if(!explorados.count(atual->convert())){
            explorados.insert(atual->convert());
            if(atual->e_Solucao()){
                atual->caminho(caminho);
                comprimento_solucao = (caminho.size());
                //resultado = std::chrono::high_resolution_clock::now() - inicio;
                delete_nodos(nos_alocados);
                return ;
            }
            atual->expande(sucessores,atual,nos_alocados);
            while(!sucessores.empty()){
                fronteira.push(sucessores.front());
                sucessores.erase(sucessores.begin());
            }
        }
    }
    return ;
}

int main(int argc, char *argv[])
{
    int stop;
    vector<vector<short int>> inputs;
    time_t start, end;
    double time_taken ;
    rapl_init();


    readInputs(inputs,argc,argv);

    cout << "nos expandidos ," << "comprimento da solucao ," << "tempo de execucao ," << "energia em joules" << endl;
    for(int i = 0;i<inputs.size();i++){

        inicio = std::chrono::high_resolution_clock::now();
        start_rapl_sysfs();
        gbfs(inputs[i]);
        double energy = end_rapl_sysfs();  
        cout << nos_expandidos << ',';
        cout << comprimento_solucao << ',';
        cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
        cout << energy << endl;
    }
}