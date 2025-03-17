#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

// tipo point
typedef struct {
    int xcoord;
    int ycoord;
} point;


float distancia(point A, point B) {
    float dx = A.xcoord - B.xcoord;
    float dy = A.ycoord - B.ycoord;
    return sqrt(dx * dx + dy * dy); //distancia euclidiana
}

int main(void) {
	srand(time(0));
    int i;
    
    point A, B;
    printf("Gerando 2 valores aleatorios:\n\n");

    A.xcoord = rand() % 21; 
    A.ycoord = rand() % 21; 
    B.xcoord = rand() % 21; 
    B.ycoord = rand() % 21; 

    printf("Ponto A: (%d, %d)\n", A.xcoord, A.ycoord);
    printf("Ponto B: (%d, %d)\n", B.xcoord, B.ycoord);

    float dist = distancia(A, B);

    printf("Distancia entre A e B: %.2f\n", dist);

    return 0;
}
