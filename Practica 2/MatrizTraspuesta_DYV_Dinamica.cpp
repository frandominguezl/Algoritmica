/* Autores
	Francisco Domínguez Lorente
	Nora Itafti Rivas
	David Gómez Hernández
	Miguel Ángel Posadas Arráez
*/

#include <iostream>

using namespace std;

const int MAX = 4;

void trasponerDyV(int **m,int f,int c, int fInicio, int fFin, int cInicio, int cFin);
void intercambiar (int **m,int f, int c,int fIniA, int cIniA, int fIniB, int cIniB, int dimen);
void imprimir(int **m, int n);

void trasponerDyV(int **m,int f,int c, int fInicio, int fFin, int cInicio, int cFin){
	if(fInicio < fFin){
		int fMedio = (fInicio+fFin)/2;
		int cMedio = (cInicio+cFin)/2;

		trasponerDyV(m,f,c, fInicio, fMedio, cInicio, cMedio);
		trasponerDyV(m,f,c, fInicio, fMedio, cMedio+1, cFin);
		trasponerDyV(m,f,c, fMedio+1, fFin, cInicio, cMedio);
		trasponerDyV(m,f,c, fMedio+1, fFin, cMedio+1, cFin);

		intercambiar(m,f,c, fMedio+1, cInicio, fInicio, cMedio+1, fFin-fMedio);
	}
}

void intercambiar (int **m,int f, int c,int fIniA, int cIniA, int fIniB, int cIniB, int dimen){
	for (int i=0; i<=dimen-1; i++){
		for (int j=0; j<=dimen-1; j++) {
			int aux = m[fIniA+i][cIniA+j];
			m[fIniA+i][cIniA+j] = m[fIniB+i][cIniB+j];
			m[fIniB+i][cIniB+j] = aux;
		}
	}
}


void imprimir(int **m, int n){
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int main(int argc, char * argv[]){

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_filas>" << " <num_columnas>" << endl;
      return -1;
    }

int nfilas, ncolumnas, a;
int **m;
unsigned long tejecucion;
clock_t tantes, tdespues;

nfilas = atoi(argv[1]);
ncolumnas = atoi(argv[2]);


if( nfilas <= ncolumnas ){
  a = ncolumnas;
}
else{
  a = nfilas;
}

//Reserva de memoria
int **matriz;
matriz = new int *[a];
for(int i = 0; i<a; i++){
  matriz[i] = new int[a];
}



for(int i=0; i<nfilas; i++){
  for(int j=0; j<ncolumnas; j++){
	matriz[i][j] = rand()%10;
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
else if(nfilas > ncolumnas){
  for(int i=ncolumnas; i<nfilas; i++){
    for(int j=ncolumnas; j<nfilas; j++){
      matriz[i][j] = 0;
    }
  }
}

imprimir(matriz,a);

cout << "Traspuesta\n";


tantes = clock();
trasponerDyV(matriz,a,a, 0, a-1, 0, a-1);
tdespues = clock();


imprimir(matriz,a);

tejecucion = tdespues - tantes;

cout << tejecucion << " (us)" << endl;

}