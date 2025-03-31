#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

struct Ponto
{
    double x, y;
};

struct Reta
{
    Ponto p1, p2;
};

bool interseccao(Reta r1, Reta r2, Ponto &pontoInterseccao)
{
    double a1 = r1.p2.y - r1.p1.y;
    double b1 = r1.p1.x - r1.p2.x;
    double c1 = a1 * r1.p1.x + b1 * r1.p1.y;

    double a2 = r2.p2.y - r2.p1.y;
    double b2 = r2.p1.x - r2.p2.x;
    double c2 = a2 * r2.p1.x + b2 * r2.p1.y;

    double det = a1 * b2 - a2 * b1;

    if (fabs(det) < 1e-9)
        return false;

    pontoInterseccao.x = (b2 * c1 - b1 * c2) / det;
    pontoInterseccao.y = (a1 * c2 - a2 * c1) / det;
    return true;
}

int main()
{
    int numRetas;
    std::cout << "Informe o numero de retas: ";
    std::cin >> numRetas;

    std::vector<Reta> retas(numRetas);

    for (int i = 0; i < numRetas; i++)
    {
        std::cout << "Informe o ponto 1 da reta " << i + 1 << " (x1, y1): ";
        std::cin >> retas[i].p1.x >> retas[i].p1.y;
        std::cout << "Informe o ponto 2 da reta " << i + 1 << " (x2, y2): ";
        std::cin >> retas[i].p2.x >> retas[i].p2.y;
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

    std::cout << "Foram encontradas " << interseccoes.size() << " interseccoes.\n";
    for (size_t i = 0; i < interseccoes.size(); i++)
    {
        std::cout << "Interseccao " << i + 1 << ": ("
                  << interseccoes[i].x << ", " << interseccoes[i].y << ")\n";
    }

    std::ofstream arquivoSaida("dados.json");
    if (!arquivoSaida.is_open())
    {
        std::cerr << "Erro ao criar arquivo dados.json" << std::endl;
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

    return 0;
}