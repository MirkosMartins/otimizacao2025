class Ponto:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def show(self, nome=''):
        print(f"{nome}x = {self.x}, y = {self.y}")

class Reta:
    def __init__(self, p1, p2):
        if p2.x - p1.x == 0:
            self.a = None  # reta vertical
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
            return None
        return self.a * x + self.b

class Inequacao:
    def __init__(self, reta, operador):
        self.reta = reta
        self.operador = operador  # '>=' ou '<='

    def testar(self, ponto, nome=''):
        print(f"\n🔹 Testando {nome} na reta: {self.reta.mostra()} com inequação y {self.operador} f(x)")
        if self.reta.a is None:
            print("Reta vertical: não é possível testar inequações com y.")
            return

        y_calc = self.reta.calcula_y(ponto.x)
        resultado = False
        if self.operador == ">=":
            resultado = ponto.y >= y_calc
        elif self.operador == "<=":
            resultado = ponto.y <= y_calc
        else:
            print("Operador inválido.")
            return
        print(f"Ponto ({ponto.x},{ponto.y}) {'satisfaz' if resultado else 'NÃO satisfaz'} a inequação.")

# Definindo as retas e suas inequações
retas_inequacoes = [
    (Ponto(0, 2), Ponto(2, 0), ">="),   # a
    (Ponto(0, 6), Ponto(6, 0), "<="),   # b
    (Ponto(4, 0), Ponto(4, 3), "<="),   # c (reta vertical)
    (Ponto(-3, 0), Ponto(0, 2), ">="),  # d
    (Ponto(0, 3), Ponto(4, 3), "<="),   # e (reta horizontal)
    (Ponto(0, 0), Ponto(4, 1), ">="),   # f
]

# Criando inequações
inequacoes = []
for p1, p2, operador in retas_inequacoes:
    reta = Reta(p1, p2)
    inequacoes.append(Inequacao(reta, operador))

# Pontos a serem testados
pontos_teste = [
    Ponto(2, 1),
    Ponto(1, 2),
    Ponto(2, 2),
    Ponto(3, 2),
    Ponto(3, 1),
]

# Testar cada ponto em cada inequação
for i, ponto in enumerate(pontos_teste):
    print(f"\n=== Testando Ponto {i+1}: ({ponto.x}, {ponto.y}) ===")
    for j, ineq in enumerate(inequacoes):
        ineq.testar(ponto, nome=f"reta {chr(97 + j).upper()}")  # chr(97) = 'a'
