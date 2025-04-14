--[[
[x] pegar arquivos pontos de um arquivo .txt e gerar a função deles
[x] fazer combinações
[x] ver onde elas se cruzam
--]]

-- ver onde se cuzam
function cruzam(f1, f2)
    if f1[1] == f2[1] then
        return {nil, nil}
    else
        x = (f2[2] - f1[2]) / (f2[1] - f1[1])
        y = f1[1] * x + f1[2]
        return {x, y}
    end
end

-- leitura do arquivo
arquivo = io.open('input.txt', "r")
pontos = {}
i = 1
for linha in string.gmatch(arquivo:read("a"), "[^%s]+") do
    pontos[i] = linha
    i = i+1
end
arquivo:close() 

-- separar pontos e achar função
plano = {}
funcoes = {}
for pos, linha in pairs(pontos) do
    x1, y1, x2, y2 = linha:match("%((-?%d+),(-?%d+)%)%((-?%d+),(-?%d+)%)")
    plano[pos] = {{x1, y1}, {x2, y2}}
    ang = (y2 - y1)/(x2 - x1)
    funcoes[pos] = {ang, y1 - ang * x1}
end

-- fazer combinações
combinacoes = {}
for i = 1, #funcoes -1 do
    for j = i+1, #funcoes do
        table.insert(combinacoes, {funcoes[i], funcoes[j], plano[i], plano[j], cruzam(funcoes[i], funcoes[j])})
    end
end

arquivo = io.open("resultado.txt", "w")

-- mostrar cruzamento das retas
for key, e in pairs(combinacoes) do
    if e[5][1] and e[5][2] then
        saida = string.format('y = %f x + (%d) | (%d, %d)(%d, %d) | y = %f x + (%d) | (%d, %d)(%d, %d) | P = (%f, %f)', e[1][1], e[1][2], e[3][1][1], e[3][1][2], e[3][2][1], e[3][2][2], e[2][1], e[2][2], e[4][1][1], e[4][1][2], e[4][2][1], e[4][2][2], e[5][1], e[5][2])
    else
        saida = string.format('y = %f x + (%d) | (%d, %d)(%d, %d) | y = %f x + (%d) | (%d, %d)(%d, %d) | retas paralelas', e[1][1], e[1][2], e[3][1][1], e[3][1][2], e[3][2][1], e[3][2][2], e[2][1], e[2][2], e[4][1][1], e[4][1][2], e[4][2][1], e[4][2][2])
    end
    arquivo:write(saida .. '\n')
    print(saida)
    
end

arquivo:close()

-- parte gráfica
function love.load()
    love.window.setMode(1900, 1000)  -- Aumentando o tamanho da janela
end

zoom = 10
function love.draw()
    -- Definindo a largura e altura da tela
    local width, height = love.graphics.getDimensions()

    -- Calcular o centro da tela
    local centerX = width / 2
    local centerY = height / 2

    -- Aplicar o zoom e mover a origem para o centro da tela
    love.graphics.push()  -- Salvar o estado atual da transformação
    love.graphics.translate(centerX, centerY)  -- Mover a origem para o centro
    love.graphics.scale(zoom, zoom)  -- Aplicar o zoom

    -- Desenhando os eixos
    love.graphics.setColor(1, 1, 1)  -- Cor branca
    love.graphics.line(0, -height / 2, 0, height / 2)  -- Eixo Y
    love.graphics.line(-width / 2, 0, width / 2, 0)  -- Eixo X

    -- Desenhando a função
    love.graphics.setColor(0, 1, 0)  -- Cor verde
    for key, e in pairs(funcoes) do
        for x = -width / 2, width / 2, .1 do
            local y = e[1] * x + e[2]
            love.graphics.points(x, -y)  -- Desenhar ponto na coordenada ajustada
        end
    end

    love.graphics.pop()  -- Restaurar o estado de transformação
end
