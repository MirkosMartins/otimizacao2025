# -*- coding: utf-8 -*-
"""
Created on Mon Apr  7 08:51:44 2025

@author: mirkos
"""

from itertools import combinations

retas = []

class reta:
  a = 0
  b = 0
  def __init__(self,p1,p2):
    self.ponto1 = [float(x) for x in p1.split(',')]
    self.ponto2 = [float(x) for x in p2.split(',')]

  def funcao(self):
    #print(self.ponto1,self.ponto2)
    if self.ponto2[0]==0:
      #print('ponto para encontrar B')
      self.b = self.ponto2[1]
      self.a = (-self.b)/self.ponto1[0]
    if self.b>=0:
      linha = 'f-> Y='+str(self.a)+'x+'+str(self.b)
    else:
      linha = 'f-> Y='+str(self.a)+'x'+str(self.b)
    return(linha)

def verificar_intersecao_retas(a1, b1, a2, b2):
    """
      Verifica se duas retas no formato y = ax + b se cruzam e, em caso afirmativo,
      retorna o ponto de interseção.
    
      Args:
        a1: Coeficiente angular da primeira reta.
        b1: Coeficiente linear da primeira reta.
        a2: Coeficiente angular da segunda reta.
        b2: Coeficiente linear da segunda reta.
    
      Returns:
        Uma string indicando se as retas se cruzam e, em caso afirmativo, as coordenadas
        do ponto de interseção.
      """
    if a1 != a2:
        x = (b2 - b1) / (a1 - a2)
        y = a1 * x + b1
        return f"As retas se cruzam no ponto ({x:.2f}, {y:.2f})"
    elif b1 != b2:
        return "As retas são paralelas e não se cruzam."
    else:
        return "As retas são coincidentes (são a mesma reta)."

def init():
    #print('****Init****')
    arquivo = open('input.txt')
    linhas = arquivo.readlines()
    for linha in linhas:
      p = linha.split('(')
      pontos = []
      for p1 in p:
        p1=p1.rstrip()#tira o \n
        if len(p1)>0:
          #print(p1[:len(p1)-1])
          pontos.append(p1[:len(p1)-1])
      r = reta(pontos[0],pontos[1])
      retas.append(r)#adiciona reta na lista retas
      print(r.funcao())

def teste():
    print('****TESTE****')
    combRetas = combinations(retas,2)
    for cr in combRetas:
        print(verificar_intersecao_retas(cr[0].a, cr[0].b, cr[1].a, cr[1].b))
    
if __name__ == '__main__':
    init()
    teste()
