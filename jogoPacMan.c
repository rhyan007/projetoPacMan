// Para limpar a tela:
// No Linux/macOS, use system("clear");
// No Windows, use system("cls");

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>  // toupper

#define TAM 10
#define MAX_FANTASMAS 2

// Função para exibir o labirinto e a pontuação atual
void exibirLabirinto(char labirinto[TAM][TAM], int pontos) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
    printf("Pontos: %d\n", pontos);
}

// Função que movimenta os fantasmas no labirinto
void moverFantasmas(char labirinto[TAM][TAM], int fantasmas[MAX_FANTASMAS][2], int qtdFantasmas,
                    int px, int py, int pontos, int dificuldade, int comida[TAM][TAM]) {
    for (int i = 0; i < qtdFantasmas; i++) {
        int fx = fantasmas[i][0]; // posição atual x do fantasma
        int fy = fantasmas[i][1]; // posição atual y do fantasma

        int novo_fx = fx;
        int novo_fy = fy;

        if (dificuldade == 1) {
            // Movimento aleatório - dificuldade fácil
            int dir = rand() % 4;
            if (dir == 0) novo_fx--;
            else if (dir == 1) novo_fx++;
            else if (dir == 2) novo_fy--;
            else if (dir == 3) novo_fy++;

            // Verifica se o movimento é válido 
            if (novo_fx < 0 || novo_fx >= TAM || novo_fy < 0 || novo_fy >= TAM ||
                (labirinto[novo_fx][novo_fy] != ' ' && labirinto[novo_fx][novo_fy] != '*')) {
                novo_fx = fx;  // movimento inválido - mantém posição
                novo_fy = fy;
            }
        } else {
            // Movimento semi-inteligente - dificuldade difícil
            int melhor_fx = fx, melhor_fy = fy;
            int menor_dist = abs(fx - px) + abs(fy - py);

            // Tenta os 4 movimentos possíveis (cima, baixo, esquerda, direita)
            int tentativas[4][2] = {
                {fx - 1, fy}, {fx + 1, fy},
                {fx, fy - 1}, {fx, fy + 1}
            };

            for (int t = 0; t < 4; t++) {
                int tx = tentativas[t][0];
                int ty = tentativas[t][1];

                // Verifica se a posição é válida
                if (tx >= 0 && tx < TAM && ty >= 0 && ty < TAM) {
                    // Se a posição tem espaço vazio ou comida, calcula a distância para o jogador
                    if (labirinto[tx][ty] == ' ' || labirinto[tx][ty] == '*') {
                        int dist = abs(tx - px) + abs(ty - py);
                        if (dist < menor_dist) {
                            menor_dist = dist;
                            melhor_fx = tx;
                            melhor_fy = ty;
                        }
                    } else if (labirinto[tx][ty] == 'P') {
                        // Fantasma encontrou o jogador - fim de jogo
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

        // Se o fantasma vai se mover
        if (novo_fx != fx || novo_fy != fy) {
            if (labirinto[novo_fx][novo_fy] == 'P') {
                // Fantasma capturou o jogador
                system("clear");
                printf("Um fantasma te pegou!\n");
                printf("Game Over! Sua pontuação: %d\n", pontos);
                exit(0);
            }
            // Restaura a comida (*) se ainda existir na posição antiga do fantasma
            if (comida[fx][fy]) {
                labirinto[fx][fy] = '*';
            } else {
                labirinto[fx][fy] = ' ';
            }
            // Move o fantasma para a nova posição
            labirinto[novo_fx][novo_fy] = 'G';
            fantasmas[i][0] = novo_fx;
            fantasmas[i][1] = novo_fy;
        }
    }
}

int main() {
    char jogarNovamente;

    do {
        int dificuldade;
        printf("Escolha a dificuldade:\n");
        printf("1 - Fácil (1 fantasma, movimento aleatório)\n");
        printf("2 - Difícil (2 fantasmas, movimento semi-inteligente)\n");
        printf("Digite sua escolha: ");
        scanf("%d", &dificuldade);
        getchar();  // Limpa o buffer do teclado

        // Labirinto inicial
        char labirinto[TAM][TAM] = {
            {'#','#','#','#','#','#','#','#','#','#'},
            {'#','P',' ','*',' ',' ',' ',' ',' ','#'},
            {'#',' ','#','#','#',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ','*',' ','G',' ',' ','#'},
            {'#',' ','#','#','#',' ',' ','#','#','#'},
            {'#',' ','*',' ',' ',' ',' ','*',' ','#'},
            {'#',' ',' ','#','#','#',' ',' ',' ','#'},
            {'#','*',' ',' ','G',' ','*',' ',' ','#'},
            {'#',' ',' ',' ',' ','*',' ',' ',' ','#'},
            {'#','#','#','#','#','#','#','#','#','#'},
        };

        // Inicializa a matriz que indica onde tem comida (*)
        int comida[TAM][TAM] = {0};
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (labirinto[i][j] == '*') {
                    comida[i][j] = 1;
                }
            }
        }

        // Conta total de comidas para controle de vitória
        int totalComidas = 0;
        for (int i = 0; i < TAM; i++)
            for (int j = 0; j < TAM; j++)
                if (labirinto[i][j] == '*')
                    totalComidas++;

        // Posição inicial do jogador 
        int px = 1, py = 1;
        int pontos = 0;  // Pontuação inicial
        char comando;

        // Array para guardar posições dos fantasmas
        int fantasmas[MAX_FANTASMAS][2];
        int qtdFantasmas = 0;

        // Identifica a posição dos fantasmas no labirinto
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (labirinto[i][j] == 'G') {
                    fantasmas[qtdFantasmas][0] = i;
                    fantasmas[qtdFantasmas][1] = j;
                    qtdFantasmas++;
                }
            }
        }

        // Se dificuldade for fácil, mantém apenas 1 fantasma
        if (dificuldade == 1) {
            while (qtdFantasmas > 1) {
                int fx = fantasmas[qtdFantasmas - 1][0];
                int fy = fantasmas[qtdFantasmas - 1][1];
                labirinto[fx][fy] = ' ';
                qtdFantasmas--;
            }
        }

        srand(time(NULL));  // Inicializa a seed para números aleatórios

        int vitoria = 0;  // Flag para vitória

        // Loop principal do jogo
        while (1) {
            system("clear");  // Limpa a tela 
            exibirLabirinto(labirinto, pontos);  // Mostra labirinto e pontos

            printf("Use W A S D para mover (ou Q para sair): ");
            scanf(" %c", &comando);

            int novoX = px, novoY = py;

            if (comando == 'q' || comando == 'Q') break;  // Sai do jogo

            // Calcula nova posição com base no comando do usuário
            switch (comando) {
                case 'w': case 'W': novoX--; break;
                case 's': case 'S': novoX++; break;
                case 'a': case 'A': novoY--; break;
                case 'd': case 'D': novoY++; break;
                default: continue;  // Ignora comandos inválidos
            }

            // Verifica se nova posição é válida
            if (novoX < 0 || novoX >= TAM || novoY < 0 || novoY >= TAM) continue;
            if (labirinto[novoX][novoY] == '#') continue;  // Parede

            // Se comeu comida, atualiza pontuação, total e matriz comida
            if (labirinto[novoX][novoY] == '*') {
                pontos += 10;
                totalComidas--;
                comida[novoX][novoY] = 0;  // Marca comida como consumida
            }

            // Se entrou em fantasma, game over
            if (labirinto[novoX][novoY] == 'G') {
                system("clear");
                printf("Você encontrou um fantasma! Fim de jogo.\n");
                printf("Pontuação final: %d\n", pontos);
                break;
            }

            // Atualiza o labirinto: apaga posição antiga do jogador
            labirinto[px][py] = ' ';
            px = novoX;
            py = novoY;
            labirinto[px][py] = 'P';  // Atualiza posição do jogador

            // Verifica vitória: se acabou comida, jogador vence
            if (totalComidas == 0) {
                system("clear");
                exibirLabirinto(labirinto, pontos);
                printf("Parabéns! Você coletou todas as comidas!\n");
                printf("Vitória!\n");
                printf("Pontuação final: %d\n", pontos);
                vitoria = 1;
                break;
            }

            // Move os fantasmas conforme a dificuldade
            moverFantasmas(labirinto, fantasmas, qtdFantasmas, px, py, pontos, dificuldade, comida);
        }

        // Pergunta se quer jogar novamente
        printf("\nDeseja jogar novamente? (S/N): ");
        scanf(" %c", &jogarNovamente);
        jogarNovamente = toupper(jogarNovamente);
    } while (jogarNovamente == 'S');

    printf("Obrigado por jogar!\n");
    return 0;
}
