#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_CIDADES 32

typedef struct {
    char estado;
    char codigo[4];
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
} Cidade;

Cidade cidades[MAX_CIDADES];
int total_cidades = 0;

int validar_estado(char estado) {
    estado = toupper(estado);
    return (estado >= 'A' && estado <= 'H');
}

int validar_codigo(const char *codigo) {
    int len = strlen(codigo);
    if (len < 1 || len > 2) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(codigo[i])) {
            return 0;
        }
    }
    int numero = atoi(codigo);
    return (numero >= 1 && numero <= 4);
}

void formatar_codigo(char *codigo) {
    if (strlen(codigo) == 1) {
        codigo[1] = codigo[0];
        codigo[0] = '0';
        codigo[2] = '\0';
    }
}

int validar_nome(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int validar_numero_inteiro(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int validar_numero_decimal(const char *str) {
    int ponto_encontrado = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            if (ponto_encontrado) {
                return 0;
            }
            ponto_encontrado = 1;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void cadastrar_carta() {
    if (total_cidades >= MAX_CIDADES) {
        printf("Limite de cidades atingido!\n");
        return;
    }

    Cidade nova_cidade;

    printf("Cadastro de Carta de Cidade\n");

    do {
        printf("Digite o estado (A-H): ");
        scanf(" %c", &nova_cidade.estado);
        nova_cidade.estado = toupper(nova_cidade.estado);
        if (!validar_estado(nova_cidade.estado)) {
            printf("Estado inválido! Digite uma letra de A a H.\n");
        }
    } while (!validar_estado(nova_cidade.estado));

    char codigo_temp[4];
    do {
        printf("Digite o código da carta (1-4 ou 01-04): ");
        scanf("%s", codigo_temp);
        if (!validar_codigo(codigo_temp)) {
            printf("Código inválido! Digite um número entre 1 e 4.\n");
        }
    } while (!validar_codigo(codigo_temp));

    formatar_codigo(codigo_temp);
    strcpy(nova_cidade.codigo, codigo_temp);

    do {
        printf("Digite o nome da cidade: ");
        scanf(" %[^\n]", nova_cidade.nome);
        if (!validar_nome(nova_cidade.nome)) {
            printf("Nome inválido! Use apenas letras e espaços.\n");
        }
    } while (!validar_nome(nova_cidade.nome));

    char populacao_temp[20];
    do {
        printf("Digite a população: ");
        scanf("%s", populacao_temp);
        if (!validar_numero_inteiro(populacao_temp)) {
            printf("População inválida! Digite apenas números.\n");
        } else {
            nova_cidade.populacao = atoi(populacao_temp);
        }
    } while (!validar_numero_inteiro(populacao_temp));

    char area_temp[20];
    do {
        printf("Digite a área em km²: ");
        scanf("%s", area_temp);
        if (!validar_numero_decimal(area_temp)) {
            printf("Área inválida! Digite apenas números e no máximo um ponto.\n");
        } else {
            nova_cidade.area = atof(area_temp);
        }
    } while (!validar_numero_decimal(area_temp));

    char pib_temp[20];
    do {
        printf("Digite o PIB: ");
        scanf("%s", pib_temp);
        if (!validar_numero_decimal(pib_temp)) {
            printf("PIB inválido! Digite apenas números e no máximo um ponto.\n");
        } else {
            nova_cidade.pib = atof(pib_temp);
        }
    } while (!validar_numero_decimal(pib_temp));

    char pontos_temp[20];
    do {
        printf("Digite o número de pontos turísticos: ");
        scanf("%s", pontos_temp);
        if (!validar_numero_inteiro(pontos_temp)) {
            printf("Número de pontos turísticos inválido! Digite apenas números.\n");
        } else {
            nova_cidade.pontos_turisticos = atoi(pontos_temp);
        }
    } while (!validar_numero_inteiro(pontos_temp));

    cidades[total_cidades] = nova_cidade;
    total_cidades++;

    printf("\nCarta cadastrada com sucesso!\n\n");
}

void exibir_cartas() {
    if (total_cidades == 0) {
        printf("Nenhuma cidade cadastrada.\n");
        return;
    }

    for (int i = 0; i < total_cidades; i++) {
        printf("Estado: %c\n", cidades[i].estado);
        printf("Código da Carta: %s\n", cidades[i].codigo);
        printf("Nome da Cidade: %s\n", cidades[i].nome);
        printf("População: %d\n", cidades[i].populacao);
        printf("Área: %.2f km²\n", cidades[i].area);
        printf("PIB: %.2f bilhões de reais\n", cidades[i].pib);
        printf("Número de Pontos Turísticos: %d\n\n", cidades[i].pontos_turisticos);
    }
}

int main() {
    int opcao;

    do {
        printf("1. Cadastrar Carta\n");
        printf("2. Exibir Cartas Cadastradas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_carta();
                break;
            case 2:
                exibir_cartas();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}