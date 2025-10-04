/*
 * Complete the 'getAutoSaveInterval' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER n as parameter.
 */

 long getAutoSaveInterval(int n) {
    if (n == 0) return 1;
    if (n == 1) return 2;
    
    long a = 1, b = 2, resultado = 0;
    for (int i = 2; i <= n; i++) {
        resultado = a + b;
        a = b;
        b = resultado;
    }
    return resultado;
}

int main()