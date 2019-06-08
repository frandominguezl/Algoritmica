#ifndef TSP_HEURISTICA_H
#define TSP_HEURISTICA_H
#include "Nodo.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include <chrono>
using namespace std;

vector<nodo> llenaGrafo_2opt(const char  fichero[]);

int Coste(vector<nodo> camino);

void Swap( vector<nodo> & nuevo_camino,vector<nodo> camino, int i, int k );

vector<nodo> TwoOpt(vector<nodo> camino, int max_vueltas);


#endif