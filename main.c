#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Defini��o da estrutura da pilha
typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

// Fun��o para empilhar um valor na pilha
void empilhar(Pilha *pilha, double valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha na aloca��o de mem�ria\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Fun��o para desempilhar um valor da pilha
double desempilhar(Pilha *pilha) {
    if (pilha->topo != NULL) {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

// Fun��o principal para avaliar uma express�o em nota��o p�s-fixada
double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha pilha;
    inicializar(&pilha);
    int i = 0;
    char token[20];
    double operando1, operando2;

    while (sscanf(expressao, "%s", token) != EOF) {
        expressao += strlen(token) + 1; // Avan�a para o pr�ximo token

        if (isdigit(token[0])) {
            // Se for um d�gito, converte para double e empilha
            empilhar(&pilha, atof(token));
        } else if (strcmp(token, "log") == 0) {
            operando1 = desempilhar(&pilha);
            empilhar(&pilha, log10(operando1));
            log10(operando1);
        } else if (strcmp(token, "sen") == 0) {
    		operando1 = desempilhar(&pilha);
    		operando1 = sin(operando1 * M_PI / 180.0);
    		// falta arredondar o valor
    		empilhar(&pilha, operando1);
		} else if (strcmp(token, "cos") == 0) {
            operando1 = desempilhar(&pilha);
            operando1 = cos(operando1 * M_PI / 180.0);
            empilhar(&pilha, operando1);
        } else if (strcmp(token, "tg") == 0) {
        	operando1 = desempilhar(&pilha);
        	operando1 = tan(operando1 * M_PI / 180.0);
        	empilhar(&pilha, operando1);
		} else if (strcmp(token, "sqrt") == 0) {
			operando1 = desempilhar(&pilha);
        	operando1 = sqrt(operando1);
        	empilhar(&pilha, operando1);
		}
		else {
            // Se for um operador, ...
            operando2 = desempilhar(&pilha);
            operando1 = desempilhar(&pilha);

            switch (token[0]) {
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
                    if (operando2 != 0.0) {
                        empilhar(&pilha, operando1 / operando2);
                    } else {
                        printf("Erro: Divis�o por zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '^':
                    empilhar(&pilha, pow(operando1, operando2));
                    break;
                default:
                    printf("Erro: Operador inv�lido\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    // O resultado final estar� no topo da pilha
    return desempilhar(&pilha);
}

int main() {
    // Exemplo de express�o em nota��o p�s-fixada: �2 4 + 5 *
    printf("Digite a expressao:\n");
    char expressaotemp[100];
    scanf(" %[^\n]", expressaotemp);
    const char *expressao = expressaotemp;
    double resultado = avaliarExpressaoPosfixada(expressao);
    printf("Resultado: %f\n", resultado);
    return 0;
}

