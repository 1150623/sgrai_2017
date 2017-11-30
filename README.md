# Labirinto 3D - OpenGL+Glut (C++)


## História por trás do jogo:

Nenhuma ainda....


## O que está no código:

+ O código está estruturado em várias classes .cpp e .h .
> XXX.h   -> constroem a classe YYY e têm os atributos e funções dessa classe declarados  
> YYY.cpp -> têm a implementação das funções inicializadas no XXX.h  

### GlobalHeader.h
  Inclui bibliotecas gerais.
  Declara varáveis globais

### Camera.h e Camera.cpp

  Como o nome indica, traduzem um "objeto" Camera, onde vai ser colocado e como. Até agora está implementado a seguir (visto de cima) o personagem.
  Já há iluminações para algumas coisas e sombras, embora ainda não esteja nada muito bem feito xd
  
  
### Character.h e Character.cpp

  Novamente, como o nome indica, são a representação do nosso personagem que vai andar pelo labirinto.
  Neste caso ainda é uma esfera apenas, nada de especial, embora que (porque me apeteceu) lhe meti sombra já, ou seja, tá fxe até
  Um personagem tem vários atributos, desde o x e y, angulo , vidas (embora não sei bem se precisa, ou como é que as perde/ganha).
  
  
### Board.h e Board.cpp

  Constroem o labirinto com base numa matriz de 0 e 1, podendo (objetos diferentes de paredes) ter numeros diferentes.
  Board.h implementa o namespace Astar que contempla o algoritmo de melhor caminho A*.
  
### main.cpp

  Basicamente é o Controller do jogo, inicia-o, corre-o e fecha-o. Tem um objeto de cada tipo (Character, Board e Camera) caso venha a haver monstros, é preciso adicionar o objeto ao main.cpp... Já escrevi uns exemplos de codigo para monstros, mas precisava de ter a classe criada para ver se faz sentido/funciona
  
