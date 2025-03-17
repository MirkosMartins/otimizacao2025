ponto1 = Hash.new
ponto2 = Hash.new

ponto1 = {'x' => 0, 'y' => rand(100)}
ponto2 = {'x' => rand(100), 'y' => 0}


puts("ponto 1 (#{ponto1['x']}, #{ponto1['y']})")
puts("ponto 2 (#{ponto2['x']}, #{ponto2['y']})")

def regerar_funcacao(ponto1, ponto2)
    x = ponto1['x']
    y = ponto1['y']
    a = 1

    # y = a*x + b

    b = (a * x) + y
    puts("b = #{b}")
    


    x2 = ponto2['x']
    y2 = ponto2['y']
    
    a = (y2 - b)/x2
    puts("a = #{a}")
    return
end


for i in 1..10
    ponto1 = Hash.new
    ponto2 = Hash.new

    ponto1 = {'x' => 0, 'y' => rand(100)}
    ponto2 = {'x' => rand(100), 'y' => 0}


    puts("ponto 1 (#{ponto1['x']}, #{ponto1['y']})")
    puts("ponto 2 (#{ponto2['x']}, #{ponto2['y']})")

    regerar_funcacao(ponto1, ponto2)
  end