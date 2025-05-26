#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Para gerar números aleatórios

// Tamanho do labirinto
#define TAM 10
#define MAX_FANTASMAS 2

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

// Função para movimentar fantasmas
void moverFantasmas(char labirinto[TAM][TAM], int fantasmas[MAX_FANTASMAS][2], int qtdFantasmas, int px, int py, int pontos, int dificuldade) {
    for (int i = 0; i < qtdFantasmas; i++) {
        int fx = fantasmas[i][0];
        int fy = fantasmas[i][1];

        int novo_fx = fx;
        int novo_fy = fy;

        if (dificuldade == 1) {
            // Modo fácil: movimento aleatório
            int dir = rand() % 4;
            if (dir == 0) novo_fx--;        // cima
            else if (dir == 1) novo_fx++;   // baixo
            else if (dir == 2) novo_fy--;   // esquerda
            else if (dir == 3) novo_fy++;   // direita

            // Verifica se o movimento é válido
            if (novo_fx < 0 || novo_fx >= TAM || novo_fy < 0 || novo_fy >= TAM ||
                (labirinto[novo_fx][novo_fy] != ' ' && labirinto[novo_fx][novo_fy] != '*')) {
                novo_fx = fx;
                novo_fy = fy;
            }
        } else {
            // Modo difícil: movimento inteligente (aproximar do jogador)
            int melhor_fx = fx, melhor_fy = fy;
            int menor_dist = abs(fx - px) + abs(fy - py);

            int tentativas[4][2] = {
                {fx - 1, fy},  // cima
                {fx + 1, fy},  // baixo
                {fx, fy - 1},  // esquerda
                {fx, fy + 1}   // direita
            };

            for (int t = 0; t < 4; t++) {
                int tx = tentativas[t][0];
                int ty = tentativas[t][1];

                // Verificando se o movimento é válido e dentro do labirinto
                if (tx >= 0 && tx < TAM && ty >= 0 && ty < TAM) {
                    if (labirinto[tx][ty] == ' ' || labirinto[tx][ty] == '*') {
                        int dist = abs(tx - px) + abs(ty - py);
                        if (dist < menor_dist) {
                            menor_dist = dist;
                            melhor_fx = tx;
                            melhor_fy = ty;
                        }
                    }
                    else if (labirinto[tx][ty] == 'P') {
                        system("clear");
                        printf("Um fantasma te pegou!\n");
                        printf("Game Over! Sua pontuação: %d\n", pontos);
                        exit(0);
                    }
                }
            }

            novo_fx = melhor_fx;
            novo_fy = melhor_fy;
        }

        if (novo_fx != fx || novo_fy != fy) {
            if (labirinto[novo_fx][novo_fy] == 'P') {
                system("clear");
                printf("Um fantasma te pegou!\n");
                printf("Game Over! Sua pontuação: %d\n", pontos);
                exit(0);
            }
            labirinto[fx][fy] = ' ';
            labirinto[novo_fx][novo_fy] = 'G';
            fantasmas[i][0] = novo_fx;
            fantasmas[i][1] = novo_fy;
        }
    }
}

int main() {
    int dificuldade;
    printf("Escolha a dificuldade:\n");
    printf("1 - Fácil (1 fantasma, movimento aleatório)\n");
    printf("2 - Difícil (2 fantasmas, movimento semi-inteligente)\n");
    printf("Digite sua escolha: ");
    scanf("%d", &dificuldade);
    getchar();

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

    int fantasmas[MAX_FANTASMAS][2];
    int qtdFantasmas = 0;

    // Ajusta quantidade de fantasmas dependendo da dificuldade
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (labirinto[i][j] == 'G') {
                fantasmas[qtdFantasmas][0] = i;
                fantasmas[qtdFantasmas][1] = j;
                qtdFantasmas++;
            }
        }
    }

    if (dificuldade == 1) {
        // No modo fácil, mantém só 1 fantasma no labirinto
        while (qtdFantasmas > 1) {
            int fx = fantasmas[qtdFantasmas - 1][0];
            int fy = fantasmas[qtdFantasmas - 1][1];
            labirinto[fx][fy] = ' ';  // Remove fantasma extra do labirinto
            qtdFantasmas--;
        }
    }    

    srand(time(NULL));

    while (1) {
        system("clear");
        exibirLabirinto(labirinto, pontos);

        printf("Use W A S D para mover (ou Q para sair): ");
        scanf(" %c", &comando);

        int novoX = px, novoY = py;

        if (comando == 'q' || comando == 'Q') break;

        switch (comando) {
            case 'w': case 'W': novoX--; break;
            case 's': case 'S': novoX++; break;
            case 'a': case 'A': novoY--; break;
            case 'd': case 'D': novoY++; break;
            default: continue;
        }

        if (novoX < 0 || novoX >= TAM || novoY < 0 || novoY >= TAM) continue;
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

        moverFantasmas(labirinto, fantasmas, qtdFantasmas, px, py, pontos, dificuldade);
    }

    return 0;
}
