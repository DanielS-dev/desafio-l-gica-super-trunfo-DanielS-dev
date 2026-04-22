#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char estado[3], codigoDaCarta[3], nomeDaCidade[51];
    int numeroDePontosTuristicos;
    unsigned long int populacao;
    float areaEmKM, PIB, densidadePopulacional, PIBPerCapita;
} Carta;

typedef struct {
    char *nome;
    float valor1, valor2;
} Atributo;

int compararAtributo(float atributo1, float atributo2){
    if (atributo1 > atributo2) return 1;
    else if (atributo1 < atributo2) return 2;
    else return 0;
}

void compararEAtribuir (float atributo1, float atributo2, int *pontos1, int *pontos2){
    int resultado = compararAtributo(atributo1, atributo2);
    if (resultado == 1) (*pontos1)++;
    else if (resultado == 2) (*pontos2)++;
}

void imprimirVencedor(int pontos1, int pontos2){
    if (pontos1 == pontos2) printf("Empate!\n");
    else if (pontos1 > pontos2) printf("A Carta 1 venceu!\n");
    else printf("A Carta 2 venceu!\n");

    system("pause");
}

void compararDuasCaractecristicas(
    char *nomeAtributo1, char *nomeAtributo2,
    float carta1_atributo1, float carta2_atributo1,
    float carta1_atributo2, float carta2_atributo2,
    int *pontos1, int *pontos2
){
    printf("Usando os atributos %s e %s para comparação\n", nomeAtributo1, nomeAtributo2);
    printf("%s da Cidade 1: %.2f\n", nomeAtributo1, carta1_atributo1);
    printf("%s da Cidade 2: %.2f\n", nomeAtributo1, carta2_atributo1);
    printf("%s da Cidade 1: %.2f\n", nomeAtributo2, carta1_atributo2);
    printf("%s da Cidade 2: %.2f\n", nomeAtributo2, carta2_atributo2);

    float soma1 = carta1_atributo1 + carta1_atributo2;
    float soma2 = carta2_atributo1 + carta2_atributo2;

    compararEAtribuir(carta1_atributo1, carta2_atributo1, pontos1, pontos2);
    compararEAtribuir(carta1_atributo2, carta2_atributo2, pontos1, pontos2);
    compararEAtribuir(soma1, soma2, pontos1, pontos2);

    imprimirVencedor(*pontos1, *pontos2);
}

void limparBuffer(){
    while (getchar() != '\n');
}

Carta lerCartas(){
    Carta carta;

    printf("\nDigite os dados da Carta!\n\n");

    printf("Digite o Estado da carta (Abreviação, ex: SP - São Paulo): ");
    scanf(" %2s", carta.estado);
    limparBuffer();

    while (strlen(carta.estado) != 2){
        printf("\nO Estado deve ter exatamente 2 caracteres!\n");
        printf("Digite o estado da carta novamente: ");
        scanf(" %2s", carta.estado);
        limparBuffer();
    }

    printf("Digite o Código da carta: ");
    scanf(" %2s", carta.codigoDaCarta);
    limparBuffer();

    while (strlen(carta.codigoDaCarta) != 2){
        printf("\nO código deve ter exatamente 2 caracteres!\n");
        printf("Digite o código da carta novamente: ");
        scanf(" %2s", carta.codigoDaCarta);
        limparBuffer();
    }

    printf("Digite o Nome da cidade: ");
    fgets(carta.nomeDaCidade, 51, stdin);

    if (strcspn(carta.nomeDaCidade, "\n") == 50) {
        limparBuffer();
    }

    carta.nomeDaCidade[strcspn(carta.nomeDaCidade, "\n")] = '\0';

    printf("Digite a quantidade da População da cidade: ");

    while (scanf("%lu", &carta.populacao) != 1 || carta.populacao == 0){
        limparBuffer();
        if(carta.populacao == 0)
            printf("\nA quantidade da População não pode ser 0!\n");
        else
            printf("\nEntrada Inválida! Digite apenas números.\n");
        printf("Digite novamente a quantidade da População da cidade: ");
    }
    limparBuffer();

    printf("Digite a Área em KM da cidade: ");

    while (scanf("%f", &carta.areaEmKM) != 1 || carta.areaEmKM == 0){
        limparBuffer();
        if(carta.areaEmKM == 0)
            printf("\nA Área em KM não pode ser 0!\n");
        else
            printf("\nEntrada Inválida! Digite apenas números.\n");
        printf("Digite novamente a Área em KM da cidade: ");
    }
    limparBuffer();

    printf("Digite o PIB da cidade: ");

    while (scanf("%f", &carta.PIB) != 1 || carta.PIB == 0){
        limparBuffer();
        if(carta.PIB == 0)
            printf("\nA quantidade do PIB não pode ser 0!\n");
        else
            printf("\nEntrada Inválida! Digite apenas números.\n");
        printf("Digite novamente a quantidade do PIB da cidade: ");
    }
    limparBuffer();

    printf("Digite o numero de Pontos Turísticos da cidade: ");

    while (scanf("%i", &carta.numeroDePontosTuristicos) != 1){
        limparBuffer();
        printf("\nEntrada Inválida! Digite apenas números.\n");
        printf("Digite novamente a quantidade de Pontos Turísticos da cidade: ");
    }
    limparBuffer();

    carta.densidadePopulacional = (float) carta.populacao / carta.areaEmKM;
    carta.PIBPerCapita = carta.PIB / (float) carta.populacao;

    return carta;
}

int menu(Atributo atributos[], int total){
    printf("\nEscolha o primeiro atributo para comparação:\n\n");
    printf("Sair - 0\n");
    for (int i = 0; i < total; i++)
        printf("%s - %d\n", atributos[i].nome, i + 1);

    int opcao;
    printf("\nDigite a opção desejada: ");
    while (scanf("%i", &opcao) != 1) {
        limparBuffer();
        printf("Entrada inválida! Digite um número: ");
    }
    limparBuffer();
    printf("\n");
    return opcao;
}

int main () {
    setlocale(LC_ALL, ".UTF-8");

    Carta cartas[2];

    cartas[0] = lerCartas();
    cartas[1] = lerCartas();

    // Mostrando as Cartas registradas
    printf("\nCartas Cadastradas:\n");

    for (int i = 0; i < sizeof(cartas) / sizeof(cartas[0]); i++){
        printf("\nCarta número %i!\n\n", (i+1));
        printf("Estado: %s\n", cartas[i].estado);
        printf("Código da Carta: %s\n", cartas[i].codigoDaCarta);
        printf("Nome da Cidade: %s\n", cartas[i].nomeDaCidade);
        printf("Quantidade da População: %lu\n", cartas[i].populacao);
        printf("Área em KM: %.2f\n", cartas[i].areaEmKM);
        printf("PIB: %.2f\n", cartas[i].PIB);
        printf("Número de Pontos Turísticos: %i\n", cartas[i].numeroDePontosTuristicos);
        printf("Densidade Populacional: %.2f\n", cartas[i].densidadePopulacional);
        printf("PIB per Capita: %.2f\n", cartas[i].PIBPerCapita);
    }

    Atributo atributos[] = {
        {"População", (float)cartas[0].populacao, (float)cartas[1].populacao},
        {"Área em KM²", cartas[0].areaEmKM, cartas[1].areaEmKM},
        {"PIB", cartas[0].PIB, cartas[1].PIB},
        {"Pontos Turísticos", (float)cartas[0].numeroDePontosTuristicos, (float)cartas[1].numeroDePontosTuristicos},
        {"Densidade Populacional",cartas[0].densidadePopulacional, cartas[1].densidadePopulacional},
        {"PIB per Capita", cartas[0].PIBPerCapita, cartas[1].PIBPerCapita},
    };

    int total = sizeof(atributos) / sizeof(atributos[0]);
    int opcao;

    do {
        int pontosCarta1 = 0, pontosCarta2 = 0;
        opcao = menu(atributos, total);

        if (opcao == 0) break;

        if (opcao < 1 || opcao > total) {
            printf("Opção Inválida!\n");
            system("pause");
            continue;
        }

        int idx1 = opcao - 1;

        // monta lista de atributos disponíveis para o segundo atributo
        int disponiveis[5];
        int count = 0;
        printf("\nAgora escolha um segundo atributo para comparação:\n\n");
        for (int i = 0; i < total; i++) {
            if (i != idx1) {
                disponiveis[count++] = i;
                printf("%s - %d\n", atributos[i].nome, count);
            }
        }

        int opcao2;
        printf("\nDigite a opção desejada: ");
        while (scanf("%i", &opcao2) != 1 || opcao2 < 1 || opcao2 > count) {
            limparBuffer();
            printf("Opção inválida! Digite um número entre 1 e %d: ", count);
        }
        limparBuffer();

        int idx2 = disponiveis[opcao2 - 1];

        compararDuasCaractecristicas(
            atributos[idx1].nome, atributos[idx2].nome,
            atributos[idx1].valor1, atributos[idx2].valor1,
            atributos[idx1].valor2, atributos[idx2].valor2,
            &pontosCarta1, &pontosCarta2
        );

    } while (opcao != 0);

    return 0;
}
