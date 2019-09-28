#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct {
	char *nome;
	int pontos;
	char media;
	char *cartas;
} Jogador;

void inicializarMaos(Jogador *jogador, Jogador *computador, Jogador *mesa) {
	jogador->nome = NULL;
	jogador->pontos = 0;
	jogador->media = 'A';
	jogador->cartas = (char *) malloc(sizeof(char));
	jogador->cartas[0] = '\0';

	computador->nome = NULL;
	computador->pontos = 0;
	computador->media = 'A';
	computador->cartas = (char *) malloc(sizeof(char));
	computador->cartas[0] = '\0';

	mesa->nome = NULL;
	mesa->pontos = 0;
	mesa->media = 'A';
	mesa->cartas = (char *) malloc(sizeof(char));
	mesa->cartas[0] = '\0';
}

int cartaRepetida(char carta, Jogador jogador, Jogador computador, Jogador mesa) {
	int repetido = 0;
	int i = 0;
	int tam = strlen(jogador.cartas);

	while (repetido == 0 && i < tam) {
		if (jogador.cartas[i] == carta)
			repetido++;
		i++;
	}

	i = 0;
	tam = strlen(computador.cartas);

	while (repetido == 0 && i < tam) {
		if (computador.cartas[i] == carta)
			repetido++;
		i++;
	}

	i = 0;
	tam = strlen(mesa.cartas);

	while (repetido == 0 && i < tam) {
		if (mesa.cartas[i] == carta)
			repetido++;
		i++;
	}

	return repetido;
}

char sortearCarta(Jogador jogador, Jogador computador, Jogador mesa) {
	char carta;

	do {
		carta = (rand() % 26) + 65;
	} while (cartaRepetida(carta, jogador, computador, mesa));

	return carta;
}

char puxarCartaAleatoria(Jogador *j1, Jogador j2, Jogador mesa) {
	int tam = strlen(j1->cartas);

	j1->cartas = (char *) realloc(j1->cartas, (tam + 2) * sizeof(char));
	j1->cartas[tam] = sortearCarta(*j1, j2, mesa);
	j1->cartas[tam + 1] = '\0';

	return j1->cartas[tam];
}

char puxarCarta(Jogador *j, char carta) {
	int tam = strlen(j->cartas);

	j->cartas = (char *) realloc(j->cartas, (tam + 2) * sizeof(char));
	j->cartas[tam] = carta;
	j->cartas[tam + 1] = '\0';

	return j->cartas[tam];
}

void mesaPuxarCartaAleatoria(Jogador *mesa, Jogador j1, Jogador j2) {
	printf("Carta referencia: %c\n", puxarCartaAleatoria(mesa, j1, j2));
}

void jogadorPuxarCartaAleatoria(Jogador *jogador, Jogador j, Jogador m) {
	printf("Jogador puxou a carta: %c\n", puxarCartaAleatoria(jogador, j, m));
}

void jogadorPuxarCarta(Jogador *jogador, Jogador *computador, Jogador *mesa) {
	char carta;

	do {
		printf("Escolha uma carta que ainda nao saiu: ");
		scanf(" %c", &carta);
	} while (cartaRepetida(carta, *jogador, *computador, *mesa));

	printf("Jogador puxou a carta: %c\n", puxarCarta(jogador, carta));
}

void calcularMedia(Jogador *j) {
	int tam = strlen(j->cartas);
	int media = 0;

	for (int i = 0; i < tam; i++) {
		media += j->cartas[i];
	}

	media /= tam;
	j->media = media;

	printf("Media das cartas do jogador: %c\n", j->media);
}

void calcularPontos(Jogador *j, Jogador m) {
	int novo = abs(j->media - m.cartas[strlen(m.cartas) - 1]);

	j->pontos += novo;

	printf("Jogador marcou %d pontos\n", novo);
}

void mostrarPlacar(Jogador jogador, Jogador computador, Jogador mesa) {
	printf("Jogador Cartas Media Pontos\n");
	printf("Mesa %s\n", mesa.cartas);
	printf("Jogador %s %c %d\n", jogador.cartas, jogador.media, jogador.pontos);
	printf("Computador %s %c %d\n", computador.cartas, computador.media, computador.pontos);
}

void fimDeJogo(Jogador jogador, Jogador computador, Jogador mesa) {
	printf("Fim de jogo!\n");

	if (jogador.pontos > computador.pontos)
		printf("O jogador ganhou!\n");
	else if (jogador.pontos < computador.pontos)
		printf("O computador ganhou!\n");
	else
		printf("Empate!\n");
}

void liberarMemoria(Jogador *jogador, Jogador *computador, Jogador *mesa) {
	free(jogador->nome);
	free(jogador->cartas);
	free(computador->nome);
	free(computador->cartas);
	free(mesa->nome);
	free(mesa->cartas);
}

int main() {
	Jogador jogador, computador, mesa;
	time_t t;
	srand((unsigned) time(&t));
	inicializarMaos(&jogador, &computador, &mesa);

	mesaPuxarCartaAleatoria(&mesa, jogador, computador);
	jogadorPuxarCartaAleatoria(&jogador, computador, mesa);
	calcularMedia(&jogador);
	jogadorPuxarCartaAleatoria(&computador, jogador, mesa);
	calcularMedia(&computador);
	calcularPontos(&jogador, mesa);
	calcularPontos(&computador, mesa);
	mostrarPlacar(jogador, computador, mesa);

	for (int i = 0; i < 4; i++) {
		mesaPuxarCartaAleatoria(&mesa, jogador, computador);
		jogadorPuxarCarta(&jogador, &computador, &mesa);
		calcularMedia(&jogador);
		jogadorPuxarCartaAleatoria(&computador, jogador, mesa);
		calcularMedia(&computador);
		jogadorPuxarCarta(&jogador, &computador, &mesa);
		calcularMedia(&jogador);
		jogadorPuxarCartaAleatoria(&computador, jogador, mesa);
		calcularMedia(&computador);
		calcularPontos(&jogador, mesa);
		calcularPontos(&computador, mesa);
		mostrarPlacar(jogador, computador, mesa);
	}

	fimDeJogo(jogador, computador, mesa);
	liberarMemoria(&jogador, &computador, &mesa);

	return 0;
}