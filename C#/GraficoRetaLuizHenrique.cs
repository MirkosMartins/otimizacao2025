
namespace Grafico;

using System;
using System.Windows.Forms;
using ScottPlot;

class GraficoRetaLuizHenrique
{
    [STAThread]
    static void Main()
    {
        Random rand = new Random();
        int x1 = rand.Next(1, 11);
        int y1 = rand.Next(1, 11);
        int x2 = rand.Next(1, 11);
        int y2 = rand.Next(1, 11);

        if (x1 == x2)
        {
            Console.WriteLine("Os pontos têm a mesma coordenada x. Gerando novos pontos para evitar divisão por zero.");
            x2 = x1 + 1;
        }

        double m = (double)(y2 - y1) / (x2 - x1);
        double b = y1 - m * x1;

        Console.WriteLine($"Ponto 1: ({x1}, {y1})");
        Console.WriteLine($"Ponto 2: ({x2}, {y2})");
        Console.WriteLine($"A equação da reta é: y = {m}x + {b}");

        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        
        Form form = new Form() { Width = 800, Height = 600, Text = "Plano Cartesiano" };
        ScottPlot.WinForms.FormsPlot formsPlot = new() { Dock = DockStyle.Fill };
        form.Controls.Add(formsPlot);

        var plt = formsPlot.Plot;
        plt.Axes.SetLimits(-10, 10, -10, 10);
        plt.Title("Plano Cartesiano");
        plt.Axes.Bottom.Label.Text = "X";
        plt.Axes.Left.Label.Text = "Y";

        // Gerar valores de X para a reta
        double[] xVals = { -10, 10 };
        double[] yVals = { m * xVals[0] + b, m * xVals[1] + b };

        // Adicionar pontos ao gráfico
        var scatter = plt.Add.ScatterPoints(new double[] { x1, x2 }, new double[] { y1, y2 });
        scatter.Color = Colors.Blue;
        scatter.MarkerSize = 10;

        // Adicionar a reta ao gráfico
        var line = plt.Add.Line(xVals[0], yVals[0], xVals[1], yVals[1]);
        line.Color = Colors.Red;
        line.LineWidth = 2;

        formsPlot.Refresh();
        Application.Run(form);
    }
}


