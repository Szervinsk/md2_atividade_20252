#include <stdio.h>

// Função para calcular o Máximo Divisor Comum (MDC)
// utilizando o Algoritmo de Euclides.
// a = bq + r -> usando mod
int mdc(int a, int b)
{
    printf("\n--- Calculando MDC(%d, %d) ---\n", a, b);
    int resto;
    while (b != 0)
    {
        resto = a % b;
        printf("   -> Passo do Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
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

    printf("\n--> Calculando MMC(%d, %d)\n", a, b);
    printf("    Formula: (%d * %d) / MDC(%d, %d)\n", a, b, a, b);

    // fórmula mmc = (a * b) / mdc(a, b) => (a / mdc(a,b)) * b;
    int resultado = (a / mdc(a, b)) * b;

    printf("--> MMC de (%d, %d) = %d\n", a, b, resultado);
    return resultado;
}

int main()
{
    int n;        
    int ciclos[10]; // Array para armazenar os ciclos (até 10)
    int i;

    // Leitura do número de chaves
    printf("Digite o numero de chaves (N): ");
    scanf("%d", &n);

    // Lê os N cicllos
    printf("Digite os %d ciclos separados por espaco: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ciclos[i]);
    }
    printf("INICIANDO CALCULO DO MMC PARA OS CICLOS...\n");

    // cálculo mmc (primeiro)
    int resultado_mmc = ciclos[0];
    printf("MMC inicial = %d\n", resultado_mmc);

    // iteração a partir do segundo termo para pegar o (ciclo[0], ciclo[1]) e assim por diante...
    for (i = 1; i < n; i++)
    {
        printf("\n--------------------------------------------\n");
        printf("Proxima iteracao: MMC atual (%d) e proximo ciclo (%d)\n", resultado_mmc, ciclos[i]);
        resultado_mmc = mmc(resultado_mmc, ciclos[i]);
        printf("MMC parcial atualizado = %d\n", resultado_mmc);
    }

    // verifica se o limite do resultado foi atingido
    if (resultado_mmc > 50)
    {
        printf("\nRESULTADO: Nao foi possivel encontrar um ano para sincronizacao dentro do limite de 50 anos (MMC = %d).\n", resultado_mmc);
    }
    else
    {
        printf("\nRESULTADO: O primeiro ano para sincronizacao e: %d\n", resultado_mmc);
    }

    return 0;
}