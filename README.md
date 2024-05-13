# trabalho_pif
trabalho pif - jogo snake

Equipe:
André Luis Castro Monteiro e Silva;
Caio Lima Bezerra;
Lucas Ferreira Sukar Wanderley;



#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int matriz[20][20];
int largura = 20, altura = 20;
int x, y; // Posição da cabeça da cobra
int frutax, frutay; // Posição da fruta
int tecla;
int tamanhocobra;
int cobrax[100], cobray[100]; // Posição do corpo da cobra
int pontuacao;
int fimdejogo;

// Função que configura as variáveis para o início de um novo jogo
void codigo_pre_jogo() {
    x = 10; // Posição inicial da cabeça da cobra no eixo x
    y = 10; // Posição inicial da cabeça da cobra no eixo y
    pontuacao = 0; // Inicializa a pontuação do jogador
    tamanhocobra = 0; // Inicializa o tamanho da cobra
    // Configuração da posição inicial da fruta
    do {
        frutax = 1 + rand() % (largura - 2); // Gera uma posição aleatória no eixo x para a fruta tem -2 para ser gerado dentro das bordas
        frutay = 1 + rand() % (altura - 2); // Gera uma posição aleatória no eixo y para a fruta tem -2 para ser gerado dentro das bordas
    } while (frutax <= 0 || frutay <= 0 || frutax == x || frutay == y || frutax > altura || frutay > largura); // Garante que a fruta não apareça na mesma posição que a cabeça da cobra ou nas bordas
}

// Função que desenha o estado atual do jogo na tela
void jogo(){
    clear_screen(); // Limpa a tela
    // Percorre a matriz representando o tabuleiro do jogo e desenha cada elemento (borda, cabeça da cobra, fruta, corpo da cobra)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0 || i == 19 || j == 0 || j == 19) {
                matriz[i][j] = '#'; // Desenha a borda
            } else if (i == x && j == y) {
                matriz[i][j] = 'O'; // Desenha a cabeça da cobra
            } else if (i == frutax && j == frutay) {
                matriz[i][j] = 'x'; // Desenha a fruta
            } else {
                int corpo = 0;
                // Verifica se a posição atual pertence ao corpo da cobra e desenha apropriadamente
                for (int k = 0; k < tamanhocobra; k++) {
                    if (cobrax[k] == i && cobray[k] == j) {
                        corpo = 1;
                        break;
                    }
                }
                if (corpo) { // Se for corpo da cobra
                    matriz[i][j] = 'o'; // Desenha o corpo da cobra
                } 
                else {
                    matriz[i][j] = ' '; // Deixa a posição vazia
                }
            }
            printf("%c", matriz[i][j]); // Imprime o elemento na tela
        }
        printf("\n"); // Nova linha para o próximo elemento na vertical
    }
}

// Função que contém a lógica do jogo, incluindo movimento da cobra, colisões e pontuação
void Logica(){
    int prevX = cobrax[0];
    int prevY = cobray[0];
    int prev2X, prev2Y;
    cobrax[0] = x;
    cobray[0] = y;
    // Atualiza a posição do corpo da cobra com base no movimento da cabeça
    for (int i = 1; i < tamanhocobra; i++) {
        prev2X = cobrax[i];
        prev2Y = cobray[i];
        cobrax[i] = prevX;
        cobray[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Atualiza a posição da cabeça da cobra com base na tecla pressionada
    if (tecla == 1) {
        x--; // Movimento para cima
    } else if (tecla == 2) {
        x++; // Movimento para baixo
    } else if (tecla == 3) {
        y--; // Movimento para a esquerda
    } else if (tecla == 4) {
        y++; // Movimento para a direita
    }
    
    // Controla a velocidade do jogo com base na pontuação
    if (tecla == 1 || tecla == 2 || tecla == 3 || tecla == 4) {
        if (pontuacao < 5) {
            sleep_ms(100); //aqui é para a cobra andar mais devagar
        } else if (pontuacao >= 5 && pontuacao < 10) {
            sleep_ms(50); //aqui é para a cobra andar mais rápido
        } else if (pontuacao >= 10) {
            sleep_ms(25); //aqui é para a cobra andar mais rápido ainda    
        }
    }

    // Verifica se a cobra colidiu consigo mesma ou com as bordas
    for(int i = 0; i < tamanhocobra; i++){
        if(cobrax[i] == x && cobray[i] == y){
            fimdejogo = 1; //aqui é para cobra morrer se bater nela mesma
        }
    }

    if(x >= largura - 1 || y >= altura - 1 || x <= 0 || y <= 0){
        fimdejogo = 1; //aqui é para cobra morrer se bater na parede
    }

    // Verifica se a cobra comeu a fruta e ajusta a pontuação e o tamanho da cobra
    if(x == frutax && y == frutay){
        pontuacao += 1;
        tamanhocobra++;
        // Reposiciona a fruta em um local aleatório
        do {
            frutax = 1 + rand() % (largura - 2); // Assegura que a fruta apareça dentro das bordas por isso o -2
            frutay = 1 + rand() % (altura - 2); 
        } while (frutax == x || frutay == y || matriz[frutax][frutay] != ' '); // Garante que a fruta não apareça na mesma posição que a cabeça da cobra ou em uma parte ocupada do tabuleiro

    }
}

// Função que verifica se alguma tecla foi pressionada
void teclado(){
    if (is_key_pressed()) {
        char c = get_key();
        if(c == 'w'){
            tecla = 1;
        } else if(c == 's'){
            tecla = 2;
        } else if(c == 'a'){
            tecla = 3;
        } else if(c == 'd'){
            tecla = 4;
        }
    }
}

// Estrutura para representar um jogador e sua pontuação
struct jogador{
    char nome[50];
    int pontuacao;
    struct jogador *next;
};

// Função para adicionar um novo jogador à lista
void novo_jogador(struct jogador **head){
    struct jogador *novo = NULL;
    novo = (struct jogador *)malloc(sizeof(struct jogador));
    printf("Digite o nome do novo jogador: ");
    scanf("%s", novo->nome);
    novo->pontuacao = 0;
    novo->next = NULL;
    if(*head == NULL){
        *head = novo;
    } else{
        struct jogador *temp = *head;
        while( temp->next != NULL){
            temp = temp->next;
        }
        temp->next = novo;
    }
}

// Função para salvar a pontuação do jogador atual
void salva_pontuacao(struct jogador **head, int pontuacao){
    struct jogador *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->pontuacao = pontuacao;    
}

// Função para exibir o ranking dos jogadores
void exibe_ranking(struct jogador **head){
    struct jogador *temp = *head;
    if(temp == NULL){
        printf("Nenhum jogador cadastrado\n");
    } 
    else if(temp->next == NULL){
        printf("%s: %d Pontos\n", temp->nome, temp->pontuacao);
    } 
    else{
        while(temp != NULL){
            printf("%s: %d Pontos\n", temp->nome, temp->pontuacao);
            temp = temp->next;
        }
    }
}

// Função principal
int main(){
    struct jogador *head = NULL;
    while(1){
        int x;
        printf("Bem vindo ao jogo da cobrinha!\n");
        printf("\n");
        printf("Digite 1 para jogar:\n");
        printf("Digite 2 para ver o ranking:\n");
        printf(":");
        scanf("%d", &x);
        if(x == 1){
            clear_screen();
            while(1){
                novo_jogador(&head);
                while (1){
                    codigo_pre_jogo();
                    fimdejogo = 0;
                    while (fimdejogo != 1){
                        timerInit(0); // Add the missing argument to the timerInit() function call
                        jogo(); 
                        teclado();
                        Logica();
                    }
                    clear_screen(); 
                    timerTimeOver();
                    printf("\n");
                    printf("Sua pontuacao: %d", pontuacao);
                    printf("\n");
                    printf("seu tempo vivo: ");
                    timerPrint();
                    timerDestroy();
                    printf("\n");
                    salva_pontuacao(&head, pontuacao);
                    printf("\n");
                    printf("Digite 1 para jogar novamente ou 0 para sair: ");
                    int opcao;
                    scanf("%d", &opcao);
                    if(opcao == 0){
                        clear_screen();
                        break;
                    }
                }
            break;
            }
        }
        if(x == 2){
            clear_screen();
            exibe_ranking(&head);
            printf("\n");
            system("pause"); // pausa o sistema e so continua se a pessoa precionar alguma tecla
            clear_screen();
        }
    }
    return 0;
}

        }
    }
    return 0;
}
