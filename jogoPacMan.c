#include <stdio.h>

// Tamanho do labirinto
#define TAM 10

// Função para exibir o labirinto no terminal
void exibirLabirinto(char labirinto[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // escolha de dificuldade
    int dificuldade;
    printf("Escolha a dificuldade:\n");
    printf("1 - Fácil (1 fantasma, movimento aleatório)\n");
    printf("2 - Difícil (2 fantasmas, movimento semi-inteligente)\n");
    printf("Digite sua escolha: ");
    scanf("%d", &dificuldade);

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

    // Exibir o labirinto no terminal
    printf("Estado atual do labirinto:\n\n");
    exibirLabirinto(labirinto);

    return 0;
}