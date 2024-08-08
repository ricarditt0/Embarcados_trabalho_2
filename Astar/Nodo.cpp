/*
    Este arquivo contém a descrição das classes usadas no arquivo principal. 
    A classe 'Nodo' é utilizada para as versões 8-puzzle, enquanto a classe 'Nodo16' é 
    utilizada para a versão 15-puzzle. As classes 'Compare' são utilizadas para decidir 
    a ordem das filas de prioridade.
*/

#include<vector>
#include<string>
#include<iostream>
#include<iomanip> 

using namespace std;

long int nos_expandidos = 0;
double media_heuristica = 0;
int media_count = 0;

class Nodo
{
    public:
    vector<short int> estado;
    Nodo* pai;
    string acao;
    int custo;
    int h;
    unsigned int id;

    static unsigned int ID;

    Nodo(){}

    Nodo(const vector<short int>& estado, Nodo* pai, const string& acao, int custo)
        : estado(estado), pai(pai), acao(acao), custo(custo) {id = ID ++;}

    void clear_id(){
        ID = 0;
    }

    int distanceManhatan(){
        media_count ++;
        int distancia = 0;
        for (int i = 0; i < 9; ++i) {
            if (estado[i]) {
                int val = estado[i];
                int rowDistance = std::abs((val) % 3 - static_cast<int>(i % 3));
                int colDistance = std::abs((val) / 3 - static_cast<int>(i / 3));
                distancia += rowDistance + colDistance;
            }
        }
        this->h = distancia;
        media_heuristica += distancia;
    	return distancia;
    }

    string convert()
    {
        std::string s;
        for (int elem : this->estado) {
                s = s + "," + std::to_string(elem);
            }
        return s;
    }

    bool e_Solucao()
    {
        for(int i = 0;i<this->estado.size();i++){
            if(this->estado[i] != i){
                return false;
            }
        }
        return true;
    }

    vector<short int> swap(vector<short int> estado , int index_alvo, int index_vazio)
    {
        std::vector<short int> new_estado = estado;
        new_estado[index_vazio] = new_estado[index_alvo];
        new_estado[index_alvo] = 0;
        return new_estado;
    }

    void expande(vector<Nodo*>& sucessores,Nodo *pai,vector<Nodo*>& nos_alocados)
    {
        nos_expandidos++;
        int i = 0;
        int custo = 0;
        while (this->estado[i] != 0)
            i ++;
	
        if(i != 0 && i != 1 && i != 2 && this->acao.compare("baixo")){
            sucessores.push_back(new Nodo(swap(this->estado,i-3,i),pai,"cima",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
            sucessores.back()->distanceManhatan();
        }

        if(i != 0 && i != 3 && i != 6 && this->acao.compare("direita")){
            sucessores.push_back(new Nodo(swap(this->estado,i-1,i),pai,"esquerda",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
            sucessores.back()->distanceManhatan();
        }

        if(i != 2 && i != 5 && i != 8 && this->acao.compare("esquerda")){
            sucessores.push_back(new Nodo(swap(this->estado,i+1,i),pai,"direita",this->custo + 1));
            nos_alocados.push_back(sucessores.back());
            sucessores.back()->distanceManhatan();
        }

        if(i != 6 && i != 7 && i != 8 && this->acao.compare("cima")){
            sucessores.push_back(new Nodo(swap(this->estado,i+3,i),pai,"baixo",this->custo + 1));
            nos_alocados.push_back(sucessores.back()); 
            sucessores.back()->distanceManhatan();
        }
    }

    void caminho(vector<string> &caminho){
        if(this->pai){
            caminho.push_back(this->acao);
            this->pai->caminho(caminho);
        }
    }


};

unsigned int Nodo::ID = 0;

class CompareASTAR
{
    public:
        bool operator()(Nodo *a,Nodo *b){
            int f_a = a->custo + a->h;
            int f_b = b->custo + b->h;
            if(f_a != f_b)
                return f_a > f_b;
            if(a->h!= b->h)
                return a->h > b->h;
            return a->id < b->id;
        }
};

