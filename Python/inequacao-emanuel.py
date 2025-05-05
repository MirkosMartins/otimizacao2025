from random import randint

class Ponto:
    def __init__(self, a, b):
        self.x = a
        self.y = b

    def show(self):
        print('x:', self.x, 'y:', self.y)

class Reta:
    def __init__(self, p1, p2):
        if p1.x == p2.x:
            self.intermedA = None
            self.intermedB = p1.x
        else:
            self.intermedA = (p2.y - p1.y) / (p2.x - p1.x)
            self.intermedB = p1.y - self.intermedA * p1.x

    def mostraReta(self):
        if self.intermedA is None:
            return f"x = {self.intermedB}"
        elif self.intermedB >= 0:
            return f"y = {self.intermedA}x + {self.intermedB}"
        else:
            return f"y = {self.intermedA}x {self.intermedB}"

class Inequacao:
    def __init__(self, p1, p2, tipo):
        self.reta = Reta(p1, p2)
        self.tipo = tipo

    def testaPonto(self, ponto):
        y_reta = self.reta.intermedA * ponto.x + self.reta.intermedB if self.reta.intermedA is not None else None
        print(y_reta)
        match self.tipo:
            case 0:  # "<"
                if ponto.y < y_reta:
                    print(f"Ponto ({ponto.x}, {ponto.y}) satisfaz a inequação {self.reta.mostraReta()} <")
                else:
                    print(f"Ponto ({ponto.x}, {ponto.y}) não satisfaz a inequação {self.reta.mostraReta()} <")
            case 1:  # "<="
                if ponto.y <= y_reta:
                    print(f"Ponto ({ponto.x}, {ponto.y}) satisfaz a inequação {self.reta.mostraReta()} <=")
                else:
                    print(f"Ponto ({ponto.x}, {ponto.y}) não satisfaz a inequação {self.reta.mostraReta()} <=")
            case 2:  # ">"
                if ponto.y > y_reta:
                    print(f"Ponto ({ponto.x}, {ponto.y}) satisfaz a inequação {self.reta.mostraReta()} >")
                else:
                    print(f"Ponto ({ponto.x}, {ponto.y}) não satisfaz a inequação {self.reta.mostraReta()} >")
            case 3:
                if ponto.y >= y_reta:
                    print(f"Ponto ({ponto.x}, {ponto.y}) satisfaz a inequação {self.reta.mostraReta()} >=")
                else:
                    print(f"Ponto ({ponto.x}, {ponto.y}) não satisfaz a inequação {self.reta.mostraReta()} >=")
            case 4:
                if ponto.y == y_reta:
                    print(f"Ponto ({ponto.x}, {ponto.y}) satisfaz a equação {self.reta.mostraReta()}")
                else:
                    print(f"Ponto ({ponto.x}, {ponto.y}) não satisfaz a equação {self.reta.mostraReta()}")
            case _:
                print("Tipo de inequação inválido")


pontoA = Ponto(0, randint(0, 10))
pontoB = Ponto(randint(0, 10), 0)
pontoC = Ponto(0, randint(0, 10))
pontoD = Ponto(0, randint(0, 10))


pontoA.show()
pontoB.show()

inequacao = Inequacao(pontoA, pontoB, 3)
inequacao.testaPonto(pontoA)
inequacao.testaPonto(pontoB)
inequacao.testaPonto(pontoC)
inequacao.testaPonto(pontoD)