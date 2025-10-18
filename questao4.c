#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b) {
    int resto;
    // A condição do loop do Algoritmo de Euclides é enquanto o divisor (b) não for zero.
    while (b != 0) { // [1] na linha 9 do PDF original
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        // linha 10
        a = b;
        // linha 14
        b = resto;
    }
    return a;
}

int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m; // Variáveis para o printf final

    // linha 23: Verifica se existe inverso modular. Se mdc != 1, não existe.
    if (mdcComPassos(a, m) != 1) {
       printf("Nao existe inverso modular, pois mdc(%d, %d) != 1\n", a, m);
       return -1; // Retorna -1 para indicar erro
    }


    // Algoritmo de Euclides Estendido
    while (a > 1) { // A condição original de 'while (m != 0)' estava incorreta no PDF
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
      // linha 36
      x1 = x1 + m0;
    }
    printf("\nSubstituindo, temos que o inverso de %d em mod %d e: %d.\n\n", A, B, x1);
    return x1;
}

long long powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        // linha 45: Se o expoente é ímpar, multiplica res por b
        if (exp % 2 == 1)
            res = (res * b) % mod;
        
        b = (b * b) % mod;
        // Divide o expoente por 2
        exp >>= 1;
    }
    return res;
}


int main() {
    #ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    int H, G, Zn, x, n1;
    
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
    
    printf("\n");

    // linha 72: Chama a função para calcular o inverso modular
    int inverso = inversoModular(G, Zn);
    
    if (inverso != -1) {
        int a = (long long)H * inverso % Zn; // Casting para long long para evitar overflow
        
        printf("Fazendo a multiplicacao modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);

        // Verifica qual teorema aplicar para a exponenciação
        // Como n1 (13) é primo, o expoente x (10) pode ser reduzido por mod (n1-1) = 12
        // x mod (n1-1) => 10 mod 12 = 10. Nesse caso, não há redução.
        // O código do PDF não pedia a implementação da redução, apenas o cálculo.
        
        // linha 78: Chama a função de exponenciação modular
        int resultado = powMod(a, x, n1);
        
        printf("Sendo %d o inverso de %d (mod %d)\n", inverso, G, Zn);
        printf("Valor final da congruencia: %d\n", resultado);
    }
    
    return 0;
}