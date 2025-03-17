p1 = {math.random(1, 100), math.random(1, 100)}
p2 = {math.random(1, 100), math.random(1, 100)}
dist = ((p1[1]-p2[1])^2+(p1[2]-p2[2])^2)^(1/2)
print(string.format("√((%d-%d)² + (%d-%d)²) = %.1f",p1[1],p2[1],p1[2],p2[2],dist))
