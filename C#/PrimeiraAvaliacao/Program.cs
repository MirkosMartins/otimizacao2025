namespace Reta
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Windows.Forms;
    using ScottPlot;

    class CruzamentoRetasInfinitoArquivoLuizHenrique
    {
        [STAThread]
        static void Main()
        {
            string filePath = ("C:\\Users\\laboratorio\\source\\repos\\Reta\\Reta\\input.txt");

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

                    if (m1 == m2)  // Se as retas s?o paralelas
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
                string textoIntersecoes = "Pontos de interse��o:\n";
                foreach (var (x, y) in intersecoes)
                {
                    textoIntersecoes += $"({x:F2}, {y:F2}) ";
                }
                labelIntersecoes.Text = textoIntersecoes;
            }
            else
            {
                labelIntersecoes.Text = "N�o h� pontos de interse��o.";
            }


            var plt = formsPlot.Plot;
            plt.Axes.SetLimits(-10, 10, -10, 10);
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
                plt.Add.ScatterPoints(new double[] { x }, new double[] { y }).Color = ScottPlot.Colors.Black;
            }

            formsPlot.Refresh();
            Application.Run(form);
        }
    }
}