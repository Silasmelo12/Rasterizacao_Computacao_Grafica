# Trabalho de Computação Gráfica

#### Aluno: Silas Melo

## T1: Especificação do trabalho
Nesta atividade implementamos o algoritmo para a rasterização algumas primitivas gráficas que são pontos, linhas e triângulos. Onde as arestas do triangulo são desenhada através da rasterização das linhas.
Como não temos acesso direto à memória, pois os sistemas operacionais atuais a protegem, então iremos usar um framework, disponibilizda pelo professor, que simula esse acesso, assim poderemos desenvolver nosso algoritmo.

## Introdução 

A rasterização de primitivas gráficas é uma operação que deve ser executada rapidamente e milhões de vezes para que dê a impressão de movimento, por isso, os algoritmos desenvolvidos devem ser muito eficientes.


Na rasterizção, segmentos contínuos como reta, circunferencia, poligonos, etc, são "imprimidos" na tela de forma discreta, por isso, uma parte da informação é perdida, em outras palavras, esses gráficos não terão a mesma densidade visual.

Se uma reta, por exemplo, estiver fazendo um ângulo de 0 graus ou 45 graus, as quadrículas que compoem o segmento estão sempre alinhados com o segmento que o comporta. Porém, se fizer um ãngulo de 25 graus, por exemplo, então o efeito será como uma escada. Na figura abaixo, temos um exemplo ilustrativo desses segmentos. Na figura do lado esquerdo, temos os ângulos de 0,45 e 90 graus. Na figura do lado direito, temos o ângulo de 33 graus, e podemos ver o efeito escada claramente.

<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura1.png" />

## Rasterizando um ponto

O ponto é a primitiva geometrica mais simples que existe e a rasterização dela, consiste em localizar um ponto na memória e atribuir uma cor. 
Na tela de um monitor rastez, o ponto é representado por uma matriz com linhas e colunas. Cada pixel é representado pela coordenada dessa matriz, que está associado a um endereço de memória, cada pixel tem uma configuração de cores que são as componentes RGBA. O tamanho que cada pixel ocupa na memória é de 4 bytes, portando, podemos definir uma relação matematica para localizarmos o endereço de cada um deles.

OFFSET = X*4+Y*W*4

onde X representa os valores da coluna e Y os valores da linha.

resumindo, o ponto tem duas propriedades
* coordenada
* cor

Então vamos definir duas estruturas, tCoordenadas e tColor. as coordenadas, como vimos é representada por X e Y. e a cor, pelos componentes R, G, B, A.
<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura2.png"/>

### Putpixel

A função Putpixel é uma função simples de implementar e consiste em localizar o pixel na tela e de atribuir uma cor a ele. Antes de pintar um pixel, precisamos verificar se ele está "dentro" da tela.
<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura3.png"/>

Imagem do algoritmo sendo executado

<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura4.png"/>

Esses pontos fora feitos através de um for, onde o algoritmo é executado várias vezes, ou seja, vários pontos estão pintado na tela.

### Função drawLine
<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura5.png"/>
** figura das linhas

O algoritmo de Bresenham, em constraste com outros algoritmos de rasterização da reta, não utiliza, durante sua execução, várias operações de divisão e arredondamentos dentro de loops. Desta maneira, ele minimiza o desenho de uma reta na tela. Para isso, o algoritmo assume que a inclinação da reta está entre 0 e 1 (0<m<1). Implementamos uma variação do algoritmo do Bresenham. Esse algoritmo só funciona no primeiro octante, ou seja, o coeficiente angular varia entre 0° à 45º. 
<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura6.png"/>

Por causa disso, temos que reduzir os outros octantes ao primeiro. Para esse problema, implementamos o seguinte algoritmo:

<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura7.png"/>

Explicação Matemática para o problema do octante
* Mudança 1: para solucionar o problema do segundo octante, entre 45º à 90º, iremos fazer a transformação linear de reflexão, onde os pontos cujas coordenadas são (x,y) da figura passa a ser (y,x) da nova figura;
* Mudança 2: entre 90° à 180° (segundo quadrante ou terceiro e quarto octante) a transformação é feita através da reta x=x0, onde x0 é o valor da coordenada x no ponyo inicial da reta;
* Mudança 3: entre 180° à 270° (terceiro quadrante ou quinto e sexto octante) a transformação é feita através da reta x=-y;
* Mudança 4: entre 270° à 360° (quarto quadrante ou sétimo e oitavo octante) a transformação é feita através da reta y=y0, onde y0 é o valor da coordenada y do ponto inicial da reta.

### Função drawTriangle
Função de criação dos triângulos

<img src="https://github.com/Silasmelo12/CGrasterizacao/blob/master/figura8.png"/>


### Dificuldades
A maior dificuldade encontrada foi entender como funciona a generalização do algoritmo de Bresenham para que funcionasse em todos os casos

### Referências

Algoritmo Bresenham básico: Slides do professor Christian Pagot

Algoritmo DDA: http://ecomputernotes.com/computer-graphics/simple-line-drawing-method/write-short-note-on-digital-differential-analyzer-dda

Teorema Fundamental da Álgebra Linear: http://www.uel.br/projetos/matessencial/superior/alinear/teofund.htm

Cálculo de reflexão em torno da reta x = y: http://www.ufrgs.br/espmat/disciplinas/tutoriais_softwares/shapari/shapari_rfxy.htm

Cálculo da Transformação Linear de Reflexão: http://www.feg.unesp.br/~anachiaradia/Material/Cap%2011-%20tipo%20de%20transformacao%20linear.pdf
