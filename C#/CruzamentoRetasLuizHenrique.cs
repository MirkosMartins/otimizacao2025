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

        // Gerar dois pares de pontos aleatórios para cada reta
        int x1 = rand.Next(-10, 11);
        int y1 = rand.Next(-10, 11);
        int x2 = rand.Next(-10, 11);
        int y2 = rand.Next(-10, 11);

        int x3 = rand.Next(-10, 11);
        int y3 = rand.Next(-10, 11);
        int x4 = rand.Next(-10, 11);
        int y4 = rand.Next(-10, 11);

        // Garantir que não sejam retas verticais
        if (x1 == x2) x2 += 1;
        if (x3 == x4) x4 += 1;

        // Calcular coeficientes angulares (m) e coeficientes lineares (b)
        double m1 = (double)(y2 - y1) / (x2 - x1);
        double b1 = y1 - m1 * x1;

        double m2 = (double)(y4 - y3) / (x4 - x3);
        double b2 = y3 - m2 * x3;

        // Calcular o ponto de interseção, se houver
        double? xIntersect = null, yIntersect = null;
        bool hasIntersection = false;

        if (m1 != m2) // Verifica se não são paralelas
        {
            xIntersect = (b2 - b1) / (m1 - m2);
            yIntersect = m1 * xIntersect.Value + b1;
            hasIntersection = true;
        }

        // Exibir os resultados no console
        Console.WriteLine($"Reta 1: y = {m1}x + {b1}");
        Console.WriteLine($"Reta 2: y = {m2}x + {b2}");

        if (hasIntersection)
            Console.WriteLine($"As retas se cruzam em ({xIntersect:F2}, {yIntersect:F2})");
        else
            Console.WriteLine("As retas são paralelas e não se cruzam.");

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

        // Adicionar as retas ao gráfico
        var line1 = plt.Add.Line(xVals[0], yVals1[0], xVals[1], yVals1[1]);
        line1.Color = Colors.Blue;
        line1.LineWidth = 2;

        var line2 = plt.Add.Line(xVals[0], yVals2[0], xVals[1], yVals2[1]);
        line2.Color = Colors.Red;
        line2.LineWidth = 2;

        // Adicionar ponto de interseção (se houver)
        if (hasIntersection)
        {
            var scatter = plt.Add.ScatterPoints(new double[] { xIntersect.Value }, new double[] { yIntersect.Value });
            scatter.Color = Colors.Green;
            scatter.MarkerSize = 10;
        }

        formsPlot.Refresh();
        Application.Run(form);
    }
}
