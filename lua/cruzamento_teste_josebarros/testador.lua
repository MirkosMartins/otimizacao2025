-- gerar arquivo

arquivo = io.open('input.txt', "w")

io.output(arquivo)

for i = 1, math.random(2,20) do
    p1 = 0 p2 = 0
    repeat p1 = math.random(-100, 100) until p1 ~= 0
    repeat p2 = math.random(-100, 100) until p2 ~= 0
    io.write(string.format("(%i,0)(0,%i)\n",p1,p2))
end

io.close(arquivo)

-- rodar a main
os.execute('love .')