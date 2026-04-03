from turtle import Turtle

t = Turtle()
t.speed(1)
t.forward(100)
t.right(90)
t.forward(100)
t.left(90)
t.forward(100)
t.backward(200)
input()
t.speed(1)
while True:
    distancia = int(input('Distancia a percorrer'))  
    t.forward(distancia) 