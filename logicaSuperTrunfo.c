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
    if (pontos1 == pontos2) printf("Empate!");
    else if (pontos1 > pontos2) printf("A Carta 1 venceu!");
    else printf("A Carta 2 venceu!");

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

        if(carta.populacao == 0){
            printf("\nA quantidade da População não pode ser 0!\n");
        } else {
            printf("\nEntrada Inválida! Digite apenas números.\n");
        }

        printf("Digite novamente a quantidade da População da cidade: ");
    }

    limparBuffer();

    printf("Digite a Área em KM da cidade: ");

    while (scanf("%f", &carta.areaEmKM) != 1 || carta.areaEmKM == 0){
        limparBuffer();

        if(carta.areaEmKM == 0){
            printf("\nA Área em KM não pode ser 0!\n");
        } else {
            printf("\nEntrada Inválida! Digite apenas números.\n");
        }

        printf("Digite novamente a Área em KM da cidade: ");
    }

    limparBuffer();

    printf("Digite o PIB da cidade: ");

    while (scanf("%f", &carta.PIB) != 1 || carta.PIB == 0){
        limparBuffer();

        if(carta.PIB == 0){
            printf("\nA quantidade do PIB não pode ser 0!\n");
        } else {
            printf("\nEntrada Inválida! Digite apenas números.\n");
        }

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

int main () {
    setlocale(LC_ALL, ".UTF-8");

    Carta cartas[2];

    cartas[0] = lerCartas();
    cartas[1] = lerCartas();

    //Menu
    printf("\nEscolha uma opção de comparação de atributos:\n\n");
    printf("Nome do País - 1\n");
    printf("População - 2\n");
    printf("Área - 3\n");
    printf("PIB - 4\n");
    printf("Número de Pontos Turísticos - 5\n");
    printf("Densidade Populacional - 6\n\n");

    int opcao, opcao2, cartaVencedora = 0, somaDosAtributos, somaDosAtributos2;
    int pontosCarta1 = 0, pontosCarta2 = 0;

    printf("Digite a opção desejada: ");
    scanf("%i", &opcao);
    printf("\n");

    switch (opcao) {
    case 1:
        printf("País 1: %s", cartas[0].nomeDaCidade);
        printf("País 2: %s", cartas[1].nomeDaCidade);
        break;
    case 2:
        printf("\n\nAgora escolha um segundo atributo para comparação!\n");
        printf("Área - 1\n");
        printf("PIB - 2\n");
        printf("Número de Pontos Turísticos - 3\n");
        printf("Densidade Populacional - 4\n\n");

        scanf("%i", &opcao2);
        switch (opcao2) {
        case 1:
            compararDuasCaractecristicas("População", "Área em KM²",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            compararDuasCaractecristicas("População", "PIB",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].PIB, cartas[1].PIB, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            compararDuasCaractecristicas("População", "Número de Pontos Turísticos",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            compararDuasCaractecristicas("População", "Densidade Populacional",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional, 
                &pontosCarta1, &pontosCarta2);
            break;
        
        default:
            printf("Opção Invalida!");
            break;
        }
        break;
    case 3:
        printf("\n\nAgora escolha um segundo atributo para comparação!\n");
        printf("População - 1\n");
        printf("PIB - 2\n");
        printf("Número de Pontos Turísticos - 3\n");
        printf("Densidade Populacional - 4\n\n");

        scanf("%i", &opcao2);
        switch (opcao2)
        {
        case 1:
            compararDuasCaractecristicas("População", "Área em KM²",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            compararDuasCaractecristicas("PIB", "Área em KM²",
                cartas[0].PIB, cartas[1].PIB,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            compararDuasCaractecristicas("Número de Pontos Turísticos", "Área em KM²",
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            compararDuasCaractecristicas("Densidade Populacional", "Área em KM²",
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        default:
            printf("Opção Invalida!");
            break;
        }
        break;
    case 4:
        printf("\n\nAgora escolha um segundo atributo para comparação!\n");
        printf("Área - 1\n");
        printf("População - 2\n");
        printf("Número de Pontos Turísticos - 3\n");
        printf("Densidade Populacional - 4\n\n");

        scanf("%i", &opcao2);
        switch (opcao2)
        {
        case 1:
            compararDuasCaractecristicas("PIB", "Área em KM²",
                cartas[0].PIB, cartas[1].PIB,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            compararDuasCaractecristicas("População", "PIB",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].PIB, cartas[1].PIB, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            compararDuasCaractecristicas("PIB", "Número de Pontos Turísticos",
                cartas[0].PIB, cartas[1].PIB,
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            compararDuasCaractecristicas("PIB", "Densidade Populacional",
                cartas[0].PIB, cartas[1].PIB,
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional, 
                &pontosCarta1, &pontosCarta2);
            break;
        
        default:
            printf("Opção Invalida!");
            break;
        }
        break;
    case 5:
        printf("\n\nAgora escolha um segundo atributo para comparação!\n");
        printf("Área - 1\n");
        printf("PIB - 2\n");
        printf("População - 3\n");
        printf("Densidade Populacional - 4\n\n");

        scanf("%i", &opcao2);
        switch (opcao2)
        {
        case 1:
            compararDuasCaractecristicas("Número de Pontos Turísticos", "Área em KM²",
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            compararDuasCaractecristicas("Número de Pontos Turísticos", "PIB",
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos,
                cartas[0].PIB, cartas[1].PIB, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            compararDuasCaractecristicas("População", "Número de Pontos Turísticos",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            compararDuasCaractecristicas("Número de Pontos Turísticos", "Densidade Populacional",
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos,
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional, 
                &pontosCarta1, &pontosCarta2);
            break;
        default:
            printf("Opção Invalida!");
            break;
        }
        break;
    case 6:
        printf("\n\nAgora escolha um segundo atributo para comparação!\n");
        printf("Área - 1\n");
        printf("PIB - 2\n");
        printf("Número de Pontos Turísticos - 3\n");
        printf("População - 4\n\n");

        scanf("%i", &opcao2);
        switch (opcao2)
        {
        case 1:
            compararDuasCaractecristicas("Densidade Populacional", "Área em KM²",
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional,
                cartas[0].areaEmKM, cartas[1].areaEmKM, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 2:
            compararDuasCaractecristicas("Densidade Populacional", "PIB",
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional,
                cartas[0].PIB, cartas[1].PIB, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 3:
            compararDuasCaractecristicas("Densidade Populacional", "Número de Pontos Turísticos",
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional,
                cartas[0].numeroDePontosTuristicos, cartas[1].numeroDePontosTuristicos, 
                &pontosCarta1, &pontosCarta2);
            break;
        case 4:
            compararDuasCaractecristicas("População", "Densidade Populacional",
                cartas[0].populacao, cartas[1].populacao,
                cartas[0].densidadePopulacional, cartas[1].densidadePopulacional, 
                &pontosCarta1, &pontosCarta2);
            break;        
        default:
            printf("Opção Invalida!");
            break;
        }
        break;
    }
return 0;
}
