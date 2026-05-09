#include "polinomio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Funciones de Lista :)))

Nodo* crearNodo(float coef, int exp){
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if(nuevo == NULL)
        return NULL;
    nuevo->termino.coeficiente = coef;
    nuevo->termino.exponente = exp;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;

    return nuevo;
}

void insertarNodoOrdenado(Polinomio* p, Nodo* nuevo){
    if(p == NULL || nuevo == NULL)
        return;
    //Lista vacía
    if(p->cabeza == NULL){
        p->cabeza = nuevo;
        p->cola = nuevo;
        return;
    }

    Nodo* actual = p->cabeza;

    //Para buscar una posición
    while(actual != NULL &&
          actual->termino.exponente >
          nuevo->termino.exponente){
        actual = actual->siguiente;
    }

    //Para insertar al final
    if(actual == NULL){
        nuevo->anterior = p->cola;
        p->cola->siguiente = nuevo;
        p->cola = nuevo;

        return;
    }

    //Insertar al inicio
    if(actual == p->cabeza){
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
        return;
    }

    //Insertar en medio
    nuevo->siguiente = actual;
    nuevo->anterior = actual->anterior;
    actual->anterior->siguiente = nuevo;
    actual->anterior = nuevo;
}

void eliminarNodo(Polinomio* p, int exp){
    if(p == NULL)
        return;
    Nodo* actual = p->cabeza;
    while(actual != NULL &&
          actual->termino.exponente != exp){
        actual = actual->siguiente;
    }
    if(actual == NULL)
        return;
    // Sólo un nodo
    if(actual == p->cabeza && actual == p->cola){
        p->cabeza = NULL;
        p->cola = NULL;
    }
    
    else if(actual == p->cabeza){
        p->cabeza = actual->siguiente;
        p->cabeza->anterior = NULL;
    }

    else if(actual == p->cola){
        p->cola = actual->anterior;
        p->cola->siguiente = NULL;
    }

    else{
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }

    free(actual);
}

// Funciones de polinomio :)))

Polinomio* crearPolinomio(){
    Polinomio* p = (Polinomio*) malloc(sizeof(Polinomio));
    if(p == NULL)
        return NULL;
    p->cabeza = NULL;
    p->cola = NULL;
    return p;
}

void insertarTermino(Polinomio* p, float coef, int exp){
    if(p == NULL || coef == 0)
        return;
    Nodo* actual = p->cabeza;
    
    //Aquí se buscan los términos semejantes
    while(actual != NULL){
        if(actual->termino.exponente == exp){
            actual->termino.coeficiente += coef;
            if(actual->termino.coeficiente == 0){
                eliminarNodo(p, exp);
            }
            return;
        }
        actual = actual->siguiente;
    }
    Nodo* nuevo = crearNodo(coef, exp);
    insertarNodoOrdenado(p, nuevo);
}

float evaluarPolinomio(Polinomio* p,float x){
    if(p == NULL)
        return 0;
    float resultado = 0;
    Nodo* actual = p->cabeza;
    while(actual != NULL){
        resultado +=
            actual->termino.coeficiente *pow(x, actual->termino.exponente);
        actual = actual->siguiente;
    }
    return resultado;
}

Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2){
    Polinomio* resultado = crearPolinomio();
    Nodo* actual;
    actual = p1->cabeza;
    while(actual != NULL){
        insertarTermino(resultado, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }

    actual = p2->cabeza;
    while(actual != NULL){
        insertarTermino(resultado, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }
    return resultado;
}

Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2){
    Polinomio* resultado = crearPolinomio();
    Nodo* a1 = p1->cabeza;
    while(a1 != NULL){
        Nodo* a2 = p2->cabeza;
        while(a2 != NULL){
            float coef = a1->termino.coeficiente * a2->termino.coeficiente;
            int exp = a1->termino.exponente + a2->termino.exponente;
            insertarTermino(resultado, coef, exp);
            a2 = a2->siguiente;
        }
        a1 = a1->siguiente;
    }
    return resultado;
}

char* polinomioToString(Polinomio* p){
    if(p == NULL)
        return NULL;
    if(p->cabeza == NULL){
        char* vacio = (char*) malloc(2);
        strcpy(vacio, "0");
        return vacio;
    }
    char* cadena = (char*) malloc(1024);
    cadena[0] = '\0';
    Nodo* actual = p->cabeza;
    int primero = 1;
    while(actual != NULL){
        float c = actual->termino.coeficiente;
        int e = actual->termino.exponente;
        if(c != 0){
            char termino[100];
            termino[0] = '\0';
            if(!primero){
                if(c > 0)
                    strcat(cadena, "+");
            }
            if(c < 0)
                strcat(cadena, "-");
            float absCoef = fabs(c);
            if(e == 0){
                if(absCoef == (int)absCoef)
                    sprintf(termino, "%d", (int)absCoef);
                else
                    sprintf(termino, "%.2f", absCoef);
            }

            else if(e == 1){
                if(absCoef == 1){
                    sprintf(termino, "x");
                }
                else{
                    if(absCoef == (int)absCoef)
                        sprintf(termino, "%dx", (int)absCoef);
                    else
                        sprintf(termino, "%.2fx", absCoef);
                }
            }
        
            else{

                if(absCoef == 1){
                    sprintf(termino, "x^%d", e);
                }
                else{
                    if(absCoef == (int)absCoef)
                        sprintf(termino, "%dx^%d", (int)absCoef, e);
                    else
                        sprintf(termino, "%.2fx^%d", absCoef, e);
                }
            }
            strcat(cadena, termino);
            primero = 0;
        }
        actual = actual->siguiente;
    }
    return cadena;
}

void destruirPolinomio(Polinomio* p){
    if(p == NULL)
        return;
    Nodo* actual = p->cabeza;
    while(actual != NULL){
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    free(p);
}
