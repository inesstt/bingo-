#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILAS 3
#define COLUMNAS 5
#define CASILLAS 15     
#define MAX 50       

typedef char tString[50];

typedef struct {
    int numero[FILAS][COLUMNAS];
    int tachado[FILAS][COLUMNAS];     
} tCartonBingo;

tCartonBingo inicializarCarton();
int buscarNumero(tCartonBingo, int, int *, int *);
int tacharNumero(tCartonBingo *, int);
int filaCompleta(tCartonBingo, int);
int filaGanadora(tCartonBingo);
int contarTachados(tCartonBingo);
void mostrarCarton(tCartonBingo);

tCartonBingo inicializarCarton(){
    tCartonBingo carton;
    int i, j;
    int nuevo, fila, columna;
    int lim_inferior = 1;
    int lim_superior = MAX;

    for(i=0; i<FILAS; i++){
        for(j=0; j<COLUMNAS; j++){
            carton.numero[i][j] = 0;
            carton.tachado[i][j] = 0;
        }
    }

    for(i=0; i<FILAS; i++){
        for(j=0; j<COLUMNAS; j++){
            do{
                nuevo = lim_inferior + rand() % (lim_superior + 1 - lim_inferior);
            }while(buscarNumero(carton, nuevo, &fila, &columna));

            carton.numero[i][j] = nuevo;
        }
    }

    return carton;
}

int buscarNumero(tCartonBingo pCarton, int pNumero, int *pFila, int *pColumna) {
    int i = 0;
    int j;
    int encontrado = 0;

    while(i < FILAS && !encontrado){
        j = 0;
        while(j < COLUMNAS && !encontrado){
            if(pCarton.numero[i][j] == pNumero){
                encontrado = 1;
                *pFila = i;
                *pColumna = j;
            }
            j++;
        }
        i++;
    }

    return encontrado;
}

int tacharNumero(tCartonBingo *pCarton, int pNumero){
    int fila, columna;
    int resultado = 0;

    if(buscarNumero(*pCarton, pNumero, &fila, &columna)){
        pCarton->tachado[fila][columna] = 1;
        resultado = 1;

        if(contarTachados(*pCarton) >= COLUMNAS && filaGanadora(*pCarton) != 0){
            resultado = 2;
        }
    }

    return resultado;
}

int filaCompleta(tCartonBingo pCarton, int pFila){
    int j;
    int completa = 1;

    for(j=0; j<COLUMNAS; j++){
        if(pCarton.tachado[pFila][j] == 0){
            completa = 0;
        }
    }

    return completa;
}

int filaGanadora(tCartonBingo pCarton){
    int i = 0;
    int ganadora = 0;

    while(i < FILAS && ganadora == 0){
        if(filaCompleta(pCarton, i)){
            ganadora = i + 1;
        }
        i++;
    }

    return ganadora;
}

int contarTachados(tCartonBingo pCarton){
    int i, j;
    int cantidad = 0;

    for(i=0; i<FILAS; i++){
        for(j=0; j<COLUMNAS; j++){
            cantidad = cantidad + pCarton.tachado[i][j];
        }
    }

    return cantidad;
}

void mostrarCarton(tCartonBingo pCarton){
    int i, j;

    for(i=0; i<FILAS; i++){
        printf("+");
        for(j=0; j<COLUMNAS; j++){
            printf("-------+");
        }
        printf("\n|");

        for(j=0; j<COLUMNAS; j++){
            if(pCarton.tachado[i][j]){
                printf(" [%2d]  |", pCarton.numero[i][j]);
            }else{
                printf("  %2d   |", pCarton.numero[i][j]);
            }
        }
        printf("\n");
    }

    printf("+");
    for(j=0; j<COLUMNAS; j++){
        printf("-------+");
    }
    printf("\n");
}
