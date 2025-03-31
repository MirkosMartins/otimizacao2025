#Executar o comando no terminal: pip install matplotlib 
import json
import matplotlib.pyplot as plt
import numpy as np

with open('dados.json', 'r') as f:
    dados = json.load(f)

print("=== RETAS ===")
for i, reta in enumerate(dados['retas']):
    print(f"Reta {i+1}:")
    print(f"  P1: ({reta['p1']['x']}, {reta['p1']['y']})")
    print(f"  P2: ({reta['p2']['x']}, {reta['p2']['y']})")
    print()

print("=== INTERSEÇÕES ===")
for i, ponto in enumerate(dados['interseccoes']):
    print(f"Interseção {i+1}: ({ponto['x']}, {ponto['y']})")

plt.figure(figsize=(10, 8))
ax = plt.gca()
plt.grid(True, linestyle='--', alpha=0.7)
plt.title('Retas Estendidas e Interseções', pad=20)
plt.xlabel('Eixo X')
plt.ylabel('Eixo Y')

all_x = []
all_y = []
for reta in dados['retas']:
    all_x.extend([reta['p1']['x'], reta['p2']['x']])
    all_y.extend([reta['p1']['y'], reta['p2']['y']])
if dados['interseccoes']:
    all_x.extend([ponto['x'] for ponto in dados['interseccoes']])
    all_y.extend([ponto['y'] for ponto in dados['interseccoes']])

margin = 0.5
x_min, x_max = min(all_x)-margin, max(all_x)+margin
y_min, y_max = min(all_y)-margin, max(all_y)+margin

plt.axhline(0, color='black', linewidth=1.2)
plt.axvline(0, color='black', linewidth=1.2)

colors = plt.cm.tab10.colors
for i, reta in enumerate(dados['retas']):
    x1, y1 = reta['p1']['x'], reta['p1']['y']
    x2, y2 = reta['p2']['x'], reta['p2']['y']

    if x1 != x2:
        a = (y2 - y1) / (x2 - x1)
        b = y1 - a * x1
        x_points = np.array([x_min, x_max])
        y_points = a * x_points + b
    else:
        x_points = np.array([x1, x1])
        y_points = np.array([y_min, y_max])

    plt.plot(x_points, y_points, color=colors[i % len(colors)],
             linewidth=2, label=f"Reta {i+1}")

if dados['interseccoes']:
    x_int = [ponto['x'] for ponto in dados['interseccoes']]
    y_int = [ponto['y'] for ponto in dados['interseccoes']]
    plt.scatter(x_int, y_int, color='black', s=150, marker='o',
                edgecolors='white', linewidths=1.5, label='Interseções', zorder=5)

plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)

plt.legend(loc='upper right', bbox_to_anchor=(1.15, 1))
plt.tight_layout()
plt.show()
