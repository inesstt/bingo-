#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//#include "CARTONBINGO.h"

#define MAXCOL 5
#define MAXFILA 3

typedef int tCartonBingo[MAXFILA][MAXCOL];

typedef struct {
	tCartonBingo carton;
	bool hizoLinea;
} tJugador;

typedef struct nodo{
    struct nodo * jugador1;
    struct nodo * jugador2;
}tJuego;


//prototipado
void crearJugador(tJugador *);
void jugarTurno(tJugador *, int);
void verificarEstado(tJugador *);
void mostrarGanador(tJugador);

void crearJugadores(tJuego**);
void jugarTurnoJugadores(tJuego, int);
void mostrarGanadorJugadores(tJuego, int);


void crearJugador(tJugador * pJugador) {
	
	inicializarCarton(pJugador->carton);
	pJugador->hizoLinea = false;
	
}

void crearJugadores(tJuego *  pJuego){
    pJuego->jugador1.carton = inicializarCarton();
    pJuego->jugador2.carton = inicializarCarton();
    pJuego->jugador1.hizoLinea = false;
    pJuego->jugador2.hizoLinea = false;
}

void jugarTurno(tJugador * pJugador, int pNumeroSorteado) {
	int i,
	int j;

	for (i = 0; i < MAXFILA; i++) {
		for (j = 0; j < MAXCOL; j++) {
			if (pJugador->carton[i][j] == pNumeroSorteado) {
				tacharNumero(pJugador->carton, pNumeroSorteado);
				printf("numero %d tachado\n", pNumeroSorteado);
			}
		}
	}
	
}

void jugarTurnoJugadores(tJuego * pJuego, int pNumeroSorteado){
    int i, j;

    for (i = 0; i < MAXFILA ; i++){
        for (j = 0; j < MAXCOL ; j++){
            if (pJuego->jugador1.carton[i][j] == numeroSorteado){
                tacharNumero(pJuego->jugador1.carton, pNumeroSorteado);
                printf("Numero %d tachado\n", pNumeroSorteado);
            } 
                if (pJuego->jugador2.carton[i][j] == numeroSorteado){
                    tacharNumero(pJuego->jugador2.carton, pNumeroSorteado);
                    printf("Numero %d tachado\n", pNumeroSorteado);
                }   
            
        }
    }    
            
    

}

void verificarEstado(tJugador * pJugador) {
	
	if (contarTachados(pJugador->carton) == MAXFILA) {
		pJugador->hizoLinea = true;
		mostrarGanador(*pJugador);
	}
	
}

void verificarEstadoJugadores(tJuego *pJuego){
    if  ( filaCompleta(pJuego->jugador1) == true){
        pJuego->jugador1.hizoLinea = true;
        mostrarGanador(pJuego->jugador1, 1);
    } else {
        if (filaCompleta(pJuego->jugador2) == true){
            pJuego->jugador2.hizoLinea = true;
             mostrarGanador(pJuego->jugador2, 2);
        } else {
            printf("siga jugando...\n");
        }
    }
}

void mostrarGanador(tJugador pJugador) {
	
	if (pJugador.hizoLinea) {
		printf("BINGO! ganaste la partida\n");
	}
	
}

void mostrarGanadorJugadores(tJuego pJuego, int pJugador){
    printf("BINGO! Ganador : %d\n", pJugador);

