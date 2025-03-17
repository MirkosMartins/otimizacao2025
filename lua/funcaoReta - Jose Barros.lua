repeat
	n = math.random(-100, 100)
until n ~= 0
p2 = {0, n}

repeat
	n = math.random(-100, 100)
until n ~= 0
p1 = {n, 0}

b = p2[2]
a = -b/p1[1]
if b > 0 then
    print(string.format("(%d, %d)\n(%d, %d)\ny = %.1fx + %d", p1[1], p1[2], p2[1], p2[2], a, b))
else 
    print(string.format("(%d, %d)\n(%d, %d)\ny = %fx - %d", p1[1], p1[2], p2[1], p2[2], a, math.abs(b)))
end
