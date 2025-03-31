namespace Grafico;

using System;
using System.Windows.Forms;
using ScottPlot;

class CruzamentoRetasLuizHenrique
{
    [STAThread]
    static void Main()
    {
        Random rand = new Random();

        // Gerar dois pares de pontos fixos para cada reta
        int x1 = 4;
        int y1 = 0;
        int x2 = 0;
        int y2 = -2;

        int x3 = 1;
        int y3 = 0;
        int x4 = 0;
        int y4 = 1;

        int x5 = 4;
        int y5 = 0;
        int x6 = 0;
        int y6 = 2;

        // Calcular coeficientes angulares (m) e coeficientes lineares (b)
        double m1 = (double)(y2 - y1) / (x2 - x1);
        double b1 = y1 - m1 * x1;

        double m2 = (double)(y4 - y3) / (x4 - x3);
        double b2 = y3 - m2 * x3;

        double m3 = (double)(y6 - y5) / (x6 - x5);
        double b3 = y5 - m3 * x5;

        // Calcular o ponto de interseção entre as retas
        double? xIntersect1 = null, yIntersect1 = null;
        double? xIntersect2 = null, yIntersect2 = null;
        double? xIntersect3 = null, yIntersect3 = null;
        bool hasIntersection1 = false, hasIntersection2 = false, hasIntersection3 = false;

        // Verificar a interseção entre a reta 1 (m1) e a reta 2 (m2)
        if (m1 != m2) // Verifica se não são paralelas
        {
            xIntersect1 = (b2 - b1) / (m1 - m2);
            yIntersect1 = m1 * xIntersect1.Value + b1;
            hasIntersection1 = true;
        }

        // Verificar a interseção entre a reta 2 (m2) e a reta 3 (m3)
        if (m2 != m3) // Verifica se não são paralelas
        {
            xIntersect2 = (b3 - b2) / (m2 - m3);
            yIntersect2 = m2 * xIntersect2.Value + b2;
            hasIntersection2 = true;
        }

        if (m1 != m3) // Verifica se não são paralelas
        {
            xIntersect3 = (b1 - b3) / (m3 - m1);
            yIntersect3 = m3 * xIntersect3.Value + b3;
            hasIntersection3 = true;
        }

        // Exibir os resultados no console
        Console.WriteLine($"Reta 1: y = {m1}x + {b1}");
        Console.WriteLine($"Reta 2: y = {m2}x + {b2}");
        Console.WriteLine($"Reta 3: y = {m3}x + {b3}");

        if (hasIntersection1)
            Console.WriteLine($"As retas 1 e 2 se cruzam em ({xIntersect1:F2}, {yIntersect1:F2})");
        else
            Console.WriteLine("As retas 1 e 2 são paralelas e não se cruzam.");

        if (hasIntersection2)
            Console.WriteLine($"As retas 2 e 3 se cruzam em ({xIntersect2:F2}, {yIntersect2:F2})");
        else
            Console.WriteLine("As retas 2 e 3 são paralelas e não se cruzam.");
        if (hasIntersection2)
            Console.WriteLine($"As retas 1 e 3 se cruzam em ({xIntersect3:F2}, {yIntersect3:F2})");
        else
            Console.WriteLine("As retas 1 e 3 são paralelas e não se cruzam.");

        // Criar o formulário com gráfico
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);

        Form form = new Form() { Width = 800, Height = 600, Text = "Interseção de Retas" };
        ScottPlot.WinForms.FormsPlot formsPlot = new() { Dock = DockStyle.Fill };
        form.Controls.Add(formsPlot);

        var plt = formsPlot.Plot;
        plt.Axes.SetLimits(-10, 10, -10, 10);
        plt.Title("Interseção de Retas");
        plt.Axes.Bottom.Label.Text = "X";
        plt.Axes.Left.Label.Text = "Y";

        // Criar pontos para desenhar as retas
        double[] xVals = { -10, 10 };
        double[] yVals1 = { m1 * xVals[0] + b1, m1 * xVals[1] + b1 };
        double[] yVals2 = { m2 * xVals[0] + b2, m2 * xVals[1] + b2 };
        double[] yVals3 = { m3 * xVals[0] + b3, m3 * xVals[1] + b3 };

        // Adicionar as retas ao gráfico
        var line1 = plt.Add.Line(xVals[0], yVals1[0], xVals[1], yVals1[1]);
        line1.Color = ScottPlot.Colors.Blue;
        line1.LineWidth = 2;

        var line2 = plt.Add.Line(xVals[0], yVals2[0], xVals[1], yVals2[1]);
        line2.Color = ScottPlot.Colors.Red;
        line2.LineWidth = 2;

        var line3 = plt.Add.Line(xVals[0], yVals3[0], xVals[1], yVals3[1]);
        line3.Color = ScottPlot.Colors.Yellow;
        line3.LineWidth = 2;

        // Adicionar ponto de interseção (se houver)
        if (hasIntersection1)
        {
            var scatter = plt.Add.ScatterPoints(new double[] { xIntersect1.Value }, new double[] { yIntersect1.Value });
            scatter.Color = ScottPlot.Colors.Green;
            scatter.MarkerSize = 10;
        }

        if (hasIntersection2)
        {
            var scatter2 = plt.Add.ScatterPoints(new double[] { xIntersect2.Value }, new double[] { yIntersect2.Value });
            scatter2.Color = ScottPlot.Colors.Green;
            scatter2.MarkerSize = 10;
        }

        if (hasIntersection3)
        {
            var scatter3 = plt.Add.ScatterPoints(new double[] { xIntersect3.Value }, new double[] { yIntersect3.Value });
            scatter3.Color = ScottPlot.Colors.Green;
            scatter3.MarkerSize = 10;
        }

        formsPlot.Refresh();
        Application.Run(form);
    }
}
