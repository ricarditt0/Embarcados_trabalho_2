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

void bfs(vector<short int> init_estate)
{
    media_count = 0;
    media_heuristica = 0;
    nos_expandidos = 0;
    comprimento_solucao = 0;

    unordered_set<string> explorados;
    queue<Nodo*> fronteira;
    vector<Nodo*> sucessores;
    vector<Nodo*> nos_alocados;
    vector<string> caminho;
    Nodo* solucao;

    Nodo *init = new Nodo (init_estate,NULL,"",0);
    nos_alocados.push_back(init);
    heuristica_inicial = init->distanceManhatan();
    if(init->e_Solucao()){
        delete init;
        return ;
    }

    fronteira.push(init);
    explorados.insert(init->convert());
    while (!fronteira.empty()){
        Nodo *atual = fronteira.front();
        fronteira.pop();
        atual->expande(sucessores,atual,nos_alocados);
        while(!sucessores.empty()){ 
            if(sucessores.front()->e_Solucao()){
                solucao = sucessores.front();
                solucao->caminho(caminho);
                comprimento_solucao = caminho.size();
                media_heuristica = 0;
                //resultado = std::chrono::high_resolution_clock::now() - inicio;
                delete_nodos(nos_alocados);
                return ;
            }

            if(!explorados.count(sucessores.front()->convert())){
                explorados.insert(sucessores.front()->convert());
                fronteira.push(sucessores.front());
            }
            sucessores.erase(sucessores.begin());
        }
    }
    return ;
}

void gbfs(vector<short int> init_estate)
{
    media_heuristica = 0;
    media_count = 0;
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
                media_heuristica = media_heuristica/media_count;
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

void astar(vector<short int> init_estate)
{
    nos_expandidos = 0;
    comprimento_solucao = 0;
    media_heuristica = 0;
    media_count = 0;

    unordered_set<string> explorados;
    priority_queue<Nodo*,vector<Nodo*>, CompareASTAR> fronteira;
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
                media_heuristica = media_heuristica/media_count;
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

    readInputs(inputs,argc,argv);

    for(int i = 0;i<inputs.size();i++){

        inicio = std::chrono::high_resolution_clock::now();
        bfs(inputs[i]);
        //resultado = std::chrono::high_resolution_clock::now() - inicio;
        cout << nos_expandidos << ',';
        cout << comprimento_solucao << ',';
        cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(resultado).count())/pow(10,9) <<',' ;
        cout << media_heuristica << ',';
        cout << heuristica_inicial << endl;
     }
    
}