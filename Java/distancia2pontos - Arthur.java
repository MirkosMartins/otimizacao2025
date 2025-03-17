/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package javaapplication2;

import java.util.Random;

/**
 Gere 2 pontos aleatorios num grafico e fazer o calculo da distancia entre eles (d = raiz quadrada(X2 - x1)² + (y2 -y1)²)
 */
public class JavaApplication2 {

    public static void main(String[] args) {
        
        Random rand = new Random();
        
        int x1 = rand.nextInt(100);
        int y1 = rand.nextInt(100);
        int x2 = rand.nextInt(100);
        int y2 = rand.nextInt(100);
        
        
        System.out.printf("Ponto 1: ("+ x1 +", "+ y1 +")\n");
        System.out.printf("Ponto 2: ("+ x2 +", "+ y2 +")\n");
        
        double distancia = Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
        
        System.out.printf("Distancia entre os pontos: %.2f unidades\n", distancia);
    
    }
    
}
