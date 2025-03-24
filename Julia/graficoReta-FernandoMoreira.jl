using Random
using Plots

# Gerar pontos aleatórios
x1, y1 = rand(1:10), rand(1:10)
x2, y2 = rand(1:10), rand(1:10)


# Calcular inclinação da reta (m)
m = (y2 - y1) / (x2 - x1)
b = y1 - m * x1

# Exibir equação da reta
println("Ponto 1: ($x1, $y1)")
println("Ponto 2: ($x2, $y2)")
println("A equação da reta é:")
println("y = $m x + $b")

# Definir limites do plano cartesiano para mostrar os 4 quadrantes
xlim = (-10, 10)
ylim = (-10, 10)

# Gerar valores de x para desenhar a reta
x_vals = LinRange(xlim[1], xlim[2], 100)
y_vals = m .* x_vals .+ b
plt = plot()

plot!(plt, size=(600,600), grid=:true, framestyle=:origin, xlims=xlim, ylims=ylim, xlabel="X", ylabel="Y", title="Plano Cartesiano", clear=true)

# Plotar os pontos e a reta
scatter!(plt, [x1, x2], [y1, y2], label="Pontos", color=:blue, markersize=5)
plot!(plt, x_vals, y_vals, label="Reta", color=:red, linewidth=2)
