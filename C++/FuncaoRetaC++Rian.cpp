#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <limits> // Necessário para limpar o buffer de entrada

int main()
{
    std::srand(std::time(0));

    double x1, y1, x2, y2;
    int escolha;

    std::cout << "Escolha uma opcao:\n";
    std::cout << "1 - Informar os pontos (x, y)\n";
    std::cout << "2 - Gerar pontos aleatoriamente entre -10 e 10\n";
    std::cout << "\n";
    std::cin >> escolha;
    std::cout << "\n";

    if (escolha == 1)
    {
        std::cout << "Informe as coordenadas do Ponto 1 (x1, y1): ";
        std::cout << "\n";
        std::cin >> x1 >> y1;
        std::cout << "\n";
        std::cout << "Informe as coordenadas do Ponto 2 (x2, y2): ";
        std::cout << "\n";
        std::cin >> x2 >> y2;
        std::cout << "\n";
    }
    else if (escolha == 2)
    {
        x1 = (std::rand() % 2101) / 100.0 - 10.0;
        y1 = (std::rand() % 2101) / 100.0 - 10.0;
        x2 = (std::rand() % 2101) / 100.0 - 10.0;
        y2 = (std::rand() % 2101) / 100.0 - 10.0;
    }
    else
    {
        std::cout << "Opcao invalida!\n";
        // Limpar o buffer de entrada para evitar problemas com std::cin em futuras interações
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }

    // Calcular a distância (mantendo como estava)
    double calculoDist = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Ponto 1: (" << x1 << ", " << y1 << ")\n";
    std::cout << "\n";
    std::cout << "Ponto 2: (" << x2 << ", " << y2 << ")\n";
    std::cout << "\n";
    std::cout << "Calculo da distancia entre os pontos: " << calculoDist << "\n";
    std::cout << "\n";

    // Calcular a equação da reta (y = ax + b)
    if (x1 == x2)
    {
        std::cout << "Os pontos formam uma reta vertical: x = " << x1 << "\n";
    }
    else
    {
        double a = (y2 - y1) / (x2 - x1);
        double b = y1 - a * x1;

        std::cout << "A equação da reta que passa pelos pontos (" << x1 << ", " << y1 << ") e (" << x2 << ", " << y2 << ") eh:\n";
        std::cout << "y = " << a << "x + " << b << "\n";

        std::cout << "\nCalculando o coeficiente angular (a):\n";
        std::cout << "a = (y2 - y1) / (x2 - x1)\n";
        std::cout << "a = (" << y2 << " - " << y1 << ") / (" << x2 << " - " << x1 << ")\n";
        std::cout << "a = " << a << "\n";
        std::cout << "\n";

        std::cout << "Calculando o coeficiente linear (b):\n";
        std::cout << "b = y1 - a * x1\n";
        std::cout << "b = " << y1 << " - (" << a << " * " << x1 << ")\n";
        std::cout << "b = " << b << "\n";
        std::cout << "\n";
    }

    return 0;
}