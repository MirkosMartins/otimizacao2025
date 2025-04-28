def calcular_reta(x1, y1, x2, y2):
    m = (y2 - y1) / (x2 - x1)
    b = y1 - m * x1
    return m, b

def ponto_interseccao(m1, b1, m2, b2):
    if m1 == m2:
        return None
    else:
        x = (b2 - b1) / (m1 - m2)
        y = m1 * x + b1
        return (x, y)

def processar_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        linhas = arquivo.readlines()
    
    retas = []
    
    for i, linha in enumerate(linhas):
        dados = linha.strip().split(',')
        x1, y1, x2, y2 = map(float, dados)
        m, b = calcular_reta(x1, y1, x2, y2)
        retas.append((m, b, i + 1))  # Atribuir um número para a reta
    
    for i in range(len(retas)):
        m1, b1, numero1 = retas[i]
        # Exibir a equação da reta
        print(f"Equação da reta {numero1}: y = {m1:.2f}x + {b1:.2f}")
    
    for i in range(len(retas)):
        for j in range(i + 1, len(retas)):
            m1, b1, numero1 = retas[i]
            m2, b2, numero2 = retas[j]
            interseccao = ponto_interseccao(m1, b1, m2, b2)
            
            if interseccao:
                x, y = interseccao
                if x > 0 and y > 0:  # Verificar se o ponto de interseção está no primeiro quadrante
                    print(f"A reta {numero1} faz interseção com a reta {numero2} no ponto ({x:.2f}, {y:.2f}) no primeiro quadrante")
                else:
                    print(f"A reta {numero1} faz interseção com a reta {numero2} no ponto ({x:.2f}, {y:.2f}), mas não está no primeiro quadrante")
            else:
                print(f"A reta {numero1} é paralela à reta {numero2} ou elas são coincidentes.")

nome_arquivo = r'C:\Users\laboratorio\Desktop\pontos.txt'
processar_arquivo(nome_arquivo)