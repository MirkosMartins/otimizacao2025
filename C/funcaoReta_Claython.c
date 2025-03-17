#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void calculaReta(int x2, int y2, int y1, int x1, int *a, int *b) {
	// calculo do b
    *b = x2 + y2;

    // calculo do a
    *a = (*b + y1) / x1;
}

int main(void) {
	int a, b;
    srand(time(0));

    int x1 = rand() % 10;
    int y1 = 0;
    int x2 = 0;
    int y2 = rand() % 10; 

    // Exibir os valores de x1 e y2
    printf("x1: %d\n", x1);
    printf("y2: %d\n", y2);

    calculaReta(x2, y2, y1, x1, &a, &b);

    // Exibir os resultados
    printf("b: %d\n", b);
    printf("a: %d\n", a);

    return 0;
}
