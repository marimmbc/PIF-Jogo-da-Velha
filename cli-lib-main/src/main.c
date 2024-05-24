#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

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

void timerCallback(void *data)
{
    // Função de callback para o timer (placeholder)
    // Adicione aqui o código que deve ser executado quando o timer expirar
}

void initializeBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = ' ';
        }
    }
}

void freeBoard()
{
    // Limpa recursos do tabuleiro, se necessário
}

void printBoard()
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy((MAXX - strlen("Jogo da Velha")) / 2, 0);
    printf("Jogo da Velha\n\n");

    int rowOffset = 3;
    int colOffset = (MAXX - BOARD_WIDTH) / 2;

    for (int i = 0; i < 3; ++i)
    {
        screenGotoxy(colOffset, i * 4 + rowOffset);
        for (int j = 0; j < 3; ++j)
        {
            char symbol = board[i][j];
            if (symbol == 'O')
            {
                screenSetColor(MAGENTA, DARKGRAY);
            }
            else if (symbol == 'X')
            {
                screenSetColor(MAGENTA, DARKGRAY);
            }
            else
            {
                screenSetColor(CYAN, DARKGRAY);
            }

            printf(" %c ", symbol);
            if (j < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2)
        {
            screenGotoxy(colOffset, i * 4 + 1 + rowOffset);
            printf("-----------\n");
        }
    }
}

int checkWinner()
{
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return 0;
}

int isBoardFull()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

void switchPlayer()
{
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

void makeMove(int choice)
{
    char symbol = (currentPlayer == 1) ? 'O' : 'X';
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] == ' ')
    {
        board[row][col] = symbol;
        switchPlayer();
    }
    else
    {
        printf("Posição já ocupada. Escolha outra.\n");
    }
}

int getRandomMove()
{
    int move;
    do
    {
        move = rand() % 9 + 1;
    } while (board[(move - 1) / 3][(move - 1) % 3] != ' ');

    return move;
}

void printHello()
{
    screenSetColor(GREEN, GREEN);
    screenGotoxy(0, 0);
    printf("Bem-vindo ao Jogo da Velha!\n\n");
}

int askToPlayAgain()
{
    printf("Deseja jogar novamente? Digite S ou N : ");
    while (1)
    {
        char playAgain;
        scanf(" %c", &playAgain);

        if (playAgain == 's' || playAgain == 'S')
        {
            return 1;
        }
        else if (playAgain == 'n' || playAgain == 'N')
        {
            printf("Jogo encerrado. Obrigado por jogar!\n");
            return 0;
        }
        else
        {
            printf("Opção inválida. Digite 'S' para jogar novamente ou 'N' para sair: ");
        }
    }
}

void animateCollision(int row, int col, char symbol)
{
    int colOffset = (MAXX - BOARD_WIDTH) / 2;
    int rowOffset = 3;
    int x = colOffset + col * 4;
    int y = rowOffset + row * 4;

    screenGotoxy(x, y);
    screenSetColor(WHITE, RED); // Cor destacada para a colisão
    printf(" %c ", symbol);
    fflush(stdout);
    usleep(200000); // Espera 200 ms

    // Restaura o símbolo original
    screenGotoxy(x, y);
    if (board[row][col] == 'O')
    {
        screenSetColor(MAGENTA, DARKGRAY);
    }
    else
    {
        screenSetColor(MAGENTA, DARKGRAY);
    }
    printf(" %c ", board[row][col]);
    fflush(stdout);
}

void animateDrop(int row, int col, char symbol)
{
    int colOffset = (MAXX - BOARD_WIDTH) / 2;
    int rowOffset = 3;
    int x = colOffset + col * 4;

    for (int i = 0; i <= row; ++i)
    {
        screenGotoxy(x, rowOffset + i * 4);
        screenSetColor(WHITE, DARKGRAY); // Cor para o símbolo caindo
        printf(" %c ", symbol);
        fflush(stdout);
        usleep(100000); // Espera 100 ms

        // Limpa o traço anterior se não for a posição final
        if (i < row)
        {
            screenGotoxy(x, rowOffset + i * 4);
            printf("   ");
        }
    }
}

void makeMove(int choice)
{
    char symbol = (currentPlayer == 1) ? 'O' : 'X';
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (board[row][col] == ' ')
    {
        animateDrop(row, col, symbol); // Animação de cair
        board[row][col] = symbol;
        switchPlayer();
    }
    else
    {
        animateCollision(row, col, symbol); // Animação de colisão
        printf("Posição já ocupada. Escolha outra.\n");
    }
}

int main()
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50, timerCallback); // Supondo que timerInit necessite de um callback e dados

    int numPlayers;
    printf("Digite o número de jogadores (1 ou 2): ");
    scanf("%d", &numPlayers);

    if (numPlayers == 1)
    {
        printf("Digite o nome do jogador 1: ");
        scanf("%s", player1);
        strcpy(player2, "Jogador 2");
    }
    else if (numPlayers == 2)
    {
        printf("Digite o nome do jogador 1: ");
        scanf("%s", player1);
        printf("Digite o nome do jogador 2: ");
        scanf("%s", player2);
    }
    else
    {
        printf("Número inválido de jogadores. Encerrando o jogo.\n");
        return 1;
    }

    do
    {
        initializeBoard();
        currentPlayer = 1;

        while (1)
        {
            printBoard();

            if (numPlayers == 1 && currentPlayer == 2)
            {
                int move = getRandomMove();
                printf("%s escolheu %d\n", player2, move);
                makeMove(move);
            }
            else
            {
                int validMove = 0;

                while (!validMove)
                {
                    printf("%s, escolha um número de 1 a 9: ", (currentPlayer == 1) ? player1 : player2);
                    if (scanf("%d", &ch) == 1)
                    {
                        if (ch >= 1 && ch <= 9 && board[(ch - 1) / 3][(ch - 1) % 3] == ' ')
                        {
                            validMove = 1;
                        }
                        else
                        {
                            printf("Posição inválida. Escolha outra.\n");
                        }
                    }
                    else
                    {
                        printf("Entrada inválida. Digite apenas um número.\n");
                        while (getchar() != '\n')
                            ;
                    }
                }

                makeMove(ch);
            }

            screenUpdate();

            int winner = checkWinner();
            if (winner)
            {
                printf("Parabéns, %s! Você venceu!\n", (winner == 'O') ? player1 : player2);
                if (winner == 'O')
                {
                    pontuacao1++;
                }
                else
                {
                    pontuacao2++;
                }
                printf("Pontuação atual: %s %d - %s %d\n", player1, pontuacao1, player2, pontuacao2);
                initializeBoard();
                break;
            }
            else if (isBoardFull())
            {
                printf("O jogo empatou!\n");
                initializeBoard();
                break;
            }

            if (!askToPlayAgain())
            {
                break;
            }
        }

    } while (1);

    freeBoard();

    keyboardDestroy();
    timerDestroy(NULL); // Supondo que não precisa de dados

    return 0;
}
