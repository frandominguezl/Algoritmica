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
void llenaGrafo(vector<nodo> &grafo,const char fichero[]){
   ifstream f(fichero);
    double valor = 0.0;
    double x,y;
    int n = 0;
    nodo ciudad;

    if (f){
        while(f >> valor >> x >> y){
            ciudad.setID(valor);
            ciudad.setCiudad(x,y);

            grafo.push_back(ciudad);
        }
    }else
		cout << "Error en la lectura del archivo"<<endl;

    f.close();
}

//Cálculo de las distancias entre ciudades
void distancia(vector<nodo> &grafo, vector<vector<double>> &distancias){
    distancias.resize(grafo.size());
	//Bucle externo que itera sobre la ciudad en la que se calcula la distancia
	//Para calcular la distancia de esa ciudad con el resto de ellas
    for(unsigned i = 0; i < distancias.size();i++){
        distancias[i].resize(grafo.size());
        //Bucle interno que itera sobre las ciudades almacenadas para calcular la distancia respecto a la del bucle externo
        for(unsigned j = 0; j< distancias[i].size();j++){
            //Fórmula del calculo de la distancia entre 2 puntos de dos dimensiones (x,y), se almacena en una matriz bidimensional
            distancias[i][j] = sqrt(pow(grafo[j].getX() - grafo[i].getX(),2) + pow((grafo[j].getY()) - (grafo[i].getY()),2));
        }
    }
}

//Calculo de las tres primeras ciudades que formaran el triangulo inicial en el que insertaremos las demas
//Serán la ciudad mas al norte, la ciudad mas al este y la ciudad mas al oeste.

void trianguloInicio(vector<nodo> &grafo, vector<nodo> &solucion){
	nodo norte, oeste, este;
	norte = grafo[grafo.size()/2];
	oeste = grafo[grafo.size()/2];
	este = grafo[grafo.size()/2];

	for(unsigned i = 0; i < grafo.size(); i++){
		if(grafo[i].getY() > norte.getY()){
			norte = grafo[i];
		}

		 if(grafo[i].getX() < oeste.getX()){
			oeste = grafo[i];
		}

		 if(grafo[i].getX() > este.getX()){
			este = grafo[i];
		}
	}

	solucion.push_back(norte);
	solucion.push_back(oeste);
	solucion.push_back(este);
}

//Calculo de la distancia total de una solucion dada
double calcularDistancia(const vector<vector<double> > &distancias, const vector<int> &solucion){

	double distancia = 0;

	for (unsigned i = 0; i < (solucion.size() - 1); i++){
		double aux = 0;
		aux = distancias[solucion[i]-1][solucion[i+1]-1];
		distancia = distancia + aux;
	}

	return distancia;

}

//Metodo que devuelve todas las posibilidades que tenemos de insertar una ciudad en una solucion
vector<vector<int> > vecinoInsertarCiudad(const vector<vector<double> > &distancias, vector<int> &solucionInicio){
	bool visitado[distancias.size()] = {false};
	unsigned totalCiudades = distancias.size();

	//Vector con todas las posibilidades
	vector<vector<int> > posiblesSoluc;

	//Marco como visitadas las ciudades que estan en la solucion de inicio
	for(unsigned i = 0; i < solucionInicio.size(); i++){

		visitado[solucionInicio[i]-1] = true;
	}

	//Bucle externo que selecciona una a una las ciudades no visitadas

		for(unsigned i = 0; i < totalCiudades; i++){
			if (visitado[i] == false){
				int ciudadSeleccionada = i;
				
				//Bucle interno que crea todas las posibles soluciones con la ciudad seleccionada y las añade al vector de soluciones posibles
				for(unsigned j = 1; j <= solucionInicio.size(); j++){
					vector<int> aux = solucionInicio;
					aux.insert(aux.begin()+j, ciudadSeleccionada + 1);
					posiblesSoluc.push_back(aux);
				}

			}
		}

	return posiblesSoluc;

}

//Metodo que calcula la mejor solucion posible
void vecinoInsercion(const vector<vector<double> > &distancias, vector<int> &solucion){
	
	//Cantidad de ciudades que todavia no se han añadido a la solucion
	int ciudadesPorExplorar = distancias.size() - solucion.size();

	vector<vector<int> > posiblesSoluc;

	vector<int> mejorSolucionTemp = solucion;

	while(ciudadesPorExplorar != 0){

		//Llamada a la funcion que crea todas la posibles soluciones con la cantidad de ciudades que nos quedan
		posiblesSoluc = vecinoInsertarCiudad(distancias, mejorSolucionTemp);

		double minimoDist = 999999999;

		vector<int> solucionMejor;

		//Dadas todas las posibilidades de añadir una ciudad obtenidas anteriormente, calculamos todas las distancias de éstas,
		//y elegimos la que tenga menor distancia.
		for(unsigned i = 0; i < posiblesSoluc.size(); i++){
			double aux = calcularDistancia(distancias, posiblesSoluc[i]);
			if (aux < minimoDist){
				solucionMejor = posiblesSoluc[i];
				minimoDist = aux;
			}
		}

		mejorSolucionTemp = solucionMejor;

		//Continuamos hasta que no queden ciudades por explorar.
		ciudadesPorExplorar--;
	}

	solucion = mejorSolucionTemp;
}

//Metodo que dada una solucion, devuelve los detalles de esa solucion con coordenadas de las ciudades
void vecinoBuscarDatosCiudades(const vector<int> &solucion, vector<nodo> &ciudades, vector<nodo> &solucionC){
	for(unsigned i = 0; i < solucion.size(); i++){
		solucionC.push_back(ciudades[solucion[i]-1]);
	}

	//Añado la primera ciudad al final, a la que hay volver
	solucionC.push_back(solucionC[0]);
}


