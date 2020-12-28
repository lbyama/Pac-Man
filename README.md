# Pac-Man
> Uma cópia do jogo Pac-man desenvolvido como projeto final da disciplina de Sistemas Operacionais(EMB5632) na UFSC - Campus Joinville em 2020.1

O jogo foi desenvolvido em C++ guiado pelos princípios de programação multithreading e orientação a objetos. Ele foi programado para um SO em nível de usuário desenvolvido durante o decorrer da disciplina (localizado na pasta [/SO](/SO)).

O comportamento dos fantasmas foi implementado como descrito [aqui](https://gameinternals.com/understanding-pac-man-ghost-behavior).
A biblioteca gráfica utilizada foi a [SFML](https://www.sfml-dev.org/).
As sprites utilizadas vieram [deste projeto](https://github.com/tkilminster/pacman).

## Como rodar

```
make
./pacman
```

## Regras

O jogo consiste no Pacman fugindo de 4 fantasmas. Se algum dos fantasmas encostar no Pacman, ele
morre (tem 3 vidas antes de acabar o jogo). Ao capturar uma das 4 “frutas” disponíveis na tela, o
Pacman cria super poderes para comer os fantasmas. Quando um fantasma é comido, ele deve
permanecer na “cadeia” por um tempo entre 1 e 7 segundos (aleatório). Ao capturar um fantasma o
Pacman ganha 200 pontos. O tabuleiro do Pacman consiste também de círculos amarelos. Toda vez que
o Pacman passar por um dos círculos ele ganha 10 pontos. De vez em quando aparece uma cereja no
centro do tabuleiro (abaixo da cadeia). Ao comer a cereja o Pacman ganha 100 pontos. O tabuleiro
também possui portáis nas laterais para permitir a passagem do pacman e fantasmas de um lado ao
outro.

## Controles
#### Movimentação
* **Teclas direcionais** para mover o Pac-Man
#### Controles Gerais
* **P** para pausar e despausar o jogo
* **Q** para sair do jogo
* **R** para reiniciar o jogo

## Contribuidores

Ligia B Yamashita - [@lbyama](https://github.com/lbyama/)  
Gustavo Henrique O de Paula - [@Ghodp](https://github.com/Ghodp/)
