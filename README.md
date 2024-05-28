# PIF-Jogo-da-Velha

## Apresentação do Jogo

Este Jogo-da-Velha é uma versão interativa do clássico jogo da velha (tic-tac-toe), desenvolvida em C, com suporte para um ou dois jogadores. O jogo apresenta animações para a movimentação das peças e detecção de colisões, tornando a experiência mais dinâmica e visualmente agradável.

## Instruções de Compilação e Uso

Para compilar e executar o jogo, siga os seguintes passos:

1. Navegue até o diretório principal do projeto:
    ```bash
    cd cli-lib-main
    ```

2. Compile o código usando o Makefile:
    ```bash
    make
    ```

3. Execute o jogo:
    ```bash
    ./bin/jogo_da_velha
    ```

## Detalhes de Implementação

### Estrutura do Código

O código do jogo está organizado da seguinte forma:

- `main.c`: Contém a lógica principal do jogo, incluindo a inicialização dos componentes, o loop principal do jogo, e a gestão das entradas dos jogadores.

### Funções Principais

- `initializeBoard()`: Inicializa o tabuleiro do jogo, preenchendo todas as posições com espaços em branco.

- `clearEndGameMessage()`: Limpa as mensagens de fim de jogo da tela.

- `printBoard()`: Exibe o tabuleiro do jogo na tela, com as peças dos jogadores.

- `animacao_queda(int linha, int coluna, char peca)`: Anima a queda de uma peça até a posição escolhida.

- `animacao_colisao(int linha, int coluna, char peca)`: Anima a colisão quando uma peça é colocada em uma posição já ocupada.

- `checkWinner()`: Verifica se há um vencedor, retornando o símbolo do jogador vencedor.

- `isBoardFull()`: Verifica se o tabuleiro está completamente preenchido.

- `switchPlayer()`: Alterna a vez entre os jogadores.

- `makeMove(int choice)`: Realiza a movimentação de uma peça no tabuleiro, com animação.

- `getRandomMove()`: Gera uma jogada aleatória para o modo de jogo contra o computador.

- `printHello()`: Exibe uma mensagem de boas-vindas no início do jogo.

- `askToPlayAgain()`: Pergunta ao usuário se ele deseja jogar novamente após o término de uma partida.

- `keyboardQuit()`: Finaliza o uso do teclado.

- `timerQuit()`: Finaliza o uso do timer.

- `screenQuit()`: Finaliza o uso da tela.

### Fluxo do Jogo

1. O jogo inicia solicitando o número de jogadores (1 ou 2) e os nomes dos jogadores.
2. Em cada rodada, o jogador atual escolhe uma posição no tabuleiro para colocar sua peça.
3. O jogo verifica se há um vencedor ou se o tabuleiro está cheio após cada jogada.
4. Quando uma partida termina, o placar é atualizado e o jogador é questionado se deseja jogar novamente.
