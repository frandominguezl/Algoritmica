#include "Grafo.h"
#include "tsp_insercion.h"
#include "tsp_cercania.h"
#include "tsp_heuristica.h"
#include <iostream> 

using namespace std;

int main(int argc, char* argv[]){

	int opcion;
	cout<<"Elije una opción a ejecutar: "<<endl; 
	cout<<"	1.- tsp por inserción"<<endl;
	cout<<"	2.- tsp por cercanía"<<endl;
	cout<<"	3.- tsp por heurística"<<endl;
	cout<<"	4.- recubrimiento de un grafo"<<endl;
	cin>>opcion;

	switch(opcion){
		case 1:
		{
			cout<<"Realizando el tsp por inserción (fichero ulysses22.tsp)"<<endl<<endl;
			vector<nodo> ciudades;
			vector<nodo> solucionC;
			vector<int> solucion;
			vector<vector<double> > D;
			double total = 0;

			llenaGrafo(ciudades, argv[1]);
			distancia(ciudades, D);
			trianguloInicio(ciudades, solucionC);

			//Añado a la solucion las tres primeras ciudades escogidas
			for(unsigned i = 0; i < solucionC.size(); i++){
				solucion.push_back(solucionC[i].getIDNodo());
			}

			solucionC.clear();

			high_resolution_clock::time_point tantes, tdespues;
			duration<double> transcurrido;
			tantes = high_resolution_clock::now();
			//Calculo la mejor solucion
			vecinoInsercion(D, solucion);
			tdespues = high_resolution_clock::now();
			transcurrido = duration_cast<duration<double>>(tdespues-tantes);
			//Calculo la distancia de mi solucion
			total = calcularDistancia(D, solucion);
			vecinoBuscarDatosCiudades(solucion, ciudades, solucionC);
			for(unsigned i = 0; i < solucionC.size(); i++)
				cout << solucionC[i].getIDNodo() << "\t" << solucionC[i].getX() << "\t" << solucionC[i].getY() << endl;

			cout << endl <<"Distancia: "<< total << endl;
			cout << endl << "Transcurrido: " << transcurrido.count() << endl;
		

		return 0;
		
		break;
		}
		case 2:
		{
			cout<<"Realizando el tsp por cercanía (fichero ulysses22.tsp)"<<endl<<endl;
			vector<nodo> nodos, solucioncercania;
			high_resolution_clock::time_point tantes, tdespues;
			duration<double> transcurrido;

			nodos = llenaGrafo_cercania(argv[1]);

			tantes = high_resolution_clock::now();
			calcularRuta(nodos, solucioncercania);
			tdespues = high_resolution_clock::now();

			transcurrido = duration_cast<duration<double>>(tdespues-tantes);

			for(int i = 0; i < (int) solucioncercania.size(); i++)
				cout << solucioncercania[i].getIDNodo() << " " << solucioncercania[i].getX() << " " << solucioncercania[i].getY() << endl;

			cout << endl << calcularDistanciaNodos(solucioncercania) << endl;

			cout << endl << "Transcurrido: " << transcurrido.count() << endl;

			return 0;
		break;
		}
		
		case 3:
		{
			cout<<"Realizando el tsp por heurística (fichero ulysses22.tsp)"<<endl<<endl;
			/*
			Aquí se muestra la funcionalidad del algoritmo 2-opt
			*/
			cout << "Comienzo" << endl;

			vector<nodo> camino, camino_optimo;

			cout << "Rellenando grafo..." ;
			camino = llenaGrafo_2opt(argv[1]);
			cout << "Grafo rellenado" << endl;

			cout << "Dimension del grafo: " << camino.size() << endl;

			cout << "\n----Camino original----\n\n";

			for( unsigned i=0; i<camino.size(); i++){
			/*cout << "(" << camino[i].getX() << ", " << camino[i].getY() << ")" << "-->";
			if( i == camino.size() -1)
			cout << "(" << camino[i].getX() << ", " << camino[i].getY() << ")" ;
			*/
			cout << camino[i].getIDNodo() << " " << camino[i].getX() << " " << camino[i].getY() << endl;
			}

			camino_optimo = TwoOpt(camino, 100);

			cout << "\n\n----Camino modificado----\n\n";

			for( unsigned i=0; i<camino.size(); i++){
			/*
			cout << "(" << camino_optimo[i].getX() << ", " << camino_optimo[i].getY() << ")" << "-->" ;
			if( i == camino.size() -1)
			cout << "(" << camino_optimo[i].getX() << ", " << camino_optimo[i].getY() << ")" ;*
			*/
			cout << camino_optimo[i].getIDNodo() << " " << camino_optimo[i].getX() << " " << camino_optimo[i].getY() << endl;

			}
			cout << endl << endl;

			cout << "\n\n--------FIN---------";
			cout << endl;

			return  0;

			break;
		}

		case 4:
		{
			cout<<"Recubrimiento del grafo"<<endl;
			cout<<"0 -- 1 -- 3 -- 4 -- 5 -- 6"<<endl;
			cout<<"|						 "<<endl;
			cout<<"2"<<endl;
			cout<<endl;

			Grafo grafo(6);
			grafo.aniadirArista(0,1);
			grafo.aniadirArista(0,2);
			grafo.aniadirArista(1,3);
			grafo.aniadirArista(3,4);
			grafo.aniadirArista(4,5);
			grafo.aniadirArista(5,6);


			vector<int>nodoscubiertos =	grafo.recubrirGrafo();
			cout<<"Los nodos cubiertos son"<<endl;
			for(int i=0;i<nodoscubiertos.size();i++){
				cout<<nodoscubiertos[i]<<" ";
			}
			cout<<endl;
		break;
		}

	

	};
}
