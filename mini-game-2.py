from turtle import Turtle
t = Turtle()
t.speed(1)

continuar = 's'  

while continuar == 's':
    direçao = str(input('Qual direção você gostaria de andar para frente ou para trás. Digite F - para Frente / Digite T - para Trás'))
    direçao_distancia = int(input('Qual distancia você quer se movimentar'))
    rotacao = str(input('Você quer rotacionar para esquerda ou para direita? Digite D para direita - Digite E para esquerda'))
    rotacao_distancia = int(input('Qual distancia você gostaria de percorrer na rotação'))
    
    if direçao == 'f':
        t.forward(direçao_distancia)
    elif direçao == 't':
        t.backward(direçao_distancia)
    else:
        print('Resposta inválida')

    if rotacao == 'd':
        t.right(rotacao_distancia)
    elif rotacao == 'e':
        t.left(rotacao_distancia)
    else:
        print('Resposta inválida')



    continuar = str(input('Deseja continuar movimentando? Se SIM digite S. Se não digite N '))

