using Random
using Plots

#gerar pontos aleatorios
x1, y1 = rand(1:10), rand(1:10)
x2, y2 = rand(1:10), rand(1:10)

#calcular inclinacao da reta 
m = (y2 - y1) / (x2 - x1)

#calcular a interceptacao da reta
b = y1 - m * x1

#exibir equacao da reta 
println("Ponto 1: ($x1, $y1)")
println("Ponto 2: ($x2, $y2)")
println("A equacao da reta eh:")
println("y = $m x + $b")

# Gerar valores de x para desenhar a reta
x_vals = LinRange(1, 10, 100)  
y_vals = m .* x_vals .+ b      

# Plotar os pontos e a reta
scatter([x1, x2], [y1, y2], label="Pontos Aleatórios", xlabel="X", ylabel="Y", title="Reta entre Dois Pontos")
plot!(x_vals, y_vals, label="Reta", color=:blue)
