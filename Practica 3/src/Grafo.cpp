#include "Grafo.h"

        using namespace std;
        Grafo::Grafo(int tamanio){
            this->n = tamanio;
            la =new list<int>[n];
        }
        void Grafo::aniadirArista(int n, int a){
            la[n].push_back(a);
            la[a].push_back(n);
        }
        vector<int> Grafo::recubrirGrafo(){
            bool visitados[n];
            vector<int> nodoscubiertos;
            for(int i=0;i<n;i++){
                visitados[i] = false;
            }

            list<int>::iterator i;

            for(int u=0;u<n;u++){
                if(visitados[u] == false){
                    for(i = la[u].begin();i!=la[u].end();i++){
                        int x = *i;
                        if(visitados[x] == false){
                            visitados[x] = true;
                            visitados[u] = true;
                            break;
                        }
                    }
                }
            }
            for(int i=0;i<n;i++){
                if(visitados[i]){
                    nodoscubiertos.push_back(i);
                }
            }

            return nodoscubiertos;
            
        }