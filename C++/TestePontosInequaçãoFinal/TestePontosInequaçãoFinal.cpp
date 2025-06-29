#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <cstdlib> // Para rand() e srand()
#include <ctime>   // Para time()

struct Ponto
{
    double x, y;
};

struct Reta
{
    Ponto p1, p2;
    double a, b, c, m;
    std::string tipo;
    int tipoInequacao; // Adicionado para armazenar o tipo de inequação
};

void calcularCoeficientes(Reta &r)
{
    r.a = r.p2.y - r.p1.y;
    r.b = r.p1.x - r.p2.x;
    r.c = r.a * r.p1.x + r.b * r.p1.y;
    if (fabs(r.p1.y - r.p2.y) < 1e-9)
    {
        r.tipo = "horizontal";
        r.m = 0;
    }
    else if (fabs(r.p1.x - r.p2.x) < 1e-9)
    {
        r.tipo = "vertical";
        r.m = std::numeric_limits<double>::infinity();
    }
    else
    {
        r.tipo = "obliqua";
        r.m = (r.p2.y - r.p1.y) / (r.p2.x - r.p1.x);
    }
}

std::string obterEquacaoReta(const Reta &r, int tipoInequacao)
{
    std::ostringstream equacao;
    std::string operador;
    switch (tipoInequacao)
    {
        case 0: operador = " < "; break;
        case 1: operador = " <= "; break;
        case 2: operador = " > "; break;
        case 3: operador = " >= "; break;
        default: operador = " = "; break;
    }

    if (std::isinf(r.m))
        equacao << "x" << operador << r.p1.x;
    else
    {
        equacao << "y" << operador;
        if (r.m != 0)
        {
            if (r.m == 1)
                equacao << "x";
            else if (r.m == -1)
                equacao << "-x";
            else
                equacao << r.m << "x";
        }
        if (r.c != 0 || r.m == 0)
        {
            if (r.c > 0 && r.m != 0)
                equacao << " + " << r.c;
            else if (r.c < 0)
                equacao << " - " << fabs(r.c);
            else
                equacao << r.c;
        }
    }
    return equacao.str();
}

bool testarPontoInequacao(const Reta &r, const Ponto &p, int tipoInequacao)
{
    double valorReta;
    if (std::isinf(r.m))
        valorReta = r.p1.x;
    else
        valorReta = r.m * p.x + r.c;

    switch (tipoInequacao)
    {
        case 0: return p.y < valorReta;
        case 1: return p.y <= valorReta;
        case 2: return p.y > valorReta;
        case 3: return p.y >= valorReta;
        default: return p.y == valorReta;
    }
}

bool saoParalelas(const Reta &r1, const Reta &r2)
{
    if (r1.tipo == "vertical" && r2.tipo == "vertical")
        return true;
    if (r1.tipo == "horizontal" && r2.tipo == "horizontal")
        return true;
    if (r1.tipo == "obliqua" && r2.tipo == "obliqua")
    {
        double det = r1.a * r2.b - r2.a * r1.b;
        return fabs(det) < 1e-9;
    }
    return false;
}

bool interseccao(const Reta &r1, const Reta &r2, Ponto &pontoInterseccao)
{
    if (r1.tipo == "vertical" && r2.tipo == "vertical")
        return false;
    if (r1.tipo == "horizontal" && r2.tipo == "horizontal")
        return false;
    if ((r1.tipo == "vertical" && r2.tipo == "horizontal") ||
        (r1.tipo == "horizontal" && r2.tipo == "vertical"))
    {
        pontoInterseccao.x = (r1.tipo == "vertical") ? r1.p1.x : r2.p1.x;
        pontoInterseccao.y = (r1.tipo == "horizontal") ? r1.p1.y : r2.p1.y;
        return true;
    }
    if (r1.tipo == "vertical" || r2.tipo == "vertical")
    {
        const Reta &vertical = (r1.tipo == "vertical") ? r1 : r2;
        const Reta &outra = (r1.tipo == "vertical") ? r2 : r1;
        pontoInterseccao.x = vertical.p1.x;
        pontoInterseccao.y = (outra.a * pontoInterseccao.x + outra.b * outra.p1.y - outra.a * outra.p1.x) / outra.b;
        return true;
    }
    if (r1.tipo == "horizontal" || r2.tipo == "horizontal")
    {
        const Reta &horizontal = (r1.tipo == "horizontal") ? r1 : r2;
        const Reta &outra = (r1.tipo == "horizontal") ? r2 : r1;
        pontoInterseccao.y = horizontal.p1.y;
        pontoInterseccao.x = (outra.b * pontoInterseccao.y - outra.b * outra.p1.y + outra.a * outra.p1.x) / outra.a;
        return true;
    }
    double det = r1.a * r2.b - r2.a * r1.b;
    if (fabs(det) < 1e-9)
        return false;
    pontoInterseccao.x = (r2.b * r1.c - r1.b * r2.c) / det;
    pontoInterseccao.y = (r1.a * r2.c - r2.a * r1.c) / det;
    return true;
}

void limparBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    srand(time(0));
    int numRetas;
    std::cout << "Informe o numero de retas: ";
    std::cin >> numRetas;
    while (numRetas < 2)
    {
        limparBuffer();
        std::cout << "Numero invalido! Deve ser pelo menos 2. Informe novamente: ";
        std::cin >> numRetas;
    }

    std::vector<Reta> retas(numRetas + 1);

    for (int i = 0; i < numRetas; i++)
    {
        std::cout << "\nReta " << i + 1 << ":\n";
        std::cout << "Informe o ponto 1 (x1, y1): ";
        std::cin >> retas[i].p1.x >> retas[i].p1.y;
        std::cout << "Informe o ponto 2 (x2, y2): ";
        std::cin >> retas[i].p2.x >> retas[i].p2.y;

        while (fabs(retas[i].p1.x - retas[i].p2.x) < 1e-9 &&
               fabs(retas[i].p1.y - retas[i].p2.y) < 1e-9)
        {
            std::cout << "Os pontos não podem ser iguais! Informe novamente:\n";
            std::cout << "Ponto 2 (x2, y2): ";
            std::cin >> retas[i].p2.x >> retas[i].p2.y;
        }

        std::cout << "Informe o tipo de inequacao para a Reta " << i + 1 << ":\n";
        std::cout << "0: <\n1: <=\n2: >\n3: >=\n";
        std::cin >> retas[i].tipoInequacao;

        while (retas[i].tipoInequacao < 0 || retas[i].tipoInequacao > 3)
        {
            std::cout << "Tipo de inequacao invalido. Informe novamente (0-3): ";
            std::cin >> retas[i].tipoInequacao;
        }

        calcularCoeficientes(retas[i]);
        std::cout << "Tipo da reta: " << retas[i].tipo << std::endl;
        std::cout << "Inequacao da Reta " << i + 1 << ": " << obterEquacaoReta(retas[i], retas[i].tipoInequacao) << std::endl;
    }
    //reta adicional
    retas[numRetas].p1.x = 0;
    retas[numRetas].p1.y = 0;
    retas[numRetas].p2.x = 1;
    retas[numRetas].p2.y = 0;
    retas[numRetas].tipoInequacao = 1; // Define a inequação do eixo x como <=
    calcularCoeficientes(retas[numRetas]);
    std::cout << "\nReta Adicional (Eixo X):\n";
    std::cout << "Ponto 1: (0, 0)\n";
    std::cout << "Ponto 2: (1, 0)\n";
    std::cout << "Tipo da reta: horizontal" << std::endl;
    std::cout << "Inequacao da Reta " << numRetas + 1 << ": " << obterEquacaoReta(retas[numRetas], retas[numRetas].tipoInequacao) << std::endl;

    std::vector<std::pair<int, int>> retasParalelas;
    for (int i = 0; i < numRetas + 1; i++)
    {
        for (int j = i + 1; j < numRetas + 1; j++)
        {
            if (saoParalelas(retas[i], retas[j]))
            {
                retasParalelas.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!retasParalelas.empty())
    {
        std::cout << "\nRetas Paralelas Encontradas:" << std::endl;
        for (const auto &par : retasParalelas)
        {
            int i = par.first;
            int j = par.second;
            std::cout << "Retas " << i + 1 << " e "
                      << j + 1 << " sao paralelas" << std::endl;
            std::cout << "  Reta " << i + 1 << ": (" << retas[i].p1.x << ", " << retas[i].p1.y << ") -> ("
                      << retas[i].p2.x << ", " << retas[i].p2.y << ")" << std::endl;
            std::cout << "  Reta " << j + 1 << ": (" << retas[j].p1.x << ", " << retas[j].p1.y << ") -> ("
                      << retas[j].p2.x << ", " << retas[j].p2.y << ")" << std::endl;
        }
    }
    else
    {
        std::cout << "\nNao foram encontradas retas paralelas." << std::endl;
    }

    std::vector<Ponto> interseccoes;
    Ponto p;

    for (int i = 0; i < numRetas + 1; i++)
    {
        for (int j = i + 1; j < numRetas + 1; j++)
        {
            if (interseccao(retas[i], retas[j], p))
            {
                bool existe = false;
                for (const auto &ponto : interseccoes)
                {
                    if (fabs(ponto.x - p.x) < 1e-9 && fabs(ponto.y - p.y) < 1e-9)
                    {
                        existe = true;
                        break;
                    }
                }
                if (!existe)
                {
                    interseccoes.push_back(p);
                }
            }
        }
    }

    std::cout << "\nForam encontradas " << interseccoes.size() << " interseccoes." << std::endl;

    for (size_t i = 0; i < interseccoes.size(); i++)
    {
        std::cout << "Interseccao " << i + 1 << ": (" << interseccoes[i].x << ", " << interseccoes[i].y << ")" << std::endl;
    }

    std::cout << "\nRetas que passam pelo ponto (0, 0):" << std::endl;
    for (int i = 0; i < numRetas; ++i)
    {
        if (testarPontoInequacao(retas[i], {0, 0}, retas[i].tipoInequacao))
        {
            std::cout << "Reta " << i + 1 << std::endl;
        }
    }

    // Gerar 5 retas aleatórias e verificar se estão na área definida pelas inequações
    std::cout << "\n=== 5 RETAS ALEATORIAS GERADAS E VERIFICADAS ===" << std::endl;
    for (int i = 0; i < 5; ++i)
    {
        Reta retaAleatoria;
        retaAleatoria.p1.x = -5 + (rand() % 11); // Gera x entre -5 e 5
        retaAleatoria.p1.y = -5 + (rand() % 11); // Gera y entre -5 e 5
        retaAleatoria.p2.x = -5 + (rand() % 11);
        retaAleatoria.p2.y = -5 + (rand() % 11);
        calcularCoeficientes(retaAleatoria);
        std::cout << "Reta Aleatoria " << i + 1 << ": (" << retaAleatoria.p1.x << ", " << retaAleatoria.p1.y << ") -> (" << retaAleatoria.p2.x << ", " << retaAleatoria.p2.y << ")" << std::endl;

        bool dentroDaArea = true;
        for (int j = 0; j < numRetas; ++j)
        {
            // Para verificar se a reta está "dentro" da área, podemos testar alguns pontos da reta
            // Se todos os pontos testados satisfizerem todas as inequações, consideramos que a reta está dentro
            Ponto pontoMedio;
            pontoMedio.x = (retaAleatoria.p1.x + retaAleatoria.p2.x) / 2.0;
            pontoMedio.y = (retaAleatoria.p1.y + retaAleatoria.p2.y) / 2.0;

            if (!testarPontoInequacao(retas[j], retaAleatoria.p1, retas[j].tipoInequacao) ||
                !testarPontoInequacao(retas[j], retaAleatoria.p2, retas[j].tipoInequacao) ||
                !testarPontoInequacao(retas[j], pontoMedio, retas[j].tipoInequacao))
            {
                dentroDaArea = false;
                break; // Se um ponto falhar em uma inequação, a reta não está na área
            }
        }
        if (dentroDaArea)
            std::cout << "  A Reta Aleatoria " << i+1 << " está dentro da área definida pelas inequações." << std::endl;
        else
             std::cout << "  A Reta Aleatoria " << i+1 << " não está dentro da área definida pelas inequações." << std::endl;
    }

    std::ofstream arquivoSaida("input.txt");
    if (!arquivoSaida.is_open())
    {
        std::cerr << "Erro ao criar arquivo input.txt" << std::endl;
        return 1;
    }

    arquivoSaida << "{\n";
    arquivoSaida << "\"retas\": [\n";
    for (int i = 0; i < numRetas + 1; i++)
    {
        arquivoSaida << "  {\"p1\": {\"x\": " << retas[i].p1.x << ", \"y\": " << retas[i].p1.y << "}, ";
        arquivoSaida << "\"p2\": {\"x\": " << retas[i].p2.x << ", \"y\": " << retas[i].p2.y << "}, ";
        arquivoSaida << "\"tipo\": \"" << retas[i].tipo << "\", ";
        arquivoSaida << "\"tipoInequacao\": " << retas[i].tipoInequacao << "}";
        if (i < numRetas)
            arquivoSaida << ",";
        arquivoSaida << "\n";
    }
    arquivoSaida << "],\n";

    arquivoSaida << "\"paralelas\": [\n";
    for (size_t i = 0; i < retasParalelas.size(); i++)
    {
        arquivoSaida << "  {\"reta1\": " << retasParalelas[i].first + 1
                      << ", \"reta2\": " << retasParalelas[i].second + 1 << "}";
        if (i < retasParalelas.size() - 1)
            arquivoSaida << ",";
        arquivoSaida << "\n";
    }
    arquivoSaida << "],\n";

    arquivoSaida << "\"interseccoes\": [\n";
    for (size_t i = 0; i < interseccoes.size(); i++)
    {
        arquivoSaida << "  {\"x\": " << interseccoes[i].x << ", \"y\": " << interseccoes[i].y << "}";
        if (i < interseccoes.size() - 1)
            arquivoSaida << ",";
        arquivoSaida << "\n";
    }
    arquivoSaida << "],\n";

    arquivoSaida << "\"retas_pelo_origem\": [";
    bool primeira = true;
    for (int i = 0; i < numRetas; ++i)
    {
        if (testarPontoInequacao(retas[i], {0, 0}, retas[i].tipoInequacao))
        {
            if (!primeira)
                arquivoSaida << ", ";
            arquivoSaida << i + 1;
            primeira = false;
        }
    }
    arquivoSaida << "],\n";
    
    arquivoSaida << "\"retas_aleatorias\": [\n";
    for (int i = 0; i < 5; ++i) {
        arquivoSaida << "  {\"p1\": {\"x\": " << -5 + (rand() % 11) << ", \"y\": " << -5 + (rand() % 11) << "}, \"p2\": {\"x\": " << -5 + (rand() % 11) << ", \"y\": " << -5 + (rand() % 11) << "}, \"dentro_da_area\": ";

        bool dentroDaArea = true;
        for (int j = 0; j < numRetas; ++j)
        {
             Ponto pontoMedio;
             pontoMedio.x = (-5 + (rand() % 11) + (-5 + (rand() % 11))) / 2.0;
             pontoMedio.y = (-5 + (rand() % 11) + (-5 + (rand() % 11))) / 2.0;
            if (!testarPontoInequacao(retas[j], {-5 + (rand() % 11), -5 + (rand() % 11)}, retas[j].tipoInequacao) ||
                !testarPontoInequacao(retas[j], {-5 + (rand() % 11), -5 + (rand() % 11)}, retas[j].tipoInequacao) ||
                 !testarPontoInequacao(retas[j], pontoMedio, retas[j].tipoInequacao))
            {
                dentroDaArea = false;
                break;
            }
        }
        arquivoSaida << (dentroDaArea ? "true" : "false") << "}";
        if (i < 4)
            arquivoSaida << ",";
        arquivoSaida << "\n";
    }
    arquivoSaida << "]\n";
    arquivoSaida << "}\n";

    arquivoSaida.close();

    std::cout << "Arquivo input.txt criado com sucesso!" << std::endl;

    std::string comandoPython = "python GerarGrafico.py";
    int resultadoExecucao = system(comandoPython.c_str());

    if (resultadoExecucao != 0)
    {
        std::cerr << "Erro ao executar o script Python GerarGrafico.py" << std::endl;
        return 1;
    }

    std::cout << "Script Python GerarGrafico.py executado com sucesso!" << std::endl;

    return 0;
}
