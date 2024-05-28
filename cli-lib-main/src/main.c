#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAXX 80
#define MAXY 24

#define BOARD_WIDTH 13
#define BOARD_HEIGHT 7

char board[3][3];
char player1[50], player2[50];
int currentPlayer;
int pontuacao1 = 0, pontuacao2 = 0;

void initializeBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void clearEndGameMessage() {
    int colOffset = (MAXX - BOARD_WIDTH) / 2;

    screenGotoxy(colOffset, MAXY - 2);
    printf("                          "); // Limpa a linha de mensagem de vencedor
    screenGotoxy(colOffset, MAXY - 1);
    printf("                          "); // Limpa a linha de mensagem de empate
    fflush(stdout);
}

void printBoard() {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy((MAXX - strlen("Jogo da Velha")) / 2, 0);
    printf("Jogo da Velha\n\n");

    int rowOffset = (MAXY - BOARD_HEIGHT) / 2;
    int colOffset = (MAXX - BOARD_WIDTH) / 2;

    for (int i = 0; i < 3; ++i) {
        screenGotoxy(colOffset, i * 2 + rowOffset);
        for (int j = 0; j < 3; ++j) {
            char symbol = board[i][j];
            screenSetColor(MAGENTA, DARKGRAY);
            printf(" %c ", symbol);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            screenGotoxy(colOffset, i * 2 + 1 + rowOffset);
            printf("---|---|---\n");
        }
    }
}

void animacao_queda(int linha, int coluna, char peca) {
    int rowOffset = (MAXY - BOARD_HEIGHT) / 2;
    int colOffset = (MAXX - BOARD_WIDTH) / 2;
    for (int i = 0; i <= linha; i++) {
        screenGotoxy(colOffset + coluna * 4, rowOffset + i * 2);
        printf(" %c ", peca);
        fflush(stdout);
        usleep(100000); // Atraso para a animação
        if (i < linha) { // Limpa a posição anterior se não for a última linha
            screenGotoxy(colOffset + coluna * 4, rowOffset + i * 2);
            printf("   "); // Limpa a posição anterior
            fflush(stdout);
        }
    }
    board[linha][coluna] = peca; // Atualiza o tabuleiro
}

void animacao_colisao(int linha, int coluna, char peca) {
    int rowOffset = (MAXY - BOARD_HEIGHT) / 2;
    int colOffset = (MAXX - BOARD_WIDTH) / 2;
    for (int i = 0; i < 3; i++) {
        screenGotoxy(colOffset + coluna * 4, rowOffset + linha * 2);
        printf(" %c ", ' '); // Limpa a peça temporariamente
        fflush(stdout);
        usleep(100000); // Atraso para a animação
        screenGotoxy(colOffset + coluna * 4, rowOffset + linha * 2);
        printf(" %c ", peca); // Desenha a peça novamente
        fflush(stdout);
        usleep(100000); // Atraso para a animação
    }
}

int checkWinner() {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void makeMove(int choice) {
    char symbol = (currentPlayer == 1) ? 'O' : 'X';
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] == ' ') {
        animacao_queda(row, col, symbol); // Animação de queda
        switchPlayer();
    } else {
        animacao_colisao(row, col, board[row][col]); // Animação de colisão
        printf("Posição já ocupada. Escolha outra.\n");
    }
}

int getRandomMove() {
    int move;
    do {
        move = rand() % 9 + 1;
    } while (board[(move - 1) / 3][(move - 1) % 3] != ' ');

    return move;
}

void printHello() {
    screenSetColor(GREEN, GREEN);
    screenGotoxy(0, 0);
    printf("Bem-vindo ao Jogo da Velha!\n\n");
}

int askToPlayAgain() {
    printf("Deseja jogar novamente? Digite S ou N: ");
    while (1) {
        char playAgain;
        scanf(" %c", &playAgain);

        if (playAgain == 's' || playAgain == 'S') {
            clearEndGameMessage(); // Limpa a mensagem de fim de jogo antes de reiniciar
            screenClear(); // Limpa a tela ao reiniciar o jogo
            return 1; // Reinicializar o jogo
        } else if (playAgain == 'n' || playAgain == 'N') {
            printf("Jogo encerrado. Obrigado por jogar!\n");
            return 0; // Sair do programa
        } else {
            printf("Opção inválida. Digite 'S' para jogar novamente ou 'N' para sair: ");
        }
    }
}

// Definições das funções `keyboardQuit`, `timerQuit` e `screenQuit`
void keyboardQuit() {
    // Código para finalizar o uso do teclado
}

void timerQuit() {
    // Código para finalizar o uso do timer
}

void screenQuit() {
    // Código para finalizar o uso da tela
}

int main() {
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    int numPlayers;
    printf("Digite o número de jogadores (1 ou 2): ");
    scanf("%d", &numPlayers);

    if (numPlayers == 1) {
        printf("Digite o nome do jogador 1: ");
        scanf("%s", player1);
        strcpy(player2, "Computador");
    } else if (numPlayers == 2) {
        printf("Digite o nome do jogador 1: ");
        scanf("%s", player1);
        printf("Digite o nome do jogador 2: ");
        scanf("%s", player2);
    } else {
        printf("Número inválido de jogadores. Encerrando o jogo.\n");
        return 1;
    }

    int playAgain;
    do {
        screenClear(); // Limpa a tela antes de iniciar uma nova partida
        initializeBoard();
        currentPlayer = 1;

        while (1) {
            printBoard();

            if (numPlayers == 1 && currentPlayer == 2) {
                int move = getRandomMove();
                printf("%s escolheu %d\n", player2, move);
                makeMove(move);
            } else {
                int validMove = 0;
                while (!validMove) {
                    printf("%s, escolha um número de 1 a 9: ", (currentPlayer == 1) ? player1 : player2);
                    if (scanf("%d", &ch) == 1 && ch >= 1 && ch <= 9) {
                        if (board[(ch - 1) / 3][(ch - 1) % 3] == ' ') {
                            validMove = 1;
                        } else {
                            animacao_colisao((ch - 1) / 3, (ch - 1) % 3, board[(ch - 1) / 3][(ch - 1) % 3]);
                            printf("Posição já ocupada. Escolha outra.\n");
                        }
                    } else {
                        printf("Entrada inválida. Escolha um número de 1 a 9.\n");
                        while (getchar() != '\n'); // Limpar buffer de entrada
                    }
                }
                makeMove(ch);
            }

            int winner = checkWinner();
            if (winner) {
                printBoard();
                printf("%s venceu!\n", (winner == 'O') ? player1 : player2);
                if (winner == 'O') {
                    pontuacao1++;
                } else {
                    pontuacao2++;
                }
                break;
            } else if (isBoardFull()) {
                printBoard();
                printf("Empate!\n");
                break;
            }
        }

        printf("Placar: %s %d - %d %s\n", player1, pontuacao1, pontuacao2, player2);

        clearEndGameMessage(); // Limpa a mensagem de fim de jogo antes de reiniciar

        playAgain = askToPlayAgain();
    } while (playAgain);

    keyboardQuit();
    timerQuit();
    screenQuit();

    return 0;
}
