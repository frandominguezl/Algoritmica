#include "Nodo.h"


nodo::nodo(){
    this->idnodo = 0;
    this->gradoNodo = 0;
    this->x = 0;
    this->y = 0;
}

nodo::nodo(int id, int g){
    this->idnodo = id;
    this->gradoNodo = g;
 }


void nodo::setID(int id){
    this->idnodo = id;
}

void nodo::setGrado(int grado){
    this->gradoNodo = grado;
}

int nodo::getIDNodo(){
    return idnodo;
}

int nodo::getGradoNodo(){
    return gradoNodo;
}

void nodo::setCiudad(double x, double y){
    this->x = x;
    this->y = y;
}

double nodo::getX(){return this->x;}

double nodo::getY(){return this->y;}