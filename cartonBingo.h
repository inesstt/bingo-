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


typedef struct nodo {
    int numero;
    struct nodo *sig;
} tNodo;

typedef tNodo *tListaBolillas;

tCartonBingo inicializarCarton();
int buscarNumero(tCartonBingo, int, int *, int *);
int tacharNumero(tCartonBingo *, int);
int filaCompleta(tCartonBingo, int);
int filaGanadora(tCartonBingo);
int contarTachados(tCartonBingo);
void mostrarCarton(tCartonBingo);

void inicializarLista(tListaBolillas *lista);
void insertarAlFinal(tListaBolillas *lista, int numero);
void eliminarEnPos(tListaBolillas *lista, int posicion);
int obtenerEnPos(tListaBolillas lista, int posicion);
int contarElementos(tListaBolillas lista);
int buscarEnLista(tListaBolillas lista, int numero);
void visualizarElem(tListaBolillas lista);
void liberarLista(tListaBolillas *lista);


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

//lista enlazada de bolillas
void inicializarLista(tListaBolillas *lista) {
    *lista = NULL;
}

void insertarAlFinal(tListaBolillas *lista, int numero) {
    tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));
    if (nuevo != NULL) {
        nuevo->numero = numero;
        nuevo->sig = NULL;

        if (*lista == NULL) {
            *lista = nuevo;
        } else {
            tNodo *actual = *lista;
            while (actual->sig != NULL) {
                actual = actual->sig;
            }
            actual->sig = nuevo;
        }
    }
}

void eliminarEnPos(tListaBolillas *lista, int posicion) {
    if (*lista == NULL || posicion < 1) {
        return;
    }

    tNodo *actual = *lista;

    if (posicion == 1) {
        *lista = actual->sig;
        free(actual);
    } else {
        tNodo *anterior = NULL;
        int i = 1;
        while (actual != NULL && i < posicion) {
            anterior = actual;
            actual = actual->sig;
            i++;
        }

        if (actual != NULL) {
            anterior->sig = actual->sig;
            free(actual);
        }
    }
}

int obtenerEnPos(tListaBolillas lista, int posicion) {
    tNodo *actual = lista;
    int i = 1;
    while (actual != NULL && i < posicion) {
        actual = actual->sig;
        i++;
    }
    if (actual != NULL) {
        return actual->numero;
    }
    return -1; 
}

int contarElementos(tListaBolillas lista) {
    int contador = 0;
    tNodo *actual = lista;
    while (actual != NULL) {
        contador++;
        actual = actual->sig;
    }
    return contador;
}

int buscarEnLista(tListaBolillas lista, int numero) {
    tNodo *actual = lista;
    int pos = 1;
    while (actual != NULL) {
        if (actual->numero == numero) {
            return pos;
        }
        actual = actual->sig;
        pos++;
    }
    return 0; 
}

void visualizarElem(tListaBolillas lista){
    tNodo *actual = lista;
    printf("Lista de bolillas: ");
    while (actual != NULL) {
        printf("%d -> ", actual->numero);
        actual = actual->sig;
    }
    printf("NULL\n");
}

void liberarLista(tListaBolillas *lista){
    tNodo *actual = *lista;
    tNodo *siguiente;
    while (actual != NULL){
        siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }
    *lista = NULL;
}

#endif
