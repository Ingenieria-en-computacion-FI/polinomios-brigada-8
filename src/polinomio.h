#ifndef __POLINOMIO_H__
#define __POLINOMIO_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct Termino{
    float coeficiente;
    int exponente;
} Term;

typedef struct Nodo {
    Term termino;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* cabeza;
    Nodo* cola;
} Polinomio;


Nodo* crearNodo(float coef, int exp);
void insertarNodoOrdenado(Polinomio* p, Nodo* nuevo);
void eliminarNodo(Polinomio* p, int exp);
Polinomio* crearPolinomio();
void insertarTermino(Polinomio* p, float coef, int exp);
float evaluarPolinomio(Polinomio* p, float x);
Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2);
Polinomio* multiplicarPolinomios(Polinomio* p1,Polinomio* p2);
char* polinomioToString(Polinomio* p);
void destruirPolinomio(Polinomio* p);


#endif
