peso = 20

retas = 2

repeat
    io.write('insira o valor de Y do ponto 1: ')
	n = tostring(io.read())
until tonumber(n) ~= 0 and #n ~= 0
p2 = {0, tonumber(n) * peso}

repeat
    io.write('insira o valor de x do ponto 2: ')
    n = tostring(io.read())
until tonumber(n) ~= 0 and #n ~= 0
p1 = {tonumber(n) * peso, 0}

b = p2[2]
a = -b/p1[1]

-- Função de desenho (Love2D)
function love.load()
    love.window.setMode(1900, 1000)  -- Aumentando o tamanho da janela
    zoomFactor = 2
end

function love.draw()
    -- Definindo a largura e altura da tela
    local width, height = love.graphics.getDimensions()

    -- Desenhando os eixos
    love.graphics.setColor(1, 1, 1)  -- Cor branca
    love.graphics.line(width / 2, 0, width / 2, height)  -- Eixo Y
    love.graphics.line(0, height / 2, width, height / 2)  -- Eixo X

    -- Desenhando a função()
    love.graphics.setColor(0, 1, 0)  -- Cor verde

    print()

    for x = -width / 2, width / 2, 1 do
        local y = a * x + b
        love.graphics.points(width / 2 + x, height / 2 - y )
    end
end
