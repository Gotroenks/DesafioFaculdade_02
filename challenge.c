#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

void menu();

// Strutc
struct types {
    char name[99];
    float quantity;
    float price;

    int month;
    int year;
};

// Util
void clearScreen() { // Limpa tela
    system("cls");
}

int searchName() { // Pesquisa o nome
    // Declaracao de struct
    struct types types[4];

    // Variaveis
    char searchedName[99];
    int i, j;

    // Declarando o arquivo
    FILE *f;

    // Limpa tela
    clearScreen();

    // Nome que ira ser pesquisado
    printf("\tProcurar produto pelo nome: ");
    scanf("%s", &searchedName);

    // Abre o arquivo product.txt
    f = fopen("product.txt", "r");

    // Verificando o nome pesquisado e comparando com os dados inseridos
    for(i = 0; i < 4; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        for(j = 0; types[i].name[j] != '\0'; j++) {
            if(searchedName[j] != types[i].name[j]) {
                break;
            }
        }

        if(searchedName[j] == '\0' && types[i].name[j] == '\0') {
            // Limpa tela
            clearScreen();

            // Exibindo os valores encontrados
            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }

            // Pula linha
            printf("\n");

            // Fecha o arquivo product.txt
            fclose(f);

            return i;
        }
    }

    // Fecha o arquivo product.txt
    fclose(f);
     
    return -1;
}

// App
void dataEntries() { // Entrada de dados
    // Declaracao de struct
    struct types types[4];

    // Variaveis
    int i, j;

    // Declarando o arquivo
    FILE *f;

    // Limpa tela
    clearScreen();

    // Valores do struct ficando NULL
    if(types[0].name[0] == NULL) {
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                types[i].name[j] == NULL;
            }
        }
    }

    // Entrada de dados
    for(i = 0; i < 4; i++) {
        printf("\tDigite o %d produto: ", i + 1);
        scanf("%s", &types[i].name);

        printf("\tDigite a quantidade: ");
        scanf("%f", &types[i].quantity);

        printf("\tDigite a preco: ");
        scanf("%f", &types[i].price);

        printf("\tDigite a mes: ");
        scanf("%d", &types[i].month);

        printf("\tDigite a ano: ");
        scanf("%d", &types[i].year);

        // Pula linha
        printf("\n");
    }

    // Abre o arquivo product.txt
    f = fopen("product.txt", "w");

    // Dados entrando no arquivo product.txt
    for(i = 0; i < 4; i++) {
        fwrite(&types[i].name, sizeof(types[i].name), 1, f);
        fwrite(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fwrite(&types[i].price, sizeof(types[i].price), 1, f);
        fwrite(&types[i].month, sizeof(types[i].month), 1, f);
        fwrite(&types[i].year, sizeof(types[i].year), 1, f);
    }

    // Pula linha
    printf("\n");

    // Fecha o arquivo product.txt
    fclose(f);

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu();
}

void dataList() { // Lista os dados
    // Declaracao de struct
    struct types types[4];

    // Variaveis
    int i, j;
    int error = 0;

    // Declarando o arquivo
    FILE *f;

    // Limpa tela
    clearScreen();

    // Abre o arquivo product.txt
    f = fopen("product.txt", "r");

    // Verificando se existe o arquivo product.txt
    if(f == NULL) {
        clearScreen();
        printf(YEL "\tATENCAO: Nenhum arquivo encontrado." RESET);
        Sleep(1500);

        clearScreen();
        menu();
    }

    // Verificando se o struct esta NULL
    if(types[0].name[0] == NULL) {
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                types[i].name[j] == NULL;
            }
        }
    }

    // Lendo os dados
    for(i = 0; i < 4; i++) {
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);
    }

    for(i = 0; i < 4; i++) {
        //Verificando se os dados estao NULL
        if(types[i].name[0] == NULL) {
            error++;
            break;
        } else {
            // Exibindo os dados
            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            // Verificando se o mes tem 1 digito
            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }

            // Pula linha
            printf("\n");
        }
    }

    // Fecha o arquivo product.txt
    fclose(f);

    // Verificando se existe algum registro
    if(error == 4) {
        printf("\tNenhum registro encontrado.\n");
    }

    // Pula linha
    printf("\n");

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu();
}

void dataListPriceRange() { // Lista os dados pela faixa de preco
    // Declaracao de struct
    struct types types[4];

    // Variaveis
    float searchedPriceRange1 = 0;
    float searchedPriceRange2 = 0;
    int i, j;
    int error = 0;

    // Declarando o arquivo
    FILE *f;

    // Limpa tela
    clearScreen();

    // Entrada de dados
    printf("\tProcurar produto pela faixa de preco 1: ");
    scanf("%f", &searchedPriceRange1);

    printf("\tProcurar produto pela faixa de preco 2: ");
    scanf("%f", &searchedPriceRange2);

    // Abre o arquivo product.txt
    f = fopen("product.txt", "r");

    // Limpa tela
    clearScreen();

    // Exibindo a faixa de preco que o usuaria digitou
    printf("\tFaixa de preco: R$ %.2f - R$ %.2f\n\n", searchedPriceRange1, searchedPriceRange2);

    for(i = 0; i < 4; i++) {
        // Lendo os dados
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        // Exibindo os dados apos verificacao da faixa de preco
        if(types[i].price >= searchedPriceRange1 && types[i].price <= searchedPriceRange2) {
            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            // Verificando se o mes tem 1 digito
            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }

            // Pula linha
            printf("\n");
        } else {
            error++;
        }
    }

    // Fecha o arquivo product.txt
    fclose(f);

    // Verificando se existe algum registro
    if(error == 4) {
        printf("\tNenhum registro encontrado.\n");
    }

    // Pula linha
    printf("\n");

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu();
}

void dataSearchName() { // Pesquisar dados por nome
    // Variaveis
    int change;
    int search;

    // Chamada da funcao 
    search = searchName();

    // Verificando se existe algum registro
    if(search == -1) {
        clearScreen();
        printf("\tNenhum registro encontrado.\n");
    }

    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela 
    clearScreen();

    // Chamada do menu
    menu();
}

void dataSearchValidateDate() { // Pesquisar dados pela data de validade
    // Declaracao de struct
    struct types types[4];

    // Variaveis
    int searchedValidateDateMonth;
    int searchedValidateDateYear;
    int i, j;
    int error = 0;

    // Declarando o arquivo
    FILE *f;

    // Limpa tela 
    clearScreen();

    // Entrada de dados
    printf("\tDigite o mes: ");
    scanf("%d", &searchedValidateDateMonth);

    printf("\tDigite o ano: ");
    scanf("%d", &searchedValidateDateYear);

    // Abre o arquivo product.txt
    f = fopen("product.txt", "r");

    // Limpa tela
    clearScreen();

    for(i = 0; i < 4; i++) {
        // Lendo os dados
        fread(&types[i].name, sizeof(types[i].name), 1, f);
        fread(&types[i].quantity, sizeof(types[i].quantity), 1, f);
        fread(&types[i].price, sizeof(types[i].price), 1, f);
        fread(&types[i].month, sizeof(types[i].month), 1, f);
        fread(&types[i].year, sizeof(types[i].year), 1, f);

        // Exibindo os dados apos verificacao da validade do produto
        if(types[i].month == searchedValidateDateMonth && types[i].year == searchedValidateDateYear) {
            printf("\tProduto %d: %s\n", i + 1, types[i].name);
            printf("\tQuantidade: %.2f\n", types[i].quantity);
            printf("\tValor: R$ %.2f\n", types[i].price);

            // Verificando se o mes tem 1 digito
            if(types[i].month > 9) {
                printf("\tValidade: %d/%d\n", types[i].month, types[i].year);
            } else {
                printf("\tValidade: 0%d/%d\n", types[i].month, types[i].year);
            }

            // Pula linha
            printf("\n");
        } else {
            error++;
        }
    }

    // Fecha o arquivo product.txt
    fclose(f);

    // Verificando se existe algum registro
    if(error == 4) {
        printf("\tNenhum registro encontrado.\n");
    }

    // Pula linha
    printf("\n");
    
    // Pausando a aplicacao
    printf("\tPressione qualquer tecla para continuar...");
    getch();

    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu();
}

void quit() { // Sair do programa
    // Limpa tela
    clearScreen();

    // Contador do tempo de fechamento do progrma
    for(int i = 3; i > -1; i--) {
        clearScreen();
        printf("\tFechando em %d", i);
        Sleep(1000);
    }

    // Fechando programa
    exit(0);
}

// Menu
void menu() {
    int change;
    // Menu Top
    printf("\t|-------------------------------------------------------------------------|\n");

    // Menu Item
    printf("\t| 1 - Entrada de dados                                                    |\n");
    printf("\t| 2 - Listar todos os produtos                                            |\n");
    printf("\t| 3 - Listar produtos por faixa de preco                                  |\n");
    printf("\t| 4 - Pesquisar um produto pelo nome completo                             |\n");
    printf("\t| 5 - Pesquisar data de validade (mes/ano)                                |\n");
    printf("\t| 6 - Altera produto pesquisado pelo nome completo                        |\n");
    printf("\t| 7 - Altera quantidade em estoque (entrada e saida) pesquisado pelo nome |\n");
    printf("\t| 8 - Altera preco de um produto pesquisado pelo nome completo            |\n");
    printf("\t| 9 - Excluir produto                                                     |\n");
    printf("\t| 10 - Sair                                                               |\n");

    // Menu bottom
    printf("\t|-------------------------------------------------------------------------|\n");

    // Pula a linha
    printf("\n");

    // Opcao escolhida do usario
    printf("\tEscolha uma opcao: ");
    scanf("%d", &change);

    // Escolhas
    switch(change) {
        case 1: {
            // Entrada de dados
            dataEntries();
            break;
        }

        case 2: {
            // Lista de dados
            dataList();
            break;
        }

        case 3: {
            // Lista de dados pela faixa de preco
            dataListPriceRange();
            break;
        }

        case 4: {
            // Pesquisa dados pelo nome 
            dataSearchName();
            break;
        }

        case 5: {
            // Pesquisa dados pela data de validade
            dataSearchValidateDate();
            break;
        }

        case 6: {
            break;
        }

        case 7: {
            break;
        }

        case 8: {
            break;
        }

        case 9: {
            break;
        }

        case 10: {
            // Sair do programa
            quit();
            break;
        }

        default: {
            // Limpa tela
            clearScreen();

            // WARNING
            printf(YEL "\tAtencao: Ocorreu um erro no sistema.\n" RESET);
            printf("\tPor favor, digite um numero de 1 a 10.\n\n");

            // Pausando a aplicacao
            printf("\tPressione qualquer tecla ...\n");
            getch();

            // Limpa tela
            clearScreen();

            // Chamada do menu
            menu();
        }
    }
}

int main(void) {
    // Limpa tela
    clearScreen();

    // Chamada do menu
    menu();

    return 0;
}
