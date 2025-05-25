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