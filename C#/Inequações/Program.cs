namespace Formas
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Windows.Forms;
    using Microsoft.VisualBasic.ApplicationServices;
    using ScottPlot;

    class CruzamentoRetasInfinitoArquivoLuizHenrique
    {
        [STAThread]
        static void Main()
        {
            string filePath = ("C:\\Users\\laboratorio\\source\\repos\\Formas\\Formas\\input.txt");

            List<(int, int, int, int)> retas = new List<(int, int, int, int)>();

            try
            {
                foreach (string line in File.ReadAllLines(filePath))
                {
                    var pontos = line.Split(';');
                    var p1 = pontos[0].Replace("(", "").Replace(")", "").Split(',');
                    var p2 = pontos[1].Replace("(", "").Replace(")", "").Split(',');

                    int x1 = int.Parse(p1[0]);
                    int y1 = int.Parse(p1[1]);
                    int x2 = int.Parse(p2[0]);
                    int y2 = int.Parse(p2[1]);

                    retas.Add((x1, y1, x2, y2));
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Erro ao ler o arquivo: " + ex.Message);
                return;
            }

            List<(double, double)> intersecoes = new List<(double, double)>();
            List<string> retasParalelas = new List<string>();  // Lista para armazenar retas paralelas

            for (int i = 0; i < retas.Count; i++)
            {
                for (int j = i + 1; j < retas.Count; j++)
                {
                    var (x1, y1, x2, y2) = retas[i];
                    var (x3, y3, x4, y4) = retas[j];

                    double m1 = (double)(y2 - y1) / (x2 - x1);
                    double b1 = y2 - m1 * x2;
                    double m2 = (double)(y4 - y3) / (x4 - x3);
                    double b2 = y3 - m2 * x3;

                    if (m1 == m2)  // Se as retas sao paralelas
                    {
                        retasParalelas.Add($"Reta {i + 1} e Reta {j + 1} sao paralelas");
                    }
                    else
                    {
                        double xInt = (b2 - b1) / (m1 - m2);
                        double yInt = m1 * xInt + b1;
                        intersecoes.Add((xInt, yInt));
                    }
                }
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Form form = new Form() { Width = 800, Height = 600, Text = "Intersecao de Retas" };
            ScottPlot.WinForms.FormsPlot formsPlot = new() { Dock = DockStyle.Fill };
            form.Controls.Add(formsPlot);


            System.Windows.Forms.Label labelMensagens = new System.Windows.Forms.Label()
            {
                Dock = DockStyle.Top,
                AutoSize = true,
                Padding = new Padding(10)
            };
            form.Controls.Add(labelMensagens);


            if (retasParalelas.Count > 0)
            {
                string mensagens = "As seguintes retas sao paralelas:\n";
                foreach (var msg in retasParalelas)
                {
                    mensagens += msg + "\n";
                }
                labelMensagens.Text = mensagens;
            }
            else
            {
                labelMensagens.Text = "Nao ha retas paralelas.";
            }

            System.Windows.Forms.Label labelIntersecoes = new System.Windows.Forms.Label()
            {
                Dock = DockStyle.Bottom,
                AutoSize = true,
                Padding = new Padding(10)
            };
            form.Controls.Add(labelIntersecoes);

            if (intersecoes.Count > 0)
            {
                string textoIntersecoes = "Pontos de interseção:\n";
                foreach (var (x, y) in intersecoes)
                {
                    string quadrante = DescobrirQuadrante(x, y);
                    textoIntersecoes += $"({x:F2}, {y:F2}) — {quadrante}\n";
                }
                labelIntersecoes.Text = textoIntersecoes;
            }
            else
            {
                labelIntersecoes.Text = "Não há pontos de interseção.";
            }

            static string DescobrirQuadrante(double x, double y)
            {
                if (x > 0 && y > 0) return "Quadrante 1";
                else if (x < 0 && y > 0) return "Quadrante 2";
                else if (x < 0 && y < 0) return "Quadrante 3";
                else if (x > 0 && y < 0) return "Quadrante 4";
                else if (x == 0 && y != 0) return "Sobre o eixo Y";
                else if (y == 0 && x != 0) return "Sobre o eixo X";
                else return "Na origem (0,0)";
            }



            var plt = formsPlot.Plot;
            double maxX = 0, maxY = 0;
            plt.Add.Crosshair(0, 0).MarkerColor = ScottPlot.Colors.Black;

            foreach (var (x, y) in intersecoes)
            {
                if (x > maxX) maxX = x;
                if (y > maxY) maxY = y;
            }
            plt.Axes.SetLimits(0, maxX + 2, 0, maxY + 2);

            plt.Title("Intersecao de Retas");
            plt.Axes.Bottom.Label.Text = "X";
            plt.Axes.Left.Label.Text = "Y";

            foreach (var (x1, y1, x2, y2) in retas)
            {
                double fator = 10;

                double x1_ext = x1 - fator * (x2 - x1);
                double y1_ext = y1 - fator * (y2 - y1);
                double x2_ext = x2 + fator * (x2 - x1);
                double y2_ext = y2 + fator * (y2 - y1);

                plt.Add.Line(x1_ext, y1_ext, x2_ext, y2_ext);
            }

            foreach (var (x, y) in intersecoes)
            {
                var corPonto = ScottPlot.Colors.Black;
                plt.Add.ScatterPoints(new double[] { x }, new double[] { y }).Color = corPonto;

                if (x > 0 && y > 0)
                {
                    var linhaVertical = plt.Add.Line(x, 0, x, y);
                    linhaVertical.Color = corPonto;

                    var linhaHorizontal = plt.Add.Line(0, y, x, y);
                    linhaHorizontal.Color = corPonto;
                }
            }

            string tipoInequacao = "<=";

            if (retas.Count > 0)
            {
                var (x1, y1, x2, y2) = retas[0];
                double m = (double)(y2 - y1) / (x2 - x1);
                double b = y1 - m * x1;

                List<(double, double)> pontosTeste = new()
                    {
                        (-2, 0),
                        (-2, 2),
                        (2, -2),
                        (-2, -2)
                    };

                foreach (var (x, y) in pontosTeste)
                {
                    bool valido = tipoInequacao switch
                    {
                        "==" => y == m * x + b,
                        "<" => y < m * x + b,
                        "<=" => y <= m * x + b,
                        ">" => y > m * x + b,
                        ">=" => y >= m * x + b,
                        _ => false
                    };

                    var ponto = plt.Add.ScatterPoints(new[] { x }, new[] { y });
                    ponto.Color = valido ? ScottPlot.Colors.Indigo : ScottPlot.Colors.Red;
                    ponto.MarkerSize = 10;
                    ponto.Label = valido ? "Válido" : "Inválido";
                }
            }




            formsPlot.Refresh();
            Application.Run(form);
        }
    }
}