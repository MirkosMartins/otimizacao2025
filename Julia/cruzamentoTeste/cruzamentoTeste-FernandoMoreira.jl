using Plots
using Random

# Função para gerar pontos aleatórios inteiros
function gerar_pontos_aleatorios(n, lim=(-30, 30))
    pontos = []
    for _ in 1:n
        x1 = rand(lim[1]:lim[2])
        y1 = rand(lim[1]:lim[2])
        x2 = rand(lim[1]:lim[2])
        y2 = rand(lim[1]:lim[2])
        push!(pontos, ((x1, y1), (x2, y2)))
    end
    return pontos
end

# Função para calcular o ponto de interseção entre duas retas
function calcular_interseccao(p1, p2, p3, p4)
    x1, y1 = p1
    x2, y2 = p2
    x3, y3 = p3
    x4, y4 = p4

    # Calculando as inclinações e os interceptos das duas retas
    m1 = (y2 - y1) / (x2 - x1)
    b1 = y1 - m1 * x1

    m2 = (y4 - y3) / (x4 - x3)
    b2 = y3 - m2 * x3

    # Verifica se as retas são paralelas (se as inclinações forem iguais)
    if m1 == m2
        return nothing  # As retas são paralelas e não se intersectam
    end

    # Calculando a interseção das duas retas
    x_intersecao = (b2 - b1) / (m1 - m2)
    y_intersecao = m1 * x_intersecao + b1

    return (x_intersecao, y_intersecao)
end

# Gerando os pares de pontos aleatórios inteiros
n = 10  # Número de retas (pares de pontos)
pares = gerar_pontos_aleatorios(n)

# Criando o gráfico com tamanho maior e ajuste dos limites
plt = plot(size=(1000, 1000), grid=true, framestyle=:origin, 
           xlims=(-50, 50), ylims=(-50, 50), xlabel="X", ylabel="Y", title="Plano Cartesiano")

# Lista para armazenar as interseções
intersecoes = []

# Plotando as retas e as interseções
for i in 1:length(pares)
    for j in i+1:length(pares)
        p1, p2 = pares[i]
        p3, p4 = pares[j]

        # Plotar as retas
        m1 = (p2[2] - p1[2]) / (p2[1] - p1[1])
        b1 = p1[2] - m1 * p1[1]
        m2 = (p4[2] - p3[2]) / (p4[1] - p3[1])
        b2 = p3[2] - m2 * p3[1]

        x_vals = LinRange(-50, 50, 100)
        y_vals1 = m1 .* x_vals .+ b1
        y_vals2 = m2 .* x_vals .+ b2
        plot!(plt, x_vals, y_vals1, label=false, color=:red, linewidth=2)
        plot!(plt, x_vals, y_vals2, label=false, color=:red, linewidth=2)

        # Encontrar a interseção
        ponto_intersecao = calcular_interseccao(p1, p2, p3, p4)
        if ponto_intersecao !== nothing
            push!(intersecoes, ponto_intersecao)
        end
    end
end

# Plotar as interseções no gráfico
for (x_inter, y_inter) in intersecoes
    scatter!(plt, [x_inter], [y_inter], label=false, color=:green, markersize=8)
end

# Exibir o gráfico
display(plt)

# Salvar os pontos e interseções em um arquivo .txt
open("pontos_e_interseccoes.txt", "w") do f
    # Salvar os pontos gerados
    println(f, "Pontos gerados para as retas:")
    for (p1, p2) in pares
        println(f, "Pontos: ", p1, " e ", p2)
    end

    # Salvar as interseções
    println(f, "\nInterseções calculadas:")
    for ponto in intersecoes
        println(f, "Interseção: ", ponto)
    end
end

println("Pontos e interseções foram salvos no arquivo 'pontos_e_interseccoes.txt'.")
