#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

void calculaReta(int x1, int y1, int x2, int y2, float *a, float *b) {
    // cálculo do a
    *a = (float)(y2 - y1) / (x2 - x1);
    
    // cálculo do b
    *b = y1 - (*a * x1);
}

int main(void) {
    // inicializando o gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    float a, b;
    srand(time(0));


    int x1 = -2; 
    int y1 = 0; 
    int x2 = 0; 
    int y2 = 2; 

    int escala = 50; 

    printf("valor x1: %d\n", x1);
    printf("valor y2: %d\n\n", y2);

    calculaReta(x1, y1, x2, y2, &a, &b);

    printf("valor a : %.1f\n", a);
    printf("valor b : %.1f\n", b);


    x1 *= escala;
    y1 = -y1 * escala;  
    x2 *= escala;
    y2 = -y2 * escala; 

    line(x1 + getmaxx()/2, y1 + getmaxy()/2, x2 + getmaxx()/2, y2 + getmaxy()/2);

    getch();  
    closegraph();

    return 0;
}
