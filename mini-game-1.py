# crie um mini game que possibilite que o usuario controle para qual direção a 
# tartaruga
# deve andar (frenta/traz) e qual ângulo deverá ser tomado para nova movimentação 

from turtle import Turtle
t = Turtle()
t.speed(1)

continuar = 's'

while continuar == 's':
    direçao = str(input('Qual direção você gostaria de andar para frente ou para trás. Digite F - para Frente / Digite T - para Trás'))
    distancia = int(input('Qual distancia você quer se movimentar'))
    
    if direçao == 'f':
        t.forward(distancia)
    elif direçao == 't':
        t.backward(distancia)
    else:
        print('Resposta inválida')
    continuar = str(input('Deseja continuar movimentando? Se SIM digite S. Se não digite N '))