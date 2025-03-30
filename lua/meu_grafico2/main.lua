peso = 20
retas = 2

p = {} -- Tabela de pontos
for i = 1, retas do
    p[i] = {}

    -- Entrada para o ponto 1 (x1, y1)
    repeat
        io.write(string.format('Insira o valor de Y do ponto 1 da reta %d: ', i))
        n = tostring(io.read())
    until tonumber(n) ~= 0 and #n ~= 0
    p[i][1] = {0, tonumber(n) * peso}  -- Ponto 1 (x1 = 0, y1 = n * peso)

    -- Entrada para o ponto 2 (x2, y2)
    repeat
        io.write(string.format('Insira o valor de X do ponto 2 da reta %d: ', i))
        n = tostring(io.read())
    until tonumber(n) ~= 0 and #n ~= 0
    p[i][2] = {tonumber(n) * peso, 0}  -- Ponto 2 (x2 = n * peso, y2 = 0)
end

-- Função de inicialização (Love2D)
function love.load()
    love.window.setMode(1900, 1000)  -- Aumentando o tamanho da janela
end

function love.draw()
    local width, height = love.graphics.getDimensions()

    -- Desenhando os eixos
    love.graphics.setColor(1, 1, 1)  -- Cor branca
    love.graphics.line(width / 2, 0, width / 2, height)  -- Eixo Y
    love.graphics.line(0, height / 2, width, height / 2)  -- Eixo X

    -- Desenhando as retas
    love.graphics.setColor(0, 1, 0)  -- Cor verde

    local a = {}  -- Inclinação das retas
    local b = {}  -- Intercepto das retas
    for i = 1, retas do
        -- Pega os pontos da reta
        x1, y1 = p[i][1][1], p[i][1][2]
        x2, y2 = p[i][2][1], p[i][2][2]

        -- Calcula a inclinação (a) e o intercepto (b) da reta
        a[i] = (y2 - y1) / (x2 - x1)
        b[i] = y1 - a[i] * x1

        -- Desenha os pontos da reta no intervalo de -width/2 a width/2
        for x = -width / 2, width / 2, 1 do
            local y = a[i] * x + b[i]
            love.graphics.points(width / 2 + x, height / 2 - y)
        end
    end

    -- Encontrando o ponto de interseção entre as duas retas
    if a[1] ~= a[2] then
        -- Calculando o ponto de interseção
        local x_intersecao = (b[2] - b[1]) / (a[1] - a[2]) / peso
        local y_intersecao = a[1] * x_intersecao + b[1] / peso
        print(string.format('(%d, %d)', x_intersecao, y_intersecao))
    end
end
