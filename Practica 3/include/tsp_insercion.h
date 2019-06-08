#ifndef TSP_INSERCION_H
#define TSP_INSERCION_H
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

//Función que lee el archivo de datos y transforma el problema en un vector de nodos
void llenaGrafo(vector<nodo>& grafo,const char fichero[]);

//Cálculo de las distancias entre ciudades
void distancia(vector<nodo> &grafo, vector<vector<double>> &distancias);

//Calculo de las tres primeras ciudades que formaran el triangulo inicial en el que insertaremos las demas
//Serán la ciudad mas al norte, la ciudad mas al este y la ciudad mas al oeste.
void trianguloInicio(vector<nodo> &grafo, vector<nodo> &solucion);

//Calculo de la distancia total de una solucion dada
double calcularDistancia(const vector<vector<double> > &distancias, const vector<int> &solucion);

//Metodo que devuelve todas las posibilidades que tenemos de insertar una ciudad en una solucion
vector<vector<int> > vecinoInsertarCiudad(const vector<vector<double> > &distancias, vector<int> &solucionInicio);

//Metodo que calcula la mejor solucion posible
void vecinoInsercion(const vector<vector<double> > &distancias, vector<int> &solucion);

//Metodo que dada una solucion, devuelve los detalles de esa solucion con coordenadas de las ciudades
void vecinoBuscarDatosCiudades(const vector<int> &solucion, vector<nodo> &ciudades, vector<nodo> &solucionC);

#endif