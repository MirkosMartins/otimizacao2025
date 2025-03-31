/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package javaapplication2;

/**
 *
 * @author laboratorio
 */
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class CruzamentoRetas_Arthur extends JPanel {
    private static double a1, b1; 
    private static double a2, b2; 
    private static int x1, y1, x2, y2; 
    private static int x3, y3, x4, y4; 
    private static double intersectX, intersectY; 

    public static void main(String[] args) {
        x1 = 0;
        y1 = (int)(Math.random() * 41) - 20;
        y1 = -2;
        do {
            x2 = (int)(Math.random() * 41) - 20;
        } while (x2 == 0);
        y2 = 0;

        b1 = y1;
        a1 = (y2 - b1) / x2;

        System.out.println("Reta 1: y = " + a1 + "x + " + b1);
        System.out.println("Ponto 1 (cruza y): (" + x1 + "," + y1 + ")");
        System.out.println("Ponto 2 (cruza x): (" + x2 + "," + y2 + ")");

        x3 = 0;
        y3 = (int)(Math.random() * 41) - 20;
        do {
           x4 = (int)(Math.random() * 41) - 20;
        } while (x4 == 0);
        y4 = 0;

        b2 = y3;
        a2 = (y4 - b2) / x4;

        System.out.println("\nReta 2: y = " + a2 + "x + " + b2);
        System.out.println("Ponto 3 (cruza y): (" + x3 + "," + y3 + ")");
        System.out.println("Ponto 4 (cruza x): (" + x4 + "," + y4 + ")");

        findIntersection();

        JFrame frame = new JFrame("Gráfico das Retas com Interseção");
        CruzamentoRetas_Arthur panel = new CruzamentoRetas_Arthur();
        frame.add(panel);
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    private static void findIntersection() {
        if (a1 == a2) {
            if (b1 == b2) {
                System.out.println("\nAs retas são coincidentes (infinitos pontos de interseção).");
            } else {
                System.out.println("\nAs retas são paralelas (sem interseção).");
            }
            intersectX = Double.NaN;
            intersectY = Double.NaN;
        } else {
            intersectX = (b2 - b1) / (a1 - a2);
            intersectY = a1 * intersectX + b1;
            System.out.println("\nPonto de interseção: (" + String.format("%.2f", intersectX) + ", " + String.format("%.2f", intersectY) + ")");
        }
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
        int yStart1 = (int)(a1 * minX + b1) * scale;
        int yEnd1 = (int)(a1 * maxX + b1) * scale;
        g2d.drawLine(0, centerY - yStart1, getWidth(), centerY - yEnd1);

        g2d.setColor(Color.GREEN);
        int yStart2 = (int)(a2 * minX + b2) * scale;
        int yEnd2 = (int)(a2 * maxX + b2) * scale;
        g2d.drawLine(0, centerY - yStart2, getWidth(), centerY - yEnd2);

        g2d.setColor(Color.RED);
        int pointSize = 6;
        g2d.fillOval(centerX + x1 * scale - pointSize/2, centerY - y1 * scale - pointSize/2, pointSize, pointSize);
        g2d.fillOval(centerX + x2 * scale - pointSize/2, centerY - y2 * scale - pointSize/2, pointSize, pointSize);
        g2d.fillOval(centerX + x3 * scale - pointSize/2, centerY - y3 * scale - pointSize/2, pointSize, pointSize);
        g2d.fillOval(centerX + x4 * scale - pointSize/2, centerY - y4 * scale - pointSize/2, pointSize, pointSize);

        if (!Double.isNaN(intersectX) && !Double.isNaN(intersectY)) {
            g2d.setColor(Color.YELLOW);
            int intersectSize = 8;
            g2d.fillOval(centerX + (int)(intersectX * scale) - intersectSize/2, 
                         centerY - (int)(intersectY * scale) - intersectSize/2, 
                         intersectSize, intersectSize);
        }

        g2d.setColor(Color.BLACK);
        String eq1 = String.format("Reta 1: y = %.2fx + %.2f", a1, b1);
        String eq2 = String.format("Reta 2: y = %.2fx + %.2f", a2, b2);
        g2d.drawString(eq1, 10, 20);
        g2d.drawString(eq2, 10, 40);
        if (!Double.isNaN(intersectX) && !Double.isNaN(intersectY)) {
            String intersect = String.format("Interseção: (%.2f, %.2f)", intersectX, intersectY);
            g2d.drawString(intersect, 10, 60);
        }
    }
}
