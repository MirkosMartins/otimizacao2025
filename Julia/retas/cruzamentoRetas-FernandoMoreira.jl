using Plots

# Função para ler os pontos do arquivo
function ler_pontos(arquivo)
    pares = []
    open(arquivo, "r") do f
        for linha in eachline(f)
            nums = parse.(Int, split(strip(linha)))
            if length(nums) == 4
                push!(pares, ((nums[1], nums[2]), (nums[3], nums[4])))
            end
        end
    end
    return pares
end

# Lendo os pares de pontos
pares = ler_pontos("pontos.txt")

# Criando o gráfico
plt = plot(size=(600,600), grid=true, framestyle=:origin, xlims=(-10,10), ylims=(-10,10),
           xlabel="X", ylabel="Y", title="Plano Cartesiano")

# Plotando os pontos e as retas
for (p1, p2) in pares
    x1, y1 = p1
    x2, y2 = p2

    # Plotar pontos
    scatter!(plt, [x1, x2], [y1, y2], label=false, color=:blue, markersize=5)

    # Plotar reta entre os pontos
    if x1 != x2  # Caso geral (evita divisão por zero)
        m = (y2 - y1) / (x2 - x1)
        b = y1 - m * x1
        x_vals = LinRange(-10, 10, 100)
        y_vals = m .* x_vals .+ b
        plot!(plt, x_vals, y_vals, label=false, color=:red, linewidth=2)
    else
        # Caso especial: reta vertical
        plot!(plt, [x1, x1], [-10, 10], label=false, color=:red, linewidth=2)
    end
end

display(plt)
