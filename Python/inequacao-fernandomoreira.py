import random

class Ponto:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def show(self, nome=''):
        print(f"{nome}x = {self.x}, y = {self.y}")

class Reta:
    def __init__(self, p1, p2):
        if p2.x - p1.x == 0:
            self.a = None  # reta vertical (x = constante)
            self.b = p1.x
        else:
            self.a = (p2.y - p1.y) / (p2.x - p1.x)
            self.b = p1.y - self.a * p1.x

    def mostra(self):
        if self.a is None:
            return f"x = {self.b}"
        elif self.b >= 0:
            return f"y = {self.a:.2f}x + {self.b:.2f}"
        else:
            return f"y = {self.a:.2f}x - {abs(self.b):.2f}"

    def calcula_y(self, x):
        if self.a is None:
            return None  # reta vertical
        return self.a * x + self.b

class Inequacao:
    def __init__(self, reta):
        self.reta = reta

    def testar_todas(self, ponto, nome=''):
        print(f"\n🔹 Testando {nome} na reta: {self.reta.mostra()}")
        if self.reta.a is None:
            print("Reta vertical: não é possível testar inequações com y.")
            return
        y_calc = self.reta.calcula_y(ponto.x)
        print(f"1. y <  f(x)     -> {'Verdadeiro' if ponto.y < y_calc else 'Falso'}")
        print(f"2. y <= f(x)     -> {'Verdadeiro' if ponto.y <= y_calc else 'Falso'}")
        print(f"3. y >  f(x)     -> {'Verdadeiro' if ponto.y > y_calc else 'Falso'}")
        print(f"4. y >= f(x)     -> {'Verdadeiro' if ponto.y >= y_calc else 'Falso'}")
        print(f"5. y == f(x)     -> {'Verdadeiro' if ponto.y == y_calc else 'Falso'}")

# Ponto fixos para a reta
p1 = Ponto(-3, 0)
p2 = Ponto(0, -3)

# Criar a reta e inequação com os pontos fixos
reta = Reta(p1, p2)
inequacao = Inequacao(reta)

# Perguntar se o usuário quer pontos aleatórios ou manuais
usar_auto = input("Deseja gerar 4 pontos aleatórios? (s/n): ")

pontos = []

if usar_auto.lower() == 's':
    for i in range(4):
        x = random.randint(-10, 10)
        y = random.randint(-10, 10)
        pontos.append(Ponto(x, y))
        print(f"Ponto {i+1} gerado: x = {x}, y = {y}")
else:
    for i in range(4):
        x = int(input(f"Digite o valor de x{i+1}: "))
        y = int(input(f"Digite o valor de y{i+1}: "))
        pontos.append(Ponto(x, y))

# Testar os pontos contra a reta
for i, ponto in enumerate(pontos):
    inequacao.testar_todas(ponto, nome=f"Ponto {i+1} ")
