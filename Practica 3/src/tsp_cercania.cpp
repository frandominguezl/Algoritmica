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
vector<nodo> llenaGrafo_cercania(const char fichero[]){
    ifstream f(fichero);
    double valor = 0.0;
    double x,y;
    nodo ciudad;
    vector<nodo> res;

    if (f.is_open()){

        while(f >> valor >> x >> y){
            ciudad.setID(valor);
            ciudad.setCiudad(x,y);

            res.push_back(ciudad);
        }

        f.close();
    }

    else{
    	cout << "Error en la lectura del archivo" << endl;
    }
  
    return res;
}

// Calcula la distancia de un vector de nodos
double calcularDistanciaNodos(vector<nodo> &nodos){
	double distancia = 0.0, x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;

	for(int i = 1; i < (int) nodos.size(); i++){
		x1 = nodos[i-1].getX();
		y1 = nodos[i-1].getY();
		x2 = nodos[i].getX();
		y2 = nodos[i].getY();

		distancia += sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
	}

	return distancia;
}

// Selección del siguiente nodo a visitar
void seleccionarNodo(vector<nodo> &nodos, vector<nodo> &solucion){
	nodo nodo_actual;
	vector<nodo> nodos_aux;
	vector<vector<double>> distancias;
	double min_distancia = 999999999;
	int indice_nodo = 0;

	for(int i = 0; i < (int) nodos.size(); i++){
		nodo_actual = nodos[i];
		nodos_aux = solucion;
		nodos_aux.push_back(nodo_actual);

		double d = calcularDistanciaNodos(nodos_aux);

		if(d < min_distancia){
			min_distancia = d;
			indice_nodo = i;
		}

		nodos_aux.clear();
	}

	solucion.push_back(nodos[indice_nodo]);
	nodos.erase(nodos.begin() + indice_nodo);
}

// Obtención de la ruta
void calcularRuta(vector<nodo> &nodos, vector<nodo> &solucion){
	solucion.push_back(nodos.front());
	nodos.erase(nodos.begin());

	while(nodos.size()){
		seleccionarNodo(nodos, solucion);
	}
}

/*int main(int argc, char* argv[]){

	vector<nodo> nodos, solucion;
	llenaGrafo_cercania(nodos, argv[1]);
	calcularRuta(nodos, solucion);

	for(int i = 0; i < (int) solucion.size(); i++)
		cout << solucion[i].getIDNodo() << " " << solucion[i].getX() << " " << solucion[i].getY() << endl;

	cout << endl << calcularDistanciaNodos(solucion) << endl;

	return 0;
}*/