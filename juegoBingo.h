#ifndef JUEGOBINGO_H
#define JUEGOBINGO_H

#include "tJugadores.h"

typedef struct {
    tJugador jugador1;
    tJugador jugador2;
    tListaBolillas bolillero;
} tJuego;


//prototipado
void crearJuego(tJuego *);
int sortearBolilla(tJuego *);
void jugarTurnoJugadores(tJuego *, int);
int verificarEstadoJugadores(tJuego *);
void mostrarGanadorJugadores(tJuego, int);
void jugarPartida(tJuego *);
void liberarJuego(tJuego *);


void crearJuego(tJuego * pJuego){
    int i;

    crearJugador(&pJuego->jugador1);
    crearJugador(&pJuego->jugador2);

    inicializarLista(&pJuego->bolillero);
    for (i = 1; i <= MAX; i++){
        insertarAlFinal(&pJuego->bolillero, i);
    }
}

//saca una bolilla al azar del bolillero y la devuelve (-1 si no quedan)
int sortearBolilla(tJuego * pJuego){
    int cantidad = contarElementos(pJuego->bolillero);
    int posicion;
    int numero = -1;

    if (cantidad > 0){
        posicion = 1 + rand() % cantidad;
        numero = obtenerEnPos(pJuego->bolillero, posicion);
        eliminarEnPos(&pJuego->bolillero, posicion);
    }

    return numero;
}

void jugarTurnoJugadores(tJuego * pJuego, int pNumeroSorteado){
    jugarTurno(&pJuego->jugador1, pNumeroSorteado);
    jugarTurno(&pJuego->jugador2, pNumeroSorteado);
}

//devuelve 1 o 2 si ese jugador hizo linea, 0 si nadie
int verificarEstadoJugadores(tJuego * pJuego){
    int ganador = 0;

    verificarEstado(&pJuego->jugador1);
    verificarEstado(&pJuego->jugador2);

    if (pJuego->jugador1.hizoLinea){
        ganador = 1;
    } else {
        if (pJuego->jugador2.hizoLinea){
            ganador = 2;
        }
    }

    return ganador;
}

void mostrarGanadorJugadores(tJuego pJuego, int pJugador){
    printf("BINGO! Ganador : %d\n", pJugador);

    if (pJugador == 1){
        mostrarCarton(pJuego.jugador1.carton);
    } else {
        mostrarCarton(pJuego.jugador2.carton);
    }
}

void jugarPartida(tJuego * pJuego){
    int numero;
    int ganador = 0;

    while (ganador == 0 && contarElementos(pJuego->bolillero) > 0){
        numero = sortearBolilla(pJuego);
        printf("Bolilla sorteada: %d\n", numero);

        jugarTurnoJugadores(pJuego, numero);
        ganador = verificarEstadoJugadores(pJuego);
    }

    if (ganador != 0){
        mostrarGanadorJugadores(*pJuego, ganador);
    }
}

void liberarJuego(tJuego * pJuego){
    liberarLista(&pJuego->bolillero);
}

#endif
