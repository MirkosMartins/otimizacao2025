/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package javaaplication;

import java.util.Random;

/**
 *
 * @author laboratorio
 */
public class JavaAplication {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int x1 = 0;
        int y1 = (int)(Math.random() * 41) - 20; 
        
        int x2;
        do {
            x2 = (int)(Math.random() * 41) - 20; 
        } while (x2 == 0); 
        int y2 = 0;
        
        System.out.println("Ponto 1 (cruza y): (" + x1 + "," + y1 + ")");
        System.out.println("Ponto 2 (cruza x): (" + x2 + "," + y2 + ")");
        
        System.out.println("\nDescobrindo 'a' e 'b':");
        System.out.println("A equação geral é: y = ax + b");
        System.out.println("Usando os dois pontos para formar o sistema de equações:");
        
        System.out.println("1) Para (" + x1 + "," + y1 + "):");
        System.out.println("   " + y1 + " = a*" + x1 + " + b");
        System.out.println("   " + y1 + " = b  (equação 1)");
        
        System.out.println("2) Para (" + x2 + "," + y2 + "):");
        System.out.println("   " + y2 + " = a*" + x2 + " + b");
        System.out.println("   " + y2 + " = " + x2 + "a + b  (equação 2)");
        
        System.out.println("\nPasso 1: Descobrindo 'b'");
        System.out.println("Da equação 1: b = " + y1);
        double b = y1; 
        
        System.out.println("\nPasso 2: Descobrindo 'a'");
        System.out.println("Substituímos b = " + b + " na equação 2:");
        System.out.println("   " + y2 + " = " + x2 + "a + " + b);
        System.out.println("   " + y2 + " - " + b + " = " + x2 + "a");
        System.out.println("   " + (y2 - b) + " = " + x2 + "a");
        System.out.println("   a = " + (y2 - b) + " / " + x2);
        double a = (y2 - b) / x2; // Usa double para permitir números quebrados
        System.out.println("   a = " + a);
        
        System.out.println("\nA equação da reta é: y = " + a + "x + " + b);
        
        System.out.println("\nVerificação:");
        double resultado1 = (a * x1) + b;
        System.out.println("Ponto (" + x1 + "," + y1 + "): " + 
                          "y = " + a + "*" + x1 + " + " + b + " = " + resultado1 + 
                          " (esperado: " + y1 + ")");
        
        double resultado2 = (a * x2) + b;
        System.out.println("Ponto (" + x2 + "," + y2 + "): " + 
                          "y = " + a + "*" + x2 + " + " + b + " = " + resultado2 + 
                          " (esperado: " + y2 + ")");
        
        double tolerancia = 0.0001;
        if (Math.abs(resultado1 - y1) < tolerancia && Math.abs(resultado2 - y2) < tolerancia) {
            System.out.println("\nA equação está correta!");
        } else {
            System.out.println("\nHouve um erro na equação.");
        }
    }
}
