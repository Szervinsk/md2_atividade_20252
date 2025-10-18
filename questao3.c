#include <stdio.h>
#include <math.h> // Adicionado para pow

int main()
{
    int numero_alvo; // O número que será analisado

    // --- Seção de Entrada ---
    printf("--- CALCULADORA DE COEFICIENTE DE ABUNDANCIA ---\n");
    printf("Informe um numero inteiro (entre 1 e 100000): ");

    // Validação da entrada do usuário
    if (scanf("%d", &numero_alvo) != 1 || numero_alvo < 1 || numero_alvo > 100000)
    {
        printf("Erro: O valor fornecido e invalido ou esta fora do intervalo permitido.\n");
        return 1; // Encerra com código de erro
    }

    // --- Casos Especiais ---
    // O número 1 é um caso trivial
    if (numero_alvo == 1)
    {
        printf("\nResultado para N=1:\n");
        printf(" -> Quantidade de Divisores: 1\n");
        printf(" -> Soma dos Divisores: 1\n");
        printf(" -> Coeficiente: 1.00\n");
        return 0;
    }

    // --- Fatoração em Primos ---
    int fatores_primos[30]; // Armazena as bases (ex: 2, 3, 5)
    int expoentes[30];      // Armazena as potências correspondentes
    int num_fatores_distintos = 0;
    int numero_temp = numero_alvo;

    printf("\n[Passo 1] Decomposicao de %d em fatores primos:\n", numero_alvo);

    // Otimização: Trata a fatoração por 2 separadamente
    int expoente_atual = 0;
    while (numero_temp % 2 == 0)
    {
        numero_temp /= 2;
        expoente_atual++;
    }
    if (expoente_atual > 0)
    {
        fatores_primos[num_fatores_distintos] = 2;
        expoentes[num_fatores_distintos] = expoente_atual;
        num_fatores_distintos++;
        printf("   -> Fator: 2^%d\n", expoente_atual);
    }

    // Agora, busca por divisores ímpares a partir de 3
    for (int divisor_impar = 3; divisor_impar * divisor_impar <= numero_temp; divisor_impar += 2)
    {
        expoente_atual = 0;
        while (numero_temp % divisor_impar == 0)
        {
            numero_temp /= divisor_impar;
            expoente_atual++;
        }
        if (expoente_atual > 0)
        {
            fatores_primos[num_fatores_distintos] = divisor_impar;
            expoentes[num_fatores_distintos] = expoente_atual;
            num_fatores_distintos++;
            printf("   -> Fator: %d^%d\n", divisor_impar, expoente_atual);
        }
    }

    // Se 'numero_temp' ainda for maior que 1, ele é um fator primo
    if (numero_temp > 1)
    {
        fatores_primos[num_fatores_distintos] = numero_temp;
        expoentes[num_fatores_distintos] = 1;
        num_fatores_distintos++;
        printf("   -> Fator: %d^1\n", numero_temp);
    }

    // --- Cálculo da Quantidade de Divisores (tau) ---
    long long total_divisores = 1;
    for (int i = 0; i < num_fatores_distintos; i++)
    {
        total_divisores *= (expoentes[i] + 1);
    }
    printf("\n[Passo 2] Quantidade de divisores (tau): %lld\n", total_divisores);

    // --- Cálculo da Soma dos Divisores (sigma) ---
    long long soma_total_divisores = 1;
    for (int i = 0; i < num_fatores_distintos; i++)
    {
        int base_prima = fatores_primos[i];
        int potencia = expoentes[i];

        long long soma_parcial_fator = 1;
        long long potencia_atual = base_prima;

        // Calcula (p^0 + p^1 + ... + p^potencia)
        for (int j = 1; j <= potencia; j++)
        {
            soma_parcial_fator += potencia_atual;
            potencia_atual *= base_prima;
        }
        soma_total_divisores *= soma_parcial_fator;
    }
    printf("[Passo 3] Soma dos divisores (sigma): %lld\n", soma_total_divisores);

    // --- Resultado Final ---
    double coeficiente_final = (double)soma_total_divisores / total_divisores;
    printf("\n[RESULTADO FINAL] Coeficiente de Abundancia:\n");
    printf("   sigma(%d) / tau(%d) = %.2f\n", numero_alvo, numero_alvo, coeficiente_final);
    printf("--------------------------------------------------\n");

    return 0;
}