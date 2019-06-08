/* (C) Programmed by:
    Francisco Dominguez Lorente
    David Gómez Hernandez
    Nora Itafti Rivas
    Miguel Ángel Posadas Arráez
Asignatura Algoritmica (ALG)
practica 2: Divide y Venceras
EJERCICIO Serie unimodal de números.
Sea un vector v de números de tamaño n, todos distintos, de forma que existe un ı́ndice p (que no es
ni el primero ni el último) tal que a la izquierda de p los números están ordenados de forma creciente
y a la derecha de p están ordenados de forma decreciente; es decir ∀i, j ≤ p, i < j ⇒ v[i] < v[j] y
∀i, j ≥ p, i < j ⇒ v[i] > v[j] (de forma que el máximo se encuentra en la posición p). Diseñe un algoritmo
que permita determinar p.
*/

//compilar g++  -o serieunimodal serieunimodal.cpp 
// Ejecutar el script tras compilar

#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

//generador de ejemplos para el problema de la serie unimodal de números. Se genera un índice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese índice, a los índices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los índices mayores que p se le asignan valores en orden decreciente (n-2, n-1,...,p

double uniforme() //Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C.
{
    double u;
    u = (double) rand();
    u = u/(double)(RAND_MAX+1.0);
    return u;
}

void generador (vector<int>v,int n) {
    srand(time(0));
    double u=uniforme();
    int p=1+(int)((n-2)*u);
    v[p]=n-1;
    for (int i=0; i<p; i++) v[i]=i;
    for (int i=p+1; i<n; i++) v[i]=n-1-i+p;
}



int unimodaldyv(vector<int>v,int inicio,int fin) {
    int tamanio=fin-inicio+1;
    if(tamanio>2) {
        int p=(tamanio/2)+inicio;
        int x=v[p-1];
        int y=v[p+1];
        int z=v[p];
        if(z>x && z>y) return z; //si lo encuentra en la primera iteracion
        else {
            if(z<y) {//coger la segunda mitad desde z
                return unimodaldyv(v,p+1,fin);
            }
            if(z>y) {//coger la primera mitad desde z
                return unimodaldyv(v,inicio,p);
            }
        }
    }
    else {
        if(tamanio==2) { //si quedan 2 elementos, coje el mayor
            if(v[inicio]>v[fin]) return v[inicio];
            else return v[fin];
        }
        else //v.size()==1 si queda uno, lo devuelve
            return v[inicio];
    }
}


int main(int argc, char * argv[])
{
  	if (argc <= 2)
    {
    	cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
    	cerr<<argv[0]<<" NombreFicheroSalida tamCaso1 tamCaso2 ... tamCasoN\n\n";
      
      return -1;
    }
    ofstream fsalida;
    fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
    for(int argumento=3; argumento<argc; argumento++){
		int n = atoi(argv[argumento]);
        vector<int>t(n);
        generador(t,n);
        chrono::high_resolution_clock::time_point t_antes = chrono::high_resolution_clock::now();
        unimodaldyv(t,0,n-1);//calcula de forma bruta el maximo en un vector unimodal
        chrono::high_resolution_clock::time_point t_despues = chrono::high_resolution_clock::now();
  		unsigned long t_ejecucion = chrono::duration_cast<std::chrono::microseconds>(t_despues - t_antes).count();
        cout <<"Para n igual a "<<n<< " tarda " << t_ejecucion << "\n";
        fsalida<<n<<" "<<t_ejecucion<<endl;
    }
    fsalida.close();
    
    return 0;



}