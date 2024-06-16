#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define M_PI 3.14159265358979323846

// Definição da estrutura da pilha
typedef struct No
{
    double dado;
    struct No *proximo;
} No;

typedef struct
{
    No *topo;
} Pilha;

void inicializar(Pilha *pilha)
{
    pilha->topo = NULL;
}

// Função para empilhar um valor na pilha
void empilhar(Pilha *pilha, double valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Função para desempilhar um valor da pilha
double desempilhar(Pilha *pilha)
{
    if (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

// Função principal para avaliar uma expressão em notação pós-fixada
double avaliarExpressaoPosfixada(const char *expressao)
{
    Pilha pilha;
    inicializar(&pilha);
    char *token;

    // Divide a expressão em tokens utilizando espaços como delimitadores
    token = strtok((char *)expressao, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            // Se for um dígito (ou número negativo), converte para double e empilha
            empilhar(&pilha, atof(token));
        }
        else if (strcmp(token, "log") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, log10(operando));
        }
        else if (strcmp(token, "sen") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, sin(operando * M_PI / 180.0));
        }
        else if (strcmp(token, "cos") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, cos(operando * M_PI / 180.0));
        }
        else if (strcmp(token, "tg") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, tan(operando * M_PI / 180.0));
        }
        else if (strcmp(token, "sqrt") == 0)
        {
            double operando = desempilhar(&pilha);
            empilhar(&pilha, sqrt(operando));
        }
        else if (strcmp(token, "^") == 0)
        {
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);
            empilhar(&pilha, pow(operando1, operando2));
        }
        else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                 strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
        {
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);

            switch (token[0])
            {
            case '+':
                empilhar(&pilha, operando1 + operando2);
                break;
            case '-':
                empilhar(&pilha, operando1 - operando2);
                break;
            case '*':
                empilhar(&pilha, operando1 * operando2);
                break;
            case '/':
                if (operando2 != 0.0)
                    empilhar(&pilha, operando1 / operando2);
                else
                {
                    printf("Erro: Divisão por zero\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                printf("Erro: Operador inválido\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Erro: Token inválido na expressão\n");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " "); // Avança para o próximo token
    }

    // O resultado final estará no topo da pilha
    return desempilhar(&pilha);
}

int main()
{
    char expressaotemp[100];
    const char *expressao;
    double resultado;
    int continuar = 1;

    while (continuar)
    {
        // Exemplo de expressão em notação pós-fixada: “8 45 60 + 30 cos *”
        printf("Digite a expressao:\n");
        scanf(" %[^\n]", expressaotemp);
        expressao = expressaotemp;
        resultado = avaliarExpressaoPosfixada(expressao);
        printf("Resultado: %.2f\n", resultado);

        printf("Deseja continuar calculando? (1 - Sim, 0 - Nao): ");
        scanf("%d", &continuar);
        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
    }

    return 0;
}
