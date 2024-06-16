#include "calculadora.h"

int main()
{
    char expressaotemp[100];
    const char *expressao;
    double resultado;
    int continuar = 1;

    while (continuar)
    {
        printf("Digite a expressao em notacao pos-fixada:\n");
        scanf(" %[^\n]", expressaotemp);
        expressao = expressaotemp;

        resultado = avaliarExpressaoPosfixada(expressao);
        printf("Resultado: %.2f\n", resultado);

        char *infixa = converterParaInfixa(expressao);
        printf("Expressao em notacao infixa: %s\n", infixa);
        free(infixa);

        printf("Deseja continuar calculando? (1 - Sim, 0 - Nao): \n\n\n");
        scanf("%d", &continuar);
        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
    }

    return 0;
}
