#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Bem vindo ao código de Sokoban!

//Primeiro, é preciso definir as dimensões para cada fase.
#define COl_FACIL 16           
#define LIN_FACIL 9
#define DESTINOS_FACIL 7
#define COl_MEDIO 40
#define LIN_MEDIO 11
#define DESTINOS_MEDIO 6
#define COl_DIFICIL 44
#define LIN_DIFICIL 13
#define DESTINOS_DIFICIL 20

//Definindo uma função para definir todas as posições dos objetivos/destinos
int encontrarDestinos(int destinos[],int qnt_destinos, int coluna, int linha, char mapa[]){

int destinos_cont[qnt_destinos], cont=0;

    for(int i=0;i<linha; i++){
        for(int j=0;j<coluna; j++){
            if (mapa[coluna*i+j] == '+' || mapa[coluna*i+j] == '0') {
                destinos_cont[cont] = coluna*i+j;
                destinos[cont] = destinos_cont[cont]; 
                cont++;}
        }
    }
return 0;
}

//Definindo função para conferir se uma posição é um destino.
int conferirDestinos(int x, int destinos[], int qnt_destinos){

    for(int i=0;i<qnt_destinos; i++){
        if (x == destinos[i]){return 1;}
    }
    return 0;
}

//Definindo uma função para encontrar a posição do jogador no mapa.
int posicaoJogador(int coluna, int linha, char mapa[]){

    int jogador;
    for(int i=0;i<linha; i++){
            for(int j=0;j<coluna; j++){
                if(mapa[coluna*i+j]=='@'){jogador = coluna*i+j;}
            }
    }
    return jogador;
}

//Definindo uma função de condicao de vitoria
int condicaoDeVitoria(int qnt_destinos, int coluna, int linha, char mapa[]){
    int destinos_depois[qnt_destinos], cont=0;
    encontrarDestinos(destinos_depois, qnt_destinos, coluna, linha, mapa);

    for(int i=0;i<linha; i++){
        for(int j=0;j<coluna; j++){
            if (mapa[coluna*i+j] == '0'){cont++;}
        }
    }
    if (cont == qnt_destinos){return 1;}
return 0;
}

//Definindo uma função com as regras de movimento
int andar(char mapa[], int posicao, int prox_dim, int destinos[], int qnt_destinos){
    if(mapa[posicao+prox_dim]=='X' || mapa[posicao+prox_dim]=='0'){
        if(mapa[posicao+2*prox_dim]=='#' || mapa[posicao+2*prox_dim]=='X'|| mapa[posicao+2*prox_dim]=='0'){
            return 1;  
        }else{
            if(conferirDestinos(posicao+2*prox_dim, destinos, qnt_destinos)==1){mapa[posicao+2*prox_dim] = '0';}
            else{mapa[posicao+2*prox_dim] = 'X';}  
            }
    }
    
    if(mapa[posicao+prox_dim]!='#'){
        if(conferirDestinos(posicao, destinos, qnt_destinos)==1){mapa[posicao] = '+';}
        else{mapa[posicao] = '-';}
        mapa[posicao+prox_dim] = '@';}
        return 1;}

int main(void){

    //Declaração de variáveis.
    int fase, coluna, linha, qnt_destinos, i, posicao;
    char mapa_usado[600];
    char movimento;

    //Definindo o design dos mapas.

    char mapa_facil[200] = {

            "    # # # # #  \n"
            "# # # - - - #  \n"
            "# + @ X - - #  \n"
            "# # # - X + #  \n"
            "# + # # X - #  \n"
            "# - # - + - # #\n"
            "# X - 0 X X + #\n"
            "# - - - + - - #\n"
            "# # # # # # # #\n"

        };

        char mapa_medio[500] = {
    "        # # # # #                      \n"
    "        # - - - #                      \n"
    "        # X - - #                      \n"
    "    # # # - - X # #                    \n"
    "    # - - X - X - #                    \n"
    "# # # - # - # # - #     # # # # # # # #\n"
    "# - - - # - # # - # # # # - - - - + + #\n"
    "# - X - - X - - - - - - - - - - - + + #\n"
    "# # # # # - # # # - # @ # # - - - + + #\n"
    "        # - - - - - # # # # # # # # # #\n"
    "        # # # # # # #                  \n"
    };

    char mapa_dificil[600] = {
    "                            # # # # # # # #\n"
    "                            # - - + + + + #\n"
    "      # # # # # # # # # # # # - - + + + + #\n"
    "      # - - - - # - - X - X - - - + + + + #\n"
    "      # - X X X # X - - X - # - - + + + + #\n"
    "      # - - X - - - - - X - # - - + + + + #\n"
    "      # - X X - # X - X - X # # # # # # # #\n"
    "# # # # - - X - # - - - - - #              \n"
    "# - - - # - # # # # # # # # #              \n"
    "# - - - - X - - # #                        \n"
    "# - X X # X X - @ #                        \n"
    "# - - - # - - - # #                        \n"
    "# # # # # # # # #                          \n"
    };

    //Agora, é preciso desenvolver um menu que ensina os comandos e permite a seleção de fases!

    char menu[512] = {
      "# # # # # # # # # # # # # # # # # # # # # # # # # # #\n"  
      "#  _____  _____  _____  _____  _____  _____  _____  #\n"
      "# |   __||     ||  |  ||     || __  ||  _  ||   | | #\n"
      "# |__   ||  |  ||    -||  |  || __ -||     || | | | #\n"
      "# |_____||_____||__|__||_____||_____||__|__||_|___| #\n"
      "#                                                   #\n"
      "# # # # # # # # # # # # # # # # # # # # # # # # # # #\n\n"};
      
    printf("\n%s", menu);
    printf("Para jogar Sokoban use as teclas wasd para se mover.\n");
    printf("Seu objetivo e empurrar todas as caixas X ate os destinos + sem ficar preso!\n\n");
    printf("Selecione uma fase:\n");
    printf( "1 - NIVEL 1   2 - NIVEL 2   3 - NIVEL 3\n");

    //Obter a fase para definir qual mapa será usado pelas funcoes.
    scanf("%d", &fase);

    //Definir as variaveis do mapa que será usado
    if(fase==1){
        coluna = COl_FACIL;
        linha = LIN_FACIL;
        qnt_destinos = DESTINOS_FACIL;
        while (mapa_facil[i]!='\0'){
        mapa_usado[i] = mapa_facil[i];
        i++;}
    }
    if(fase==2){
        coluna = COl_MEDIO;
        linha = LIN_MEDIO;
        qnt_destinos = DESTINOS_MEDIO;
        while (mapa_medio[i]!='\0'){
        mapa_usado[i] = mapa_medio[i];
        i++;}
    }
    if(fase==3){
        coluna = COl_DIFICIL;
        linha = LIN_DIFICIL;
        qnt_destinos = DESTINOS_DIFICIL;
        while (mapa_dificil[i]!='\0'){
        mapa_usado[i] = mapa_dificil[i];
        i++;}
    }

    int destinos[qnt_destinos];

    encontrarDestinos(destinos, qnt_destinos, coluna, linha, mapa_usado);

    //Desenvolver um game loop
    while(1){

        printf("mover --> wasd   reiniciar --> x\n");
        printf("\n%s\n", mapa_usado);

        posicao = posicaoJogador(coluna, linha, mapa_usado);

        movimento = getchar();
        if(movimento == 'x'){break;}

        switch(movimento){
            case 'w':
                if(andar(mapa_usado, posicao, -coluna, destinos, qnt_destinos)==1){break;}
                else{andar(mapa_usado, posicao, -coluna, destinos, qnt_destinos);}
            case 's':
                if(andar(mapa_usado, posicao, coluna, destinos, qnt_destinos)==1){break;}
                else{andar(mapa_usado, posicao, coluna, destinos, qnt_destinos);}
            case 'a':
                if(andar(mapa_usado, posicao, -2, destinos, qnt_destinos)==1){break;}
                else{andar(mapa_usado, posicao, -2, destinos, qnt_destinos);}
            case 'd':
                if(andar(mapa_usado, posicao, 2, destinos, qnt_destinos)==1){break;}
                else{andar(mapa_usado, posicao, 2, destinos, qnt_destinos);}
        }
        
        if(condicaoDeVitoria(qnt_destinos, coluna, linha, mapa_usado)==1){
            system("clear");
            printf("%s", mapa_usado);
            printf("VOCE VENCEUUUU!!!");
            break;
        }

        system("clear");

    }


    return 0;
}