/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"
#include <iostream>
#include <vector>

bool gameOver;
int x, y, p2x, p2y;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir, p2dir;
int pontuacao = 0;
AnalogIn VRx(PA_0);
AnalogIn VRy(PA_1);
AnalogIn Player2VRx(PC_1);
AnalogIn Player2VRy(PC_0);
DigitalOut V5(PF_1);


char mapa[9][30] = {
    "#############################", "#*                         *#",
    "# ############ ############ #", "# ############ ############ #",
    "#                           #", "# ############ ############ #",
    "# ############ ############ #", "#*                         *#",
    "#############################"};

void Iniciar() {
  gameOver = false;
  x = 15;
  y = 4;
  p2x = 15;
  p2y = 1;
}

void RenderizarMapa() {
  printf("\033[2J\033[H");
  printf("Pontuação: %d\n\n", pontuacao);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 30; j++) {
      if (i == y && j == x) {
        cout << "\033[1;33m" << '>' << "\033[0m";
        continue;
      }

      if(i == p2y && j == p2x) {
          cout << "\033[1;32m" << '>' << "\033[0m";
          continue;
      }

      if (mapa[i][j] == '#') {
        // Código ANSI para definir a cor do texto para azul e o fundo para azul
        cout << "\033[1;34;44m" << mapa[i][j] << "\033[0m";
        //   } else if (mapa[i][j] == 'mapa[y][x]') {
        // Código ANSI para definir a cor do texto para amarelo

      } else if (mapa[i][j] == '*') {
        // Código ANSI para definir a cor do texto para vermelho
        cout << "\033[1;31m" << mapa[i][j] << "\033[0m";
      } else {
        cout << mapa[i][j];
      }
    }
    cout << endl;
  }
}

void Input() {
  if (VRx.read() <= 0.33) {
    dir = LEFT;
  } else if (VRx.read() >= 0.66) {
    dir = RIGHT;
  } else if (VRy.read() <= 0.33) {
    dir = UP;
  } else if (VRy.read() >= 0.66) {
    dir = DOWN;
  }
}

 void Input2() {
   if (Player2VRx.read() <= 0.33) {
     p2dir = LEFT;
   } else if (Player2VRx.read() >= 0.66) {
     p2dir = RIGHT;
   } else if (Player2VRy.read() <= 0.33) {
     p2dir = UP;
   } else if (Player2VRy.read() >= 0.66) {
     p2dir = DOWN;
   }
}

void Logic2() {
  if (p2dir == UP && mapa[p2y - 1][p2x] == '#')
    return;

  if (p2dir == DOWN && mapa[p2y + 1][p2x] == '#')
    return;

  if (p2dir == RIGHT && mapa[p2y][p2x + 1] == '#')
    return;

  if (p2dir == LEFT && mapa[p2y][p2x - 1] == '#')
    return;

  
  
  switch (p2dir) {
  case UP:
    p2y--;
    break;
  case RIGHT:
    p2x++;
    break;
  case LEFT:
    p2x--;
    break;
  case DOWN:
    p2y++;
    break;
  default:
    break;
  }

    if (p2y == y && p2x == x) {
    gameOver = true;
  }

  // if (x > largura || x < 0 || y > altura || y < 0)
  //     gameOver = true;

  //   if (x == pontoX && y == pontoY) {
  //     pontoX = 2;
  //     pontoY = rand() % altura;
}

void Logic() {
  if (dir == UP && mapa[y - 1][x] == '#')
    return;

  if (dir == DOWN && mapa[y + 1][x] == '#')
    return;

  if (dir == RIGHT && mapa[y][x + 1] == '#')
    return;

  if (dir == LEFT && mapa[y][x - 1] == '#')
    return;

  
  
  switch (dir) {
  case UP:
    y--;
    break;
  case RIGHT:
    x++;
    break;
  case LEFT:
    x--;
    break;
  case DOWN:
    y++;
    break;
  default:
    break;
  }
  if (mapa[y][x] == '*') {
    pontuacao += 10;
    mapa[y][x] = ' ';
  }

  // if (x > largura || x < 0 || y > altura || y < 0)
  //     gameOver = true;

  //   if (x == pontoX && y == pontoY) {
  //     pontoX = 2;
  //     pontoY = rand() % altura;
}

int main() {
  BufferedSerial pc(USBTX, USBRX, 115200);
   V5 = 1;
  
  Iniciar();

  while (!gameOver) {
    RenderizarMapa();
    Input();
    Input2();
    Logic();
    Logic2();
  }
  return 0;
}
