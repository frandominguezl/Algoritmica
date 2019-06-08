/*
  Nora Itafti Rivas
  Miguel Ángel Posadas Arráez
  Francisco Dominguez Lorente
  David Gómez Hernández
*/

//Compilación: g++ -g matriz_traspuesta.cpp -o matriz_traspuesta

#include<iostream>
#include <chrono>
#include<stdlib.h>
#include<time.h>
using namespace std;

int ** reservar(int n){
  int **matriz;
  matriz = new int *[n];
  for(int i = 0; i<n; i++){
    matriz[i] = new int[n];
  }
  return matriz;
}

void liberar(int **& m, int n){
  for(int i=0; i<n; i++){
    delete [] m[i];
  }
  delete [] m;
}


void imprimir(int **& m, int n){
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int **  trasponer(int**& m, int n){
  //Reserva de memoria
  int ** traspuesta = reservar(n);
  //Trasponemos la matriz original(m), y volcamos el resultado en la matriz resultado
  for( int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      traspuesta[i][j] = m[j][i];
    }
  }
  //Liberamos memoria
  liberar(m, n);

  m = traspuesta;
  return m;
}


int main(int argc, char * argv[]){

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_filas>" << " <num_columnas>" << endl;
      return -1;
    }

int nfilas, ncolumnas, a;
unsigned long tejecucion;
clock_t tantes, tdespues;

nfilas = atoi(argv[1]);
ncolumnas = atoi(argv[2]);

srand(time(NULL));

if( nfilas <= ncolumnas ){
  a = ncolumnas;
}
else{
  a = nfilas;
}

//Reserva de memoria
int **matriz = reservar(a);

//Rellenamos la matriz con valores aleatorios
for(int i=0; i<nfilas; i++){
  for(int j=0; j<ncolumnas; j++){
    matriz[i][j] = rand()%10 + 1;
  }
}


//Rellenar con ceros
if( nfilas < ncolumnas ){
  for(int i=nfilas; i<ncolumnas; i++){
    for(int j=nfilas; j<ncolumnas; j++){
      matriz[i][j] = 0;
    }
  }
}
else{
  for(int i=ncolumnas; i<nfilas; i++){
    for(int j=ncolumnas; j<nfilas; j++){
      matriz[i][j] = 0;
    }
  }
}

if( a<=12 ){
  cout << "\n-----------Matriz original--------------\n";
  imprimir(matriz,a);
}

tantes = clock();
trasponer(matriz,a);
tdespues = clock();

if( a<=12 ){
  cout << "\n-----------Matriz traspuesta-------------\n";
  imprimir(matriz,a);
}


tejecucion = tdespues - tantes;

cout << a << "          " << tejecucion << endl;

liberar(matriz,a);

}
