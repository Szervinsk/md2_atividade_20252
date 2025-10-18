#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>

// Define um atalho para o tipo 'long long int', usado para números grandes
typedef long long int ll;

// Calcula o Máximo Divisor Comum (MDC) usando o algoritmo de Euclides
// a, b: os dois números para o cálculo
ll mdc(ll a, ll b) {

    printf("  [MDC Calc] Calculando mdc(%lld, %lld)...\n", a, b);
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;

        printf("  [MDC Calc] -> a = %lld, b = %lld\n", a, b);
    }
    printf("  [MDC Calc] Resultado: %lld\n", a);

    return a;
}

// Função de iteração para o método Rho de Pollard: g(x) = (x^2 + 1) mod n
// x: valor atual
// n: número a ser fatorado
ll funcao_g(ll x, ll n) {
    return (x * x + 1) % n;
}

// Fatora um número 'n' usando o método Rho de Pollard
// n: número composto a ser fatorado
ll pollard_rho(ll n){

    if (n % 2 == 0) return 2;

    if (n == 1) return 1;

    ll x1 = 2;
    ll x2 = 2;
    ll d = 1;
    int iteracao = 1;

    printf("\n--- Iniciando Metodo Rho de Pollard para N = %lld ---\n", n);
    printf("Semente inicial: x0 = 2\n");
    printf("------------------------------------------------------------------\n");
    printf("Iter | x1 | x2 | |x2-x1|      | mdc(|x2-x1|, N)\n");
    printf("------------------------------------------------------------------\n");
    
    while(d == 1){
       
        //funcao de iteracao
        x1 = funcao_g(x1, n);
        
        x2 = funcao_g(funcao_g(x2, n), n);

        // Calcula a diferença absoluta e
        ll diferenca = (x1 > x2) ? (x1 - x2) : (x2 - x1);

        // O MDC da diferença e 'n' pode revelar um fator
        d = mdc(diferenca, n);

        printf("%-4d | %-14lld | %-14lld | %-12lld | %lld\n", iteracao, x1, x2, diferenca, d);
        
        iteracao++;
    }

    printf("------------------------------------------------------------------\n");
    printf("Fator encontrado: %lld\n", d);
    return d;

}

// Algoritmo Estendido de Euclides: encontra os coeficientes x, y tal que ax + my = mdc(a, m)
// a, m: números de entrada
// x, y: ponteiros para guardar os coeficientes de Bézout
ll euclides_estendido(ll a, ll m, ll *x, ll *y){

    ll x1, y1;

    // Caso base
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }

    // Chamada recursiva
    ll mdc_resultado = euclides_estendido(m % a, a, &x1, &y1);

    // Calcula os coeficientes x e y usando os resultados da recursão
    *x = y1 - (m / a) * x1;
    *y = x1;

    return mdc_resultado;
}

// Calcula o inverso modular de 'a' módulo 'm'
// a: número para o qual se busca o inverso
// m: módulo.
ll inverso_modular(ll a, ll m){

    ll x, y;

    printf("\n--- Calculando Inverso Modular de %lld mod %lld (Euclides Estendido) ---\n", a, m);

    // Usa Euclides Estendido para encontrar o mdc e os coeficientes
    ll mdc_resultado = euclides_estendido(a, m, &x, &y);

    // O inverso só existe se o mdc for 1
    if (mdc_resultado != 1) {
        printf("Inverso modular nao existe, pois mdc(%lld, %lld) != 1\n", a, m);
        return -1;
    }

    // Garante que o resultado seja positivo
    ll resultado = (x % m + m) % m;

    printf("O inverso modular (D) e: %lld\n", resultado);

    return resultado;

    
}

// Converte uma mensagem de texto para um array de números
// msg: a string de entrada
// tamanho: ponteiro para guardar o número de blocos gerados
ll *pre_codificar(char *msg, int *tamanho){

    int quant = strlen(msg);

    ll *codificada = (ll*)malloc(quant * sizeof(ll));

    int cont = 0;

    // Converte cada caractere: A=11, B=12, ..., Espaço=0
    for (int i = 0; i < quant; i++) {
        if (msg[i] >= 'A' && msg[i] <= 'Z'){
            codificada[cont++] = msg[i] - 'A' + 11;

        } else if (msg[i] == ' ') {

            codificada[cont++] = 0;
        }
    
    }

    // Informa o tamanho final do array
    *tamanho = cont;

    return codificada;
}

// Testa se um número 'n' é primo
// n: número a ser testado
int primo(ll n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (ll i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

// base, exp, mod: os parâmetros da exponenciação modular
// totiente: totiente de Euler de 'mod', usado para reduzir o expoente
ll exponenciacao_modular(ll base, ll exp, ll mod, ll totiente) {
    ll exp_reduzido = exp;

    printf("[Expo Mod] Verificando condicoes para reduzir o expoente %lld\n", exp);

    // Reduz o expoente com base nas propriedades dos teoremas de Euler/Fermat
    if (primo(mod)) {
        printf("[Expo Mod] O modulo %lld e primo. Aplicando Pequeno Teorema de Fermat\n", mod);
        ll totiente_fermat = mod - 1;
        exp_reduzido = exp % totiente_fermat;
        if (exp_reduzido == 0) exp_reduzido = totiente_fermat; // Evita expoente 0
        printf("[Expo Mod] Expoente reduzido de %lld para %lld (usando mod %lld)\n", exp, exp_reduzido, totiente_fermat);
    } else if (mdc(base, mod) == 1) {
        printf("[Expo Mod] Aplicando Teorema de Euler: mdc(%lld, %lld) = 1\n", base, mod);
        exp_reduzido = exp % totiente;
        if (exp_reduzido == 0) exp_reduzido = totiente; // Evita expoente 0
        printf("[Expo Mod] Expoente reduzido de %lld para %lld (mod %lld)\n", exp, exp_reduzido, totiente);
    } else {
        printf("[Expo Mod] mdc(%lld, %lld) != 1. Usando Extensao de Euler\n", base, mod);
        if (exp >= totiente) {
            exp_reduzido = (exp % totiente) + totiente;
            printf("[Expo Mod] Expoente reduzido de %lld para %lld (mod %lld)\n", exp, exp_reduzido, totiente);
        } else {
            printf("[Expo Mod] Nenhuma reducao aplicada pois expoente (%lld) < totiente (%lld)\n", exp, totiente);
        }
    }

    printf("[Expo Mod] Calculando %lld^%lld mod %lld\n", base, exp_reduzido, mod);
    
    // Usa exponenciação por quadratura para calcular o resultado
    ll resultado = 1;
    __int128 base_temp = base % mod;

    while (exp_reduzido > 0) {
        // Se o expoente é ímpar, multiplica o resultado pela base
        if (exp_reduzido % 2 == 1) {
            resultado = (resultado * base_temp) % mod;
        }
        // Divide o expoente por 2 e eleva a base ao quadrado
        exp_reduzido /= 2;
        base_temp = (base_temp * base_temp) % mod;
    }

    return resultado;
}

// Converte um array de números de volta para uma mensagem de texto
// codificada: o array de números
// tam: o tamanho do array
char* decodificar_para_texto(const ll *codificada, int tam) {
    char* msg = (char*)malloc((tam + 1) * sizeof(char));

    for (int i = 0; i < tam; i++) {
        ll num = codificada[i];
        if (num >= 11 && num <= 36) {
            msg[i] = (char)(num - 11 + 'A');
        } else if (num == 0) {
            msg[i] = ' ';
        } else {
            msg[i] = '?'; 
        }
    }
    msg[tam] = '\0';
    return msg;
}


int main(){


    ll n1, n2;
    printf("====== ETAPA 1: FATORACAO RHO DE POLLARD ======\n");
    printf("Informe dois numeros compostos (produto de primos distintos) entre 100 e 9999\n");
    
    printf("Digite N1: ");
    scanf("%lld", &n1);
    printf("Digite N2: ");
    scanf("%lld", &n2);

    // Fatora N1 e N2 para encontrar os primos p e q
    ll p = pollard_rho(n1);
    ll q = pollard_rho(n2);


    printf("\nFatores primos encontrados para o RSA:\n");
    printf("p (de N1=%lld) = %lld\n", n1, p);
    printf("q (de N2=%lld) = %lld\n", n2, q);



    printf("\n====== ETAPA 2: GERACAO DAS CHAVES RSA ======\n");

    // n é o módulo, parte da chave pública e privada
    ll n = p * q;
    printf("Calculando o modulo: %lld * %lld = %lld\n", p, q, n);

    // z é o totiente de Euler de n, usado para encontrar d
    ll z = (p-1) * (q-1);
    printf("Calculando o Totiente de Euler: (%lld)*(%lld) = %lld\n", p-1, q-1, z);

    printf("\nEscolhendo o expoente publico (E)\n");
    ll e = 2;

    // Encontra um 'e' tal que mdc(e, z) = 1
    while(e < n){

        printf("Tentando E = %lld\n", e);
        if(mdc(e, z) == 1){
            printf("E = %lld e valido, pois mdc(%lld, %lld) = 1.\n", e, e, z);
            break;
        }

        e++;
    }

    // d é o inverso modular de e (mod z), a chave privada
    ll d = inverso_modular(e, z);

    printf("\n--- Chaves RSA Geradas ---\n");
    printf("Chave Publica: (n, e) = (%lld, %lld)\n", n, e);
    printf("Chave Privada: (n, d) = (%lld, %lld)\n", n, d);


    printf("\n====== ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA ======\n");

    char mensagem_original[256];
    printf("Digite a mensagem para criptografar: ");

    while(getchar() != '\n'); 
    fgets(mensagem_original, sizeof(mensagem_original), stdin);


    mensagem_original[strcspn(mensagem_original, "\n")] = 0;

    // Converte a mensagem para maiúsculas para a pré-codificação
    for (ll i = 0; mensagem_original[i] != '\0'; ++i) {
        mensagem_original[i] = (char) toupper((unsigned char)mensagem_original[i]);
    }

    // Pré-codificação: converte a string em blocos de números (M)
    int num_blocos = 0;
    ll *blocos_M = pre_codificar(mensagem_original, &num_blocos);
    printf("\n--- Pre-codificacao da Mensagem ---\n");
    printf("Original: %s\n", mensagem_original);
    printf("Codificada numericamente (blocos M): ");
    for (int i = 0; i < num_blocos; i++) {
        printf("%lld ", blocos_M[i]);
    }
    printf("\n");

    // Criptografia: calcula C congruente M^e mod n para cada bloco.
    printf("\n--- Criptografando a Mensagem (C = M^e mod n) ---\n");
    ll *blocos_C = (ll*)malloc(num_blocos * sizeof(ll));

    for (int i = 0; i < num_blocos; i++) {

        printf("\nCriptografando bloco M = %lld:\n", blocos_M[i]);

        blocos_C[i] = exponenciacao_modular(blocos_M[i], e, n, z);

        printf("  Resultado: Bloco Cifrado C = %lld\n", blocos_C[i]);
    }


    printf("\nMensagem Cifrada (blocos C): ");
    for (int i = 0; i < num_blocos; i++) {
        printf("%lld ", blocos_C[i]);
    }
    printf("\n");


    // Decodificação: calcula M congruente C^d mod n para cada bloco
    printf("\n--- Descriptografando a Mensagem (M = C^d mod n) ---\n");
    ll* blocos_decodificados_M = (ll*)malloc(num_blocos * sizeof(ll));

    for (int i = 0; i < num_blocos; i++) {
        printf("\nDescriptografando bloco C = %lld:\n", blocos_C[i]);
        blocos_decodificados_M[i] = exponenciacao_modular(blocos_C[i], d, n, z);
        printf("  Resultado: Bloco Decifrado M = %lld\n", blocos_decodificados_M[i]);
    }


    // Converte os blocos numéricos de volta para texto
    char *mensagem_final = decodificar_para_texto(blocos_decodificados_M, num_blocos);
    printf("\n--- Resultado Final ---\n");
    printf("Mensagem Original:   %s\n", mensagem_original);
    printf("Mensagem Decifrada:  %s\n", mensagem_final);


    free(blocos_M);
    free(blocos_C);
    free(blocos_decodificados_M);
    free(mensagem_final);

    return 0;

}