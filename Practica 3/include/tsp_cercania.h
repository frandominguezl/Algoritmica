#ifndef TSP_CERCANIA_H
#define TSP_CERCANIA_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include <chrono>
#include "Nodo.h"

using namespace std;
using namespace std::chrono;

//Función que lee el archivo de datos y transforma el problema en un vectro de nodos
vector<nodo> llenaGrafo_cercania(const char fichero[]);

// Calcula la distancia de un vector de nodos
double calcularDistanciaNodos(vector<nodo> &nodos);

// Selección del siguiente nodo a visitar
void seleccionarNodo(vector<nodo> &nodos, vector<nodo> &solucion);

// Obtención de la ruta
void calcularRuta(vector<nodo> &nodos, vector<nodo> &solucion);
#endif