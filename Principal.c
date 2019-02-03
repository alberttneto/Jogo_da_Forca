#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Imprir campo na tela
void imprimirCampo(char campo[20][20]){

    int i, j;

    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }

}

// Criando campo
void criaCampo(char campo[20][20], int tamanho){

    int i, j;

    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            campo[i][j] = ' ';
        }
    }

    //Criando forca-------
    for(i = 6; i < 14;i++){
        campo[3][i] = '_';
    }

    campo[4][5] = '|';

    for(i = 4; i < 14;i++){
        campo[i][14] = '|';
    }
    j = 12;
    while(j < 17){
        campo[13][j] = '_';
       j++;
        if(j == 14){
           j++;
        }
    }

    // Inclui tamanho da palavra no campo
    for(i = 0; i < tamanho; i++){
        campo[16][i + 2] = '_';
    }
    //Fim forca----------
}


// Funcao para sortear palavra para forca
void escolhePalavra(char palavra[40]){

    int opcao, sorteio;
    char a1[] = "macaco", a2[] = "leao", a3[] = "golfinho";
    char o1[] = "faca", o2[] = "lapis", o3[] = "chave";
    char c1[] = "amarelo", c2[] = "verde", c3[] = "azul";

    srand(time(NULL));
    sorteio = rand() % 3;
    printf("Informe grupo de palavras para forca: \n"
           "1 - Animais \n"
           "2 - Objetos \n"
           "3 - Cores\n");
    scanf("%d", &opcao);


    switch(opcao){

        case 1:
            if(sorteio == 0){
                strcpy(palavra, a1);
            } else if(sorteio == 1){
                strcpy(palavra, a2);
            } else{
                strcpy(palavra, a3);
            }
        break;

        case 2:
            if(sorteio == 0){
                strcpy(palavra, o1);
            } else if(sorteio == 1){
                strcpy(palavra, o2);
            } else{
                strcpy(palavra, o3);
            }
        break;

        case 3:
            if(sorteio == 0){
                strcpy(palavra, c1);
            } else if(sorteio == 1){
                strcpy(palavra, c2);
            } else{
                strcpy(palavra, c3);
            }
        break;

        default: printf("Opcao incorreta!");
        break;
    }

}

// funcao monta forca quando erra letra
void forca(char campo[20][20], int erro){

    if(erro == 5){
        campo[5][5] = 'O';
    } else if(erro == 4){
        campo[6][5] = '|';
        campo[7][5] = '|';
    } else if(erro == 3){
        campo[6][4] = '/';
    } else if(erro == 2){
        campo[6][6] = '\\';
    } else if(erro == 1){
        campo[8][4] = '/';
    } else if(erro == 0){
        campo[8][6] = '\\';
    }

}

// Funcao recebe letra e verifica se ja foi usada
int verificaLetra(char palavra[40], char letrasTent[30], int tentativas){

    char letra;
    int i, tamanho, tamanho2, acerto = 0, jaTentou = 0;

    tamanho = strlen(palavra);
    tamanho2 = strlen(letrasTent);

    do{
        printf("Informe letra: ");
        setbuf(stdin, NULL);
        scanf("%c", &letra);

        for(i = 0; i < tamanho2 ; i++){
            if(letra == letrasTent[i]){
                printf("Ja tentou\n");
                jaTentou = 0;
                break;
            } else{
                jaTentou = 1;
            }
        }


    } while(jaTentou == 0);

    letrasTent[tentativas] = letra;

    for(i = 0; i < tamanho; i++){
        if(letra == palavra[i]){
            acerto = 1;
            break;
        }
    }

    return acerto;
}

int verificaVitoria(char campo[20][20], char palavra[40], int tamanho){

    int i, igual = 0;

    for(i = 0; i < tamanho; i++){
        if(campo[16][i+2] == palavra[i]){
            igual++;
        }
    }

    if(igual == tamanho){
        return 1;
    }else{
        return 0;
    }
}

void jogar(char palavra[40], char campo[20][20], int tamanho){

    int i, erros = 6, ganhou = 0, tentativas = 0, result;
    char letrasTent[30] = {' '};

    while(erros != 0 && ganhou != 1){

        result = verificaLetra(palavra, letrasTent, tentativas);

        // Se errou reduz tentativas
        if(result == 0){
            erros--;
            forca(campo, erros); // funcao monta forca

            imprimirCampo(campo); // imprimir campo atualizado.

        // Se não errou inclui letra no campo
        } else{
            for(i = 0; i < tamanho; i++){
                if(letrasTent[tentativas] == palavra[i]){
                    campo[16][i + 2] = palavra[i];
                }
            }
            imprimirCampo(campo); // imprimir campo atualizado.
        }
        tentativas++;

        ganhou = verificaVitoria(campo, palavra, tamanho);
    }

    if(ganhou == 1){
        printf("======================================\n"
                "      PARABENS VOCE GANHOU!!         \n"
                "=======================================");
    }else{
        printf("======================================\n"
                "            VOCE PERDEU!!            \n"
                "=======================================");
    }

}

int main(){

    int  tamanho = 0;
    char campo[20][20], palavra[40];

    escolhePalavra(palavra); // funcao sorteia palavra para ser adivinhada
    tamanho = strlen(palavra);
    criaCampo(campo, tamanho); //funcao para criar o campo

    //Imprimindo forca
    imprimirCampo(campo);

    // Inicia jogo
    jogar(palavra, campo, tamanho);

    return 0;
}



