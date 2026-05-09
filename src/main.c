#include "polinomio.h"

#include <stdio.h>
#include <stdlib.h>

int main(){

    //Probando caso 2 de ejemplo del pdf :))
    printf("Caso 1\n");

    Polinomio* p1 = crearPolinomio();
    Polinomio* p2 = crearPolinomio();

    // P1 = 3x^2 + 2x + 1
    insertarTermino(p1, 3, 2);
    insertarTermino(p1, 2, 1);
    insertarTermino(p1, 1, 0);

    //P2 = x^2 + 4 
    insertarTermino(p2, 1, 2);
    insertarTermino(p2, 4, 0);

    char* s1 = polinomioToString(p1);
    char* s2 = polinomioToString(p2);

    printf("Entrada:\n");
    printf("P1 = %s\n", s1);
    printf("P2 = %s\n\n", s2);

    Polinomio* suma = sumarPolinomios(p1, p2);

    char* resultado1 = polinomioToString(suma);

    printf("Salida esperada:\n");
    printf("4x^2+2x+5\n\n");

    printf("Salida obtenida:\n");
    printf("%s\n", resultado1);

    free(s1);
    free(s2);
    free(resultado1);

    destruirPolinomio(p1);
    destruirPolinomio(p2);
    destruirPolinomio(suma);

    printf("\n");

    //Probando caso 2 de ejemplo del pdf :))

    printf("Caso 2 (simplificacion)\n");

    Polinomio* p3 = crearPolinomio();

    printf("Entrada:\n");
    printf("Insertar 3x^2\n");

    insertarTermino(p3, 3, 2);

    printf("Insertar -3x^2\n");

    insertarTermino(p3, -3, 2);

    char* resultado2 = polinomioToString(p3);

    printf("\nSalida esperada:\n");
    printf("0\n\n");

    printf("Salida obtenida:\n");
    printf("%s\n", resultado2);

    free(resultado2);

    destruirPolinomio(p3);

    return 0;
}


