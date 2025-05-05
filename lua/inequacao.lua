function inequacoes(f, p, tipo)
    -- Saber se um determinado ponto corresponde a determinada inequação da função
    -- @param f table função
    -- @param p table ponto
    -- @param tipo string tipo de inequação
    -- @return boolean retorna verdadeiro ou falço

    local aux = {maior = p.y < (f.a * p.x + f.b), menor = p.y > (f.a * p.x + f.b), igual = p.y == (f.a * p.x + f.b)}
    
    if (tipo == '<') then
        return aux.maior
    elseif tipo == '<=' then
        return aux.maior or aux.igual
    elseif tipo == '>' then
        return aux.menor
    elseif tipo == '>=' then
        return aux.menor or aux.igual
    elseif tipo == '=' then
        return aux.igual
    else
        return 'erro'
    end
    
end

retas = {p1 = {x = 6,y = 0},p2 = {x = 0,y =7}}
ang = (retas.p2.y - retas.p1.y)/(retas.p2.x - retas.p1.x)
retas.f = {a = ang, b = (retas.p1.y - ang * retas.p1.x)}

-- testes

pontos = {{x = 4, y = 5}}
quant = math.random(4, 20)
ops = {'<', '<=', '>', '>=', '='}
op = ops[math.random(#ops)]
for i = #pontos, quant do
    table.insert(pontos, {x = math.random(-100, 100), y = math.random(-100, 100)})
end

print(string.format('y %s %f x + (%f)', op, retas.f.a, retas.f.b))

for i = 1, quant do
    print(string.format('(%d,%d) | %s',pontos[i].x,pontos[i].y,inequacoes(retas.f, pontos[i], op)))
end
