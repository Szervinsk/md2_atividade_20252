#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b)
{
    int resto;
    int passo_mdc = 1;
    printf("   Iniciando Algoritmo de Euclides para MDC(%d, %d):\n", a, b);
    while (b != 0)
    {
        resto = a % b;
        printf("   [MDC Passo %d] %d mod %d = %d\n", passo_mdc++, a, b, resto);
        a = b;
        b = resto;
    }
    printf("   MDC encontrado: %d\n", a);
    return a;
}

int inversoModular(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m; // Variáveis para o printf final
    int passo_ext = 1;

    // Etapa de verificação do MDC
    if (mdcComPassos(a, m) != 1)
    {
        printf("\n   ERRO: Nao existe inverso modular, pois mdc(%d, %d) != 1\n", a, m);
        return -1; // Retorna -1 para indicar erro
    }

    printf("   Iniciando Algoritmo de Euclides Estendido:\n");
    // Algoritmo de Euclides Estendido
    while (a > 1)
    {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
        printf("   [Inv. Passo %d] q=%d, a=%d, m=%d | x0=%d, x1=%d\n", passo_ext++, q, a, m, x0, x1);
    }

    // Ajuste final para garantir que o inverso seja positivo
    if (x1 < 0)
    {
        printf("   Ajuste final: %d (negativo) -> ", x1);
        x1 = x1 + m0;
        printf("%d (positivo)\n", x1);
    }
    printf("   Inverso Modular de %d (mod %d) e: %d.\n", A, B, x1);
    return x1;
}

long long powMod(int base, int exp, int mod)
{
    long long res = 1;
    long long b = base % mod;
    int passo_pow = 1;
    int exp_original = exp;

    printf("   Iniciando Exponenciacao Modular para %d^%d (mod %d):\n", base, exp_original, mod);
    while (exp > 0)
    {
        printf("   [Exp. Passo %d] exp=%d, b=%lld, res=%lld", passo_pow++, exp, b, res);
        // Se o expoente é ímpar, multiplica res por b
        if (exp % 2 == 1)
        {
            res = (res * b) % mod;
            printf(" -> exp e impar, res atualizado para %lld\n", res);
        }
        else
        {
            printf(" -> exp e par, res mantido\n");
        }

        b = (b * b) % mod;
        // Divide o expoente por 2
        exp >>= 1;
    }
    printf("   Resultado da exponenciacao: %lld\n", res);
    return res;
}

int main()
{
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("--- PASSO 1: Leitura dos Dados ---\n");
    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);

    printf("\n========================================\n");
    printf("--- PASSO 2: Calculo do Inverso Modular de G (mod Zn) ---\n");
    int inverso = inversoModular(G, Zn);

    if (inverso != -1)
    {
        printf("\n========================================\n");
        printf("--- PASSO 3: Calculo da Divisao Modular (H * G^-1) mod Zn ---\n");
        int a = (long long)H * inverso % Zn; // Casting para evitar overflow
        printf("   Calculo: (%d * %d) mod %d = %d\n", H, inverso, Zn, a);

        printf("\n========================================\n");
        printf("--- PASSO 4: Calculo da Exponenciacao Modular (a^x mod n1) ---\n");
        int resultado = powMod(a, x, n1);

        printf("\n========================================\n");
        printf("--- PASSO 5: Resultado Final ---\n");
        printf("   O inverso de %d (mod %d) e %d.\n", G, Zn, inverso);
        printf("   O valor final da congruencia e: %d\n", resultado);
    }

    return 0;
}