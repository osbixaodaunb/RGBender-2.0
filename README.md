# RGBender

[![Build Status](https://travis-ci.org/lucasBrilhante/RGBender.svg?branch=master)](https://travis-ci.org/lucasBrilhante/RGBender)

## Team

### Programmers

* Felipe Osório

* Gustavo Lopes

* Harrison Pedro

### Artists

* Fernanda Noronha

* Mariana Martins

* Marco Xavier

### Musician

* Henrique

## Tutorial to run the game

* Type make clean

* Type make

* Type make run

## Dependencies

* SDL2

* SDL2_image, SDL2_mixer

* zlib(latest)

To install the dependencies execute the script:

```
$ sh ./install.sh
```

## Genre

It's a composition of Boss Fighting, top-down shooter

## Resume

Protagonist travels in time after spelling a symbol and will stop in the renaissance. He decides to enter into the history of the art world as a great Pichador.

## Gameplay

Keyboard: WASD + MOUSE + 1 2 3

W: Move up

A: Move  left

S: Move down

D: Move right

Space: Dash(In the direction of the movement)

Mouse : Aim

Left button of mouse: Shoot


1: Select green color

2: Select red color

3: Select blue color

R: Invoke(Mix colors)

## Powers

The character attacks using paint, which can be combined as shown in the figure below:

![Combinação de cores](http://i.imgur.com/DgjUGaQ.png)

## Scenario

Italy Renaissance + Postmodern

## Organization of game elements

Life Zelda style (corações)

Common area: training room, simple navigation map between boss and cutscenes; There is a training dummy to test skills

## Win and lose condition

After defeating the 3 bosses, the player will have won the game. During these fights if he loses all his life, the character dies, and the player returns to the beginning of the phase in which he lost the fight.

## Bosses

### 1º Boss: Xuxa Freira

Mechanical:

	Survival DPS Range

	Padronizada

	life at 100% = Ditty, sings and children running around her, serving as a shield, remains invincible. When he finishes singing, to the "cloud" of scattered child

	life at 50% = Sits there Claudia, begins to play the parish banks in the player

	life at 25% = enrage, berserk, throws childrens in to player

When dying, drop the blue ink

### 2º Boss:  Davi, Statue of Michelangelo, The most beautiful guy in town

Mechanical:

	Slow

	100%: Jump + attack = Area of damage, heals (can be stopped)

	50%: Disassemble and gain range (pluck an arm to hit you)

	25%: Enrage (Boomerang arm)

When dying drops the red paint

### 3º Boss: Your rival of the future

Battle details:

	Battle on top of a building

        Break 4th wall (turn off screen, quill screen, quill faster, etc.)

        Power equal to the player, but + refined
