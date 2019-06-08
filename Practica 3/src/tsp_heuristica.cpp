#include "tsp_heuristica.h"


//Función que lee el archivo de datos y transforma el problema en un vector de nodos
vector<nodo> llenaGrafo_2opt(const char  fichero[]){
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

int Coste(vector<nodo> camino){
  double distancia = 0.0, x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;
	for(int i = 1; i < (int) camino.size(); i++){
		x1 = camino[i-1].getX();
		y1 = camino[i-1].getY();
		x2 = camino[i].getX();
		y2 = camino[i].getY();

		distancia += sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}
  x1 = camino[0].getX();
  y1 = camino[0].getY();
  x2 = camino[camino.size() - 1].getX();
  y2 = camino[camino.size() - 1].getY();
	return distancia + sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void Swap( vector<nodo> & nuevo_camino,vector<nodo> camino, int i, int k )
{
      int tamanio = camino.size();

    // 1. copiamos desde camino[0] hasta camino[i-1] y lo añadimos a la nuevo_camino
        for ( int c=0; c <= i - 1 ; c++ )
    {
        nuevo_camino[c] = camino[c];
    }
    // 2. copiamos desde camino[i] hasta camino[k] y lo añadimos a nuevo_camino
    int cont = 0;
    for ( int c = i; c <= k; c++ )
    {
        nuevo_camino[c] = camino[k - cont];
        cont++;

    }
    // 3. copiamos desde camino[k+1] hasta el final y lo añadimos a nuevo_camino
    for ( int c = k + 1 ; c < tamanio; c++)
    {
        nuevo_camino[c] = camino[c];
    }
}

vector<nodo> TwoOpt(vector<nodo> camino, int max_vueltas)
{
    // repeat until no improvement is made
    bool mejora = true;
    int limite = 0;

    double distancia = Coste(camino);
    vector<nodo> nuevo_camino;
    nuevo_camino = camino;


    while ( mejora && limite < max_vueltas )
    {
        double distancia_mejorada ;
        mejora = false;

        for ( int i = 0; i < camino.size() - 1; i++ )
        {
            for ( int k = i+1; k < camino.size(); k++)
            {
            //  cout <<"Antes swap" << k << endl;
                Swap( nuevo_camino, camino, i, k );
              //  cout <<"Despues swap" << endl;

                distancia_mejorada = Coste(nuevo_camino);

                if ( distancia_mejorada < distancia )
                {
                    // Improvement found so reset
                    mejora = true;
                    camino = nuevo_camino;
                    distancia = distancia_mejorada;
                }
            }
        }
        limite++;
    }

    return camino;
}
