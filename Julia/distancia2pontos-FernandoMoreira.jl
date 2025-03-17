using Random

# Gerar dois pontos aleatórios no plano (x, y)
x1, y1 = rand(1:10), rand(1:10)  # Ponto 1 (x1, y1)
x2, y2 = rand(1:10), rand(1:10)  # Ponto 2 (x2, y2)

# Calcular a distância entre os pontos
distancia = sqrt((x2 - x1)^2 + (y2 - y1)^2)

# Exibir os resultados
println("Ponto 1: ($x1, $y1)")
println("Ponto 2: ($x2, $y2)")
println("Distância entre os pontos: $distancia")

