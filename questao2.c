#include <stdio.h>

// Função para calcular o Máximo Divisor Comum (MDC)
// utilizando o Algoritmo de Euclides.
int mdc(int a, int b)
{
    printf("\n--- Calculando MDC(%d, %d) ---\n", a, b);
    int resto;
    int passo_mdc = 1; // Contador para os passos do MDC
    while (b != 0)
    {
        resto = a % b;
        // Indicador de passo para cada iteração do algoritmo
        printf("    -> [Passo %d do MDC] %d mod %d = %d\n", passo_mdc++, a, b, resto);
        a = b;
        b = resto;
    }
    printf("--- MDC encontrado: %d ---\n", a);
    return a;
}

// Função para calcular o Mínimo Múltiplo Comum (MMC)
int mmc(int a, int b)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }

    printf("--> Calculando MMC(%d, %d)\n", a, b);
    printf("    Formula: (%d * %d) / MDC(%d, %d)\n", a, b, a, b);

    // fórmula mmc = (a * b) / mdc(a, b) => (a / mdc(a,b)) * b;
    int resultado = (a / mdc(a, b)) * b;

    printf("--> MMC de (%d, %d) = %d\n", a, b, resultado);
    return resultado;
}

int main()
{
    int n;
    int ciclos[10]; // Array para armazenar os ciclos (até 10) [cite: 90]
    int i;

    // ETAPA 1: Entrada de dados
    printf("--- PASSO 1: ENTRADA DE DADOS ---\n");
    printf("Digite o numero de chaves (N): ");
    scanf("%d", &n);

    printf("Digite os %d ciclos separados por espaco: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ciclos[i]);
    }
    printf("\n============================================\n");

    // ETAPA 2: Processamento
    printf("--- PASSO 2: CALCULO ITERATIVO DO MMC ---\n");
    int resultado_mmc = ciclos[0];
    printf("Valor inicial para o MMC = %d\n", resultado_mmc);

    // Itera a partir do segundo ciclo para calcular o MMC total
    for (i = 1; i < n; i++)
    {
        printf("\n--------------------------------------------\n");
        // Indicador de sub-passo para cada iteração do MMC
        printf("PASSO 2.%d: Calculando MMC(resultado_parcial, proximo_ciclo)\n", i);
        printf("   -> MMC atual = %d | Proximo ciclo = %d\n", resultado_mmc, ciclos[i]);
        resultado_mmc = mmc(resultado_mmc, ciclos[i]);
        printf("\n   => MMC parcial atualizado para: %d\n", resultado_mmc);
    }

    printf("\n============================================\n");

    // ETAPA 3: Apresentação do resultado
    printf("--- PASSO 3: RESULTADO FINAL ---\n");
    // Verifica se o resultado está dentro do limite de 50 anos [cite: 86]
    if (resultado_mmc > 50)
    {
        printf("Conclusao: Nao foi possivel encontrar um ano para sincronizacao dentro do limite.\n");
        printf("   -> O MMC calculado (%d) excede o limite de 50 anos.\n", resultado_mmc);
    }
    else
    {
        printf("Conclusao: O primeiro ano para sincronizacao e: %d\n", resultado_mmc);
    }

    return 0;
}