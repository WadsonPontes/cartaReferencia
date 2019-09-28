#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

	computador->nome = (char *) malloc(11 * sizeof(char));
	strcpy(computador->nome, "Computador");
	computador->pontos = 0;
	computador->media = 'A';
	computador->cartas = (char *) malloc(sizeof(char));
	computador->cartas[0] = '\0';

	mesa->nome = (char *) malloc(5 * sizeof(char));
	strcpy(mesa->nome, "Mesa");
	mesa->pontos = 0;
	mesa->media = 'A';
	mesa->cartas = (char *) malloc(sizeof(char));
	mesa->cartas[0] = '\0';
}

void perdirNome(Jogador *jogador) {
	long unsigned int tam;

	printf("Nome: ");
	getline(&jogador->nome, &tam, stdin);
	jogador->nome[strlen(jogador->nome) - 1] = '\0';

	getchar();
}

int cartaRepetida(char carta, Jogador jogador, Jogador computador, Jogador mesa) {
	int repetido = 0;
	int i = 0;
	int tam = strlen(jogador.cartas);
	carta = toupper(carta);

	if (carta < 'A' || carta > 'Z')
		repetido++;

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

void imprimirCartasDisponiveis(Jogador jogador, Jogador computador, Jogador mesa) {
	printf("Cartas disponiveis: ");

	for (int i = 0; i < 26; i++) {
		if (cartaRepetida(65 + i, jogador, computador, mesa) == 0)
			printf(" %c", 65 + i);
	}
	printf("\n");
}

void imprimirIntroducao() {
	printf("A cada turno coloca-se uma carta referencia na mesa.\n");
	printf("Cada jogador escolhe uma carta disponivel.\n");
	printf("Calcula-se a media das cartas do jogador.\n");
	printf("Pontua-se com a distancia da carta referencia para sua media.\n");
	printf("Ganha quem tiver mais pontos.\n");
	getchar();
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
	j->cartas[tam] = toupper(carta);
	j->cartas[tam + 1] = '\0';

	return j->cartas[tam];
}

void mesaPuxarCartaAleatoria(Jogador *mesa, Jogador j1, Jogador j2) {
	printf("Carta referencia: %c\n", puxarCartaAleatoria(mesa, j1, j2));
	getchar();
}

void jogadorPuxarCartaAleatoria(Jogador *jogador, Jogador j, Jogador m) {
	printf("%s puxou a carta: %c\n", jogador->nome, puxarCartaAleatoria(jogador, j, m));
	getchar();
}

void jogadorPuxarCarta(Jogador *jogador, Jogador *computador, Jogador *mesa) {
	char carta;

	do {
		imprimirCartasDisponiveis(*jogador, *computador, *mesa);
		printf("Escolha uma carta disponivel: ");
		scanf(" %c", &carta);
	} while (cartaRepetida(carta, *jogador, *computador, *mesa));

	printf("%s puxou a carta: %c\n", jogador->nome, puxarCarta(jogador, carta));
	getchar();
	getchar();
}

void calcularMedia(Jogador *j) {
	int tam = strlen(j->cartas);
	int media = 0;

	for (int i = 0; i < tam; i++) {
		media += j->cartas[i];
	}

	media /= tam;
	j->media = media;

	printf("Media das cartas de %s: %c\n", j->nome, j->media);
	getchar();
}

void calcularPontos(Jogador *j, Jogador m) {
	int novo = abs(j->media - m.cartas[strlen(m.cartas) - 1]);

	j->pontos += novo;

	printf("%s marcou %d pontos\n", j->nome, novo);
	getchar();
}

void mostrarPlacar(Jogador jogador, Jogador computador, Jogador mesa) {
	printf("-------------------PLACAR----------------------\n");
	printf("Nome%-12s Cartas%-4s Media Pontos\n", "", "");
	printf("%-16s %-10s\n", mesa.nome, mesa.cartas);
	printf("%-16s %-10s %-5c %-6d\n", jogador.nome, jogador.cartas, jogador.media, jogador.pontos);
	printf("%-16s %-10s %-5c %-6d\n", computador.nome, computador.cartas, computador.media, computador.pontos);
	printf("-----------------------------------------------\n");
	getchar();
}

void fimDeJogo(Jogador jogador, Jogador computador, Jogador mesa) {
	printf("Fim de jogo!\n");
	getchar();

	if (jogador.pontos > computador.pontos)
		printf("%s ganhou!\n", jogador.nome);
	else if (jogador.pontos < computador.pontos)
		printf("%s ganhou!\n", computador.nome);
	else
		printf("Empate!\n");

	getchar();
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
	imprimirIntroducao();
	inicializarMaos(&jogador, &computador, &mesa);
	perdirNome(&jogador);

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