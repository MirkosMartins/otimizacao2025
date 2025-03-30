peso = 1

retas = 2

p = {} y = {}

for i = 1, retas do
    p[i] = {}

    repeat
        io.write(string.format('insira o valor de Y do ponto 1 da reta %d: ',i))
        n = tostring(io.read())
    until tonumber(n) ~= 0 and #n ~= 0
    p[i][1] = {0, tonumber(n) * peso}

    repeat
        io.write(string.format('insira o valor de X do ponto 2 da reta %d: ',i))
        n = tostring(io.read())
    until tonumber(n) ~= 0 and #n ~= 0
    p[i][2] = {tonumber(n) * peso, 0}
    
end

for i = 1, retas do
    y[i] = string.format('%s x + (%s)', - p[i][2][1]/p[i][1][2], p[i][1][2])
end

for i = 1, retas do
    print(y[i])
end