#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRA 100



// Função para imprimir a forca de acordo com o número de erros
void forca(int erro) {
    if (erro == 0) {
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
    } else if (erro == 1) {
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|           0");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n|");
    } else if (erro == 2) {
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|           0");
        printf("\n|           |");
        printf("\n|");
        printf("\n|");
        printf("\n|");
    } else if (erro == 3) {
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|           0");
        printf("\n|          -|");
        printf("\n|            ");
        printf("\n|");
        printf("\n|");
    } else if (erro == 4) {
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|           0");
        printf("\n|          -|-");
        printf("\n|            ");
        printf("\n|");
        printf("\n|");
    } else if (erro == 5) {
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|           0");
        printf("\n|          -|-");
        printf("\n|          / ");
        printf("\n|");
        printf("\n|");
    } else if (erro == 6) {
        system("cls");
        printf("\n-------------");
        printf("\n|           |");
        printf("\n|           0");
        printf("\n|          -|-");
        printf("\n|          / \\");
        printf("\n|");
        printf("\n|");
        printf("\n Fim de Jogo\n");
    }
}

// Função para escolher uma palavra aleatória de acordo com a categoria selecionada
void aleatorio(const char *animais, const char *objetos, const char *cores, const char *paises, const char *esportes, const char *palavras) {
    FILE *file;
    int choice;
    char palavraAleatoria[MAX_PALAVRA];
    char letrasErradas[MAX_PALAVRA];
    int numErros = 0;
    char res;

    do {
        // Menu para escolher a categoria do jogo
        printf("\n\n\t\t\tInforme a categoria que você deseja jogar: \n\n");
        printf("\t\t\t1 - Animais\n");
        printf("\t\t\t2 - Objetos\n");
        printf("\t\t\t3 - Cores\n");
        printf("\t\t\t4 - Países\n");
        printf("\t\t\t5 - Esportes\n");
        printf("\t\t\t6 - Qualquer categoria\n");
        printf("\t\t\t7 - Voltar\n");
        printf("\t\t\t");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                file = fopen(animais, "r");
                break;
            case 2:
                file = fopen(objetos, "r");
                break;
            case 3:
                file = fopen(cores, "r");
                break;
            case 4:
                file = fopen(paises, "r");
                break;
            case 5:
                file = fopen(esportes, "r");
                break;
            case 6:
                file = fopen(palavras, "r");
                break;
            case 7:
                return; // Voltar sem iniciar o jogo
            default:
                printf("\n\t\t\tOpção inválida.\n");
                return; // Voltar sem iniciar o jogo
        }

        int acabou = 0;
        int numPalavras = 0;
        int contador = 0;

        if (file == NULL) {
            printf("\n\t\t\tNão foi possível abrir o arquivo.\n");
            return;
        }

        char sec[MAX_PALAVRA];
        while (fgets(sec, MAX_PALAVRA, file) != NULL) {
            numPalavras++;
        }

        srand(time(NULL));
        int p_aleatoria = rand() % numPalavras;

        rewind(file);

        while (fgets(sec, MAX_PALAVRA, file) != NULL) {
            if (contador == p_aleatoria) {
                sec[strcspn(sec, "\n")] = '\0';
                strcpy(palavraAleatoria, sec);
                break;
            }
            contador++;
        }

        fclose(file);

        // Jogo da Forca

        printf("\t\t\tA palavra tem %lu caracteres\n", strlen(palavraAleatoria));
        getch();
        system("cls");

        char under[MAX_PALAVRA];
        strcpy(under, palavraAleatoria); // copia a palavra secreta para o under

        int erros = 0;
        char letra;

        for (int i = 0; i < strlen(under); i++) { // substitui as letras por "_"
            under[i] = '_';
        }

        while (acabou == 0) {
            // Imprimir a forca
            forca(erros);

            // Imprimir os underline para cada letra
            for (int i = 0; i < strlen(under); i++) {
                printf("%c ", under[i]);
            }

            // Recebe a letra
            printf("\nLetra: ");
            scanf(" %c", &letra);

            // Verificação se a letra já foi digitada antes
            int letraRepetida = 0;

            for (int i = 0; i < numErros; i++) {
                if (letrasErradas[i] == letra) {
                    letraRepetida = 1;
                    getch();
                    break;
                }
            }
            if (letraRepetida) {
                system("cls");
                continue; // Volta para o início do loop e solicita outra letra
            }

            // Se a letra estiver correta, atualiza a palavra na tela e verifica se o jogo acabou
            int se_errou = 1; // 1 = sim, 0 = não

            for (int i = 0; i < strlen(under); i++) {
                if (letra == palavraAleatoria[i]) { // correta
                    under[i] = letra;
                    se_errou = 0;
                }
            }

            // Se não, incrementa os erros
            if (se_errou == 1) {
                letrasErradas[numErros] = letra;
                numErros++;
                erros++;
            }

            // Verifica se o jogo acabou
            int letras_certas = 0;

            for (int i = 0; i < strlen(under); i++) {
                if (under[i] != '_') {
                    letras_certas++;
                }
            }

            if (letras_certas == strlen(under)) { // Ganhou
                printf("\nParabéns! Você acertou a palavra: %s\n", palavraAleatoria);
                getch();
                acabou = 1;
            }

            if (erros >= 6) { // Perdeu
                printf("\nA palavra era: %s\n", palavraAleatoria);
                printf("\nVocê perdeu!\n");
                getch();
                acabou = 1;
            }

            system("cls");
        }

        printf("\nDeseja jogar novamente? (S/N)\n");
        scanf(" %c", &res);

        system("cls");
    } while (res == 's' || res == 'S');
}

int main() {

    setlocale(LC_ALL, "");

    aleatorio("animais.txt", "objetos.txt", "cores.txt", "paises.txt", "esportes.txt", "palavras.txt");

    return 0;
}


