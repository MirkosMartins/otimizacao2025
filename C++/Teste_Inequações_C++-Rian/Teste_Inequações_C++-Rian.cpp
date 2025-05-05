#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <limits>

struct Ponto {
    double x, y;
};

struct Reta {
    Ponto p1, p2;
    double m, b;
};

void calcularCoeficientes(Reta &r) {
    if (fabs(r.p2.x - r.p1.x) < 1e-9) {
        r.m = std::numeric_limits<double>::infinity();
        r.b = r.p1.x;
    } else {
        r.m = (r.p2.y - r.p1.y) / (r.p2.x - r.p1.x);
        r.b = r.p1.y - r.m * r.p1.x;
    }
}

std::string obterEquacaoReta(const Reta &r, int tipoInequacao) {
    std::ostringstream equacao;
    std::string operador;
    
    switch(tipoInequacao) {
        case 0: operador = " < "; break;
        case 1: operador = " <= "; break;
        case 2: operador = " > "; break;
        case 3: operador = " >= "; break;
        default: operador = " = "; break;
    }
    
    if (std::isinf(r.m)) {
        equacao << "x" << operador << r.b;
    } else {
        equacao << "y" << operador;
        
        if (r.m != 0) {
            if (r.m == 1)
                equacao << "x";
            else if (r.m == -1)
                equacao << "-x";
            else
                equacao << r.m << "x";
        }
        
        if (r.b != 0 || r.m == 0) {
            if (r.b > 0 && r.m != 0)
                equacao << " + " << r.b;
            else if (r.b < 0)
                equacao << " - " << fabs(r.b);
            else
                equacao << r.b;
        }
    }
    
    return equacao.str();
}

bool testarPontoInequacao(const Reta &r, const Ponto &p, int tipoInequacao) {
    if (std::isinf(r.m)) {
        switch(tipoInequacao) {
            case 0: return p.x < r.b;
            case 1: return p.x <= r.b;
            case 2: return p.x > r.b;
            case 3: return p.x >= r.b;
            default: return false;
        }
    } else {
        double valorReta = r.m * p.x + r.b;
        switch(tipoInequacao) {
            case 0: return p.y < valorReta;
            case 1: return p.y <= valorReta;
            case 2: return p.y > valorReta;
            case 3: return p.y >= valorReta;
            default: return false;
        }
    }
}

int main() {
    Reta reta = {{-3, 0}, {0, -3}};
    calcularCoeficientes(reta);
    
    std::cout << "=== TESTE DE INEQUACOES ===" << std::endl;
    std::cout << "Equacao da reta: y = -x - 3" << std::endl;
    
    std::vector<Ponto> pontos;
    std::cout << "\nInforme 4 pontos para testar:" << std::endl;
    
    for (int i = 0; i < 4; i++) {
        Ponto p;
        std::cout << "Ponto " << i+1 << " (x y): ";
        std::cin >> p.x >> p.y;
        pontos.push_back(p);
    }
    
    std::cout << "\nEscolha o tipo de inequacao:" << std::endl;
    std::cout << "0: y < -x - 3" << std::endl;
    std::cout << "1: y <= -x - 3" << std::endl;
    std::cout << "2: y > -x - 3" << std::endl;
    std::cout << "3: y >= -x - 3" << std::endl;
    std::cout << "Opcao: ";
    
    int tipoInequacao;
    std::cin >> tipoInequacao;
    
    if (tipoInequacao < 0 || tipoInequacao > 3) {
        std::cout << "Opcao invalida. Usando tipo 1 (<=) como padrao." << std::endl;
        tipoInequacao = 1;
    }
    
    std::cout << "\n=== RESULTADOS DOS TESTES ===" << std::endl;
    std::cout << "Inequacao: " << obterEquacaoReta(reta, tipoInequacao) << std::endl;
    
    for (size_t i = 0; i < pontos.size(); i++) {
        bool resultado = testarPontoInequacao(reta, pontos[i], tipoInequacao);
        std::cout << "Ponto (" << pontos[i].x << ", " << pontos[i].y << "): " 
                  << (resultado ? "Verdadeiro" : "Falso") << std::endl;
    }
    
    return 0;
}