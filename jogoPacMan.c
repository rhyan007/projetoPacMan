#include <stdio.h>
#include <stdlib.h>

// Tamanho do labirinto
#define TAM 10

// Função para exibir o labirinto no terminal
void exibirLabirinto(char labirinto[TAM][TAM], int pontos) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
    printf("Pontos: %d\n", pontos);
}

int main() {
    // escolha de dificuldade
    int dificuldade;
    printf("Escolha a dificuldade:\n");
    printf("1 - Fácil (1 fantasma, movimento aleatório)\n");
    printf("2 - Difícil (2 fantasmas, movimento semi-inteligente)\n");
    printf("Digite sua escolha: ");
    scanf("%d", &dificuldade);
    getchar(); // Captura o Enter restante no buffer

    // Inicialização do labirinto (10x10)
    char labirinto[TAM][TAM] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'P', ' ', '*', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '*', ' ', 'G', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#'},
        {'#', ' ', '*', ' ', ' ', ' ', ' ', '*', ' ', '#'},
        {'#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#'},
        {'#', '*', ' ', ' ', 'G', ' ', '*', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };

    int px = 1, py = 1;
    int pontos = 0;
    char comando;

    while (1) {
        system("clear");
        exibirLabirinto(labirinto, pontos);

        printf("Use W A S D para mover (ou Q para sair): ");
        comando = getchar();
        getchar(); // Captura o Enter

        int novoX = px, novoY = py;

        if (comando == 'q' || comando == 'Q') break;

        switch (comando) {
            case 'w': case 'W': novoX--; break;
            case 's': case 'S': novoX++; break;
            case 'a': case 'A': novoY--; break;
            case 'd': case 'D': novoY++; break;
            default: continue; // Comando inválido
        }

        if (labirinto[novoX][novoY] == '#') continue;

        if (labirinto[novoX][novoY] == '*') {
            pontos += 10;
        }

        if (labirinto[novoX][novoY] == 'G') {
            system("clear");
            printf("Você encontrou um fantasma! Fim de jogo.\n");
            printf("Pontuação final: %d\n", pontos);
            break;
        }

        labirinto[px][py] = ' ';
        px = novoX;
        py = novoY;
        labirinto[px][py] = 'P';
    }

    return 0;
}