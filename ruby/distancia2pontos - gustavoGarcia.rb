ponto1 = Hash.new
ponto2 = Hash.new

ponto1 = {'x' => rand(100), 'y' => rand(100)}
ponto2 = {'x' => rand(100), 'y' => rand(100)}

def distancia_hash (ponto1, ponto2) 
    puts("ponto 1 #{ponto1}")
    puts("ponto 2 #{ponto2}")
    d = ((ponto2["x"] - ponto1["x"])**2 + (ponto2["y"] - ponto1["y"])**2)**(0.5)
    puts("Distância #{d.truncate(2)}")
  return
end

distancia_hash(ponto1, ponto2)