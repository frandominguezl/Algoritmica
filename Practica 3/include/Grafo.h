#ifndef GRAFO_H
#define GRAFO_H
#include <list>
#include <iostream>
#include <vector>

using namespace std;

class Grafo{
    private:
        int n; //Numero de nodos
        list<int> *la; //Punteros a array que contienen las listas de adyacencia
    public:
        Grafo(int tamanio);
        void aniadirArista(int n, int a);
        vector<int> recubrirGrafo();
};


#endif