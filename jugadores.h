#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "cartonBingo.h"

typedef struct {
	tCartonBingo carton;
	bool hizoLinea;
} tJugador;

//prototipado
void crearJugador(tJugador *);
void jugarTurno(tJugador *, int);
void verificarEstado(tJugador *);
void mostrarGanador(tJugador);


void crearJugador(tJugador *pJugador) {
	pJugador->carton = inicializarCarton();
	pJugador->hizoLinea = false;

}

void jugarTurno(tJugador *pJugador, int pNumeroSorteado){
	if (tacharNumero(&pJugador->carton, pNumeroSorteado) != 0) {
		printf("numero %d tachado\n", pNumeroSorteado);
	}

}

void verificarEstado(tJugador *pJugador){
	if (filaGanadora(pJugador->carton) != 0) {
		pJugador->hizoLinea = true;
	}
}

void mostrarGanador(tJugador pJugador){
	if (pJugador.hizoLinea) {
		printf("BINGO! ganaste la partida\n");
	}
}

