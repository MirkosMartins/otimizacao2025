/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package javaapplication2;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 *
 * @author laboratorio
 */
public class GraficoReta_Arthur extends JPanel {
    private static double a;
    private static double b;
    private static int x1;
    private static int y1;
    private static int x2;
    private static int y2;
    
    public static void main(String[] args) {
        
        x1 = 0;
        //y1 = (int)(Math.random() * 41) - 20;
        y1 = Integer.parseInt(JOptionPane.showInputDialog("Digite Y da do ponto 1"));
        do {
            //x2 = (int)(Math.random() * 41) - 20;
            x2 = Integer.parseInt(JOptionPane.showInputDialog("Digite X da do ponto 2"));
        } while (x2 == 0);
        y2 = 0;

        System.out.println("Ponto 1 (cruza y): (" + x1 + "," + y1 + ")");
        System.out.println("Ponto 2 (cruza x): (" + x2 + "," + y2 + ")");

        System.out.println("\nDescobrindo 'a' e 'b':");
        System.out.println("A equação geral é: y = ax + b");

        b = y1;
        a = (y2 - b) / x2;

        System.out.println("\nA equação da reta é: y = " + a + "x + " + b);

        
        double resultado1 = (a * x1) + b;
        double resultado2 = (a * x2) + b;
        double tolerancia = 0.0001;
        
        if (Math.abs(resultado1 - y1) < tolerancia && Math.abs(resultado2 - y2) < tolerancia) {
            System.out.println("\nA equação está correta!");
        } else {
            System.out.println("\nHouve um erro na equação.");
        }

        
        JFrame frame = new JFrame("Gráfico da Reta");
        GraficoReta_Arthur panel = new GraficoReta_Arthur();
        frame.add(panel);
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 0, getWidth(), getHeight());

        int centerX = getWidth() / 2;
        int centerY = getHeight() / 2;
        int scale = 20; 

        g2d.setColor(Color.BLACK);
        g2d.drawLine(0, centerY, getWidth(), centerY); 
        g2d.drawLine(centerX, 0, centerX, getHeight()); 

        int tickSize = 5; 
        int interval = 5;

        for (int x = -centerX / scale; x <= centerX / scale; x += interval) {
            int xPos = centerX + x * scale;
            g2d.drawLine(xPos, centerY - tickSize, xPos, centerY + tickSize); 
            if (x != 0) { 
                g2d.drawString(String.valueOf(x), xPos - 5, centerY + 20); 
            }
        }

        for (int y = -centerY / scale; y <= centerY / scale; y += interval) {
            int yPos = centerY - y * scale;
            g2d.drawLine(centerX - tickSize, yPos, centerX + tickSize, yPos); 
            if (y != 0) { 
                g2d.drawString(String.valueOf(y), centerX + 10, yPos + 5); 
            }
        }

        g2d.setColor(Color.BLUE);
        int minX = -centerX / scale;
        int maxX = centerX / scale;

        int yStart = (int)(a * minX + b) * scale;
        int yEnd = (int)(a * maxX + b) * scale;

        g2d.drawLine(0, centerY - yStart, getWidth(), centerY - yEnd);

        g2d.setColor(Color.RED);
        int pointSize = 6;
        g2d.fillOval(centerX + x1 * scale - pointSize/2, 
                     centerY - y1 * scale - pointSize/2, 
                     pointSize, pointSize);
        g2d.fillOval(centerX + x2 * scale - pointSize/2, 
                     centerY - y2 * scale - pointSize/2, 
                     pointSize, pointSize);

        g2d.setColor(Color.BLACK);
        String equation = String.format("y = %.2fx + %.2f", a, b);
        g2d.drawString(equation, 10, 20);
    }
}
