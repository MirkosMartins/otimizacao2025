#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

struct Ponto
{
    double x, y;
};

struct Reta
{
    Ponto p1, p2;
    double a, b, c;
};

void calcularCoeficientes(Reta &r)
{
    r.a = r.p2.y - r.p1.y;
    r.b = r.p1.x - r.p2.x;
    r.c = r.a * r.p1.x + r.b * r.p1.y;
}

bool saoParalelas(const Reta &r1, const Reta &r2)
{
    double det = r1.a * r2.b - r2.a * r1.b;
    return fabs(det) < 1e-9;
}

bool interseccao(const Reta &r1, const Reta &r2, Ponto &pontoInterseccao)
{
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

void gerarPontosAleatorios(Reta &reta)
{
    reta.p1.x = (rand() % 1100 - 500) / 100.0;
    reta.p1.y = (rand() % 1100 - 500) / 100.0;
    reta.p2.x = (rand() % 1100 - 500) / 100.0;
    reta.p2.y = (rand() % 1100 - 500) / 100.0;
    
    while (fabs(reta.p1.x - reta.p2.x) < 0.1 && fabs(reta.p1.y - reta.p2.y) < 0.1)
    {
        reta.p2.x = (rand() % 1100 - 500) / 100.0;
        reta.p2.y = (rand() % 1100 - 500) / 100.0;
    }
}

int main()
{
    srand(time(0));

    int opcao;
    std::cout << "Escolha a opcao de entrada:\n";
    std::cout << "1 - Informar os pontos manualmente\n";
    std::cout << "2 - Gerar pontos aleatoriamente (entre -5 e 5)\n";
    std::cin >> opcao;

    while (opcao != 1 && opcao != 2)
    {
        limparBuffer();
        std::cout << "Opcao invalida! Digite 1 ou 2:\n";
        std::cin >> opcao;
    }

    int numRetas;
    std::cout << "Informe o numero de retas: ";
    std::cin >> numRetas;

    while (numRetas < 2)
    {
        limparBuffer();
        std::cout << "Numero invalido! Deve ser pelo menos 2. Informe novamente: ";
        std::cin >> numRetas;
    }

    std::vector<Reta> retas(numRetas);

    if (opcao == 1)
    {
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
            
            calcularCoeficientes(retas[i]);
        }
    }
    else
    {
        for (int i = 0; i < numRetas; i++)
        {
            gerarPontosAleatorios(retas[i]);
            calcularCoeficientes(retas[i]);
            std::cout << "\nReta " << i + 1 << " gerada aleatoriamente:\n";
            std::cout << "Ponto 1: (" << retas[i].p1.x << ", " << retas[i].p1.y << ")\n";
            std::cout << "Ponto 2: (" << retas[i].p2.x << ", " << retas[i].p2.y << ")\n";
        }
    }

    std::vector<std::pair<int, int>> retasParalelas;
    for (int i = 0; i < numRetas; i++)
    {
        for (int j = i + 1; j < numRetas; j++)
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
            std::cout << "Retas " << i + 1 << " e " << j + 1 << " sao paralelas" << std::endl;
            std::cout << "  Reta " << i + 1 << ": (" << retas[i].p1.x << ", " << retas[i].p1.y << ") -> (" << retas[i].p2.x << ", " << retas[i].p2.y << ")" << std::endl;
            std::cout << "  Reta " << j + 1 << ": (" << retas[j].p1.x << ", " << retas[j].p1.y << ") -> (" << retas[j].p2.x << ", " << retas[j].p2.y << ")" << std::endl;
        }
    }
    else
    {
        std::cout << "\nNao foram encontradas retas paralelas." << std::endl;
    }

    std::vector<Ponto> interseccoes;
    Ponto p;

    for (int i = 0; i < numRetas; i++)
    {
        for (int j = i + 1; j < numRetas; j++)
        {
            if (interseccao(retas[i], retas[j], p))
                interseccoes.push_back(p);
        }
    }

    std::cout << "\nForam encontradas " << interseccoes.size() << " interseccoes." << std::endl;

    for (size_t i = 0; i < interseccoes.size(); i++)
    {
        std::cout << "Interseccao " << i + 1 << ": (" << interseccoes[i].x << ", " << interseccoes[i].y << ")" << std::endl;
    }

    std::ofstream arquivoSaida("input.txt");
    if (!arquivoSaida.is_open())
    {
        std::cerr << "Erro ao criar arquivo input.txt" << std::endl;
        return 1;
    }

    arquivoSaida << "{\n";
    arquivoSaida << "\"retas\": [\n";
    for (int i = 0; i < numRetas; i++)
    {
        arquivoSaida << "  {\"p1\": {\"x\": " << retas[i].p1.x << ", \"y\": " << retas[i].p1.y << "}, ";
        arquivoSaida << "\"p2\": {\"x\": " << retas[i].p2.x << ", \"y\": " << retas[i].p2.y << "}}";
        if (i < numRetas - 1)
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
    arquivoSaida << "]\n";
    arquivoSaida << "}\n";

    arquivoSaida.close();

    std::cout << "Arquivo input.txt criado com sucesso!" << std::endl;
    std::cout << "Executando o script GerarGrafico.py..." << std::endl;

#ifdef _WIN32
    system("python GerarGrafico.py");
#else
    system("python3 GerarGrafico.py");
#endif

    std::cout << "Script Python executado com sucesso!" << std::endl;

    return 0;
}
