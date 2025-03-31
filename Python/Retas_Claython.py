import matplotlib.pyplot as plt
import numpy as np

def calcula_reta(x1, y1, x2, y2):
    a = (y2 - y1) / (x2 - x1)
    b = y1 - a * x1
    return a, b

def verifica_interseccao(a1, b1, a2, b2):
    if a1 == a2:
        return None
    xi = (b2 - b1) / (a1 - a2)
    yi = a1 * xi + b1
    return xi, yi

def ler_pontos_do_arquivo(caminho):
    pontos = []
    with open(caminho, 'r') as arquivo:
        linhas = arquivo.readlines()
        for linha in linhas:
            pontos_str = linha.strip().split(')(')
            pontos_str[0] = pontos_str[0].replace('(', '')
            pontos_str[1] = pontos_str[1].replace(')', '')
            p1 = tuple(map(int, pontos_str[0].split(',')))
            p2 = tuple(map(int, pontos_str[1].split(',')))
            pontos.append((p1[0], p1[1], p2[0], p2[1]))
    return pontos

pontos = ler_pontos_do_arquivo('C:/Users/laboratorio/Desktop/input.txt')

retas = [calcula_reta(p[0], p[1], p[2], p[3]) for p in pontos]

interseccoes = [
    verifica_interseccao(retas[i][0], retas[i][1], retas[j][0], retas[j][1])
    for i in range(len(retas)) for j in range(i + 1, len(retas))
]

x_vals = np.linspace(-10, 10, 400)
y_vals = [a * x_vals + b for a, b in retas]

for i in range(len(retas)):
    plt.plot(x_vals, y_vals[i], label=f"Reta {i+1}")

for intersecao in interseccoes:
    if intersecao:
        xi, yi = intersecao
        plt.plot(xi, yi, 'ro', label=f'Interseção: ({xi:.2f}, {yi:.2f})')

plt.axhline(0, color='black', linewidth=1)
plt.axvline(0, color='black', linewidth=1)
plt.grid(True)
plt.legend()
plt.title("Interseção de Retas")
plt.xlim(-10, 10)
plt.ylim(-10, 10)
plt.gca().set_aspect('equal', adjustable='box')
plt.show()