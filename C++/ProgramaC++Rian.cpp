#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main() {
    std::srand(std::time(0));

    int x1 = std::rand() % 21 - 10;
    int y1 = std::rand() % 21 - 10;

    int x2 = std::rand() % 21 - 10;
    int y2 = std::rand() % 21 - 10;

    double calculoDist = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

    std::cout << "Ponto 1: (" << x1 << ", " << y1 << ")\n";
    std::cout << "Ponto 2: (" << x2 << ", " << y2 << ")\n";
    std::cout << "Cálculo da distância entre os pontos: " << calculoDist << "\n";

    return 0;
}