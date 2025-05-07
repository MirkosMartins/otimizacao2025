import random


def inequacoes(f, p, tipo):
    condicao = {
        'maior': p['y'] < (f['a'] * p['x'] + f['b']),
        'menor': p['y'] > (f['a'] * p['x'] + f['b']),
        'igual': p['y'] == (f['a'] * p['x'] + f['b'])
    }
   
    if tipo == '<':
        return condicao['maior']
    elif tipo == '<=':
        return condicao['maior'] or condicao['igual']
    elif tipo == '>':
        return condicao['menor']
    elif tipo == '>=':
        return condicao['menor'] or condicao['igual']
    elif tipo == '=':
        return condicao['igual']
    else:
        return 'erro'


def main():

    #pontos
    retas = {'ponto1': {'x': 2, 'y': 0}, 'ponto2': {'x': 0, 'y': 4}}

    #equacao
    ang = (retas['ponto2']['y'] - retas['ponto1']['y']) / (retas['ponto2']['x'] - retas['ponto1']['x'])

    #reta
    retas['funcao'] = {'a': ang, 'b': (retas['ponto1']['y'] - ang * retas['ponto1']['x'])}

    print("**TESTE**")
    pontos = [{'x': 4, 'y': 5}]
    quant = random.randint(4, 20)
    ops = ['<', '<=', '>', '>=', '=']
    op = random.choice(ops)

    for i in range(len(pontos), quant):
        pontos.append({'x': random.randint(-100, 100), 'y': random.randint(-100, 100)})

    print(f"y {op} {retas['funcao']['a']} x + ({retas['funcao']['b']})")

    for i in range(quant):
        print(f"({pontos[i]['x']},{pontos[i]['y']}) | {inequacoes(retas['funcao'], pontos[i], op)}")

main()
