/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"
#include <iostream>
#include <vector>

string mensagemFinal;
bool gameOver;
enum eDirecao { LEFT, RIGHT, UP, DOWN };
DigitalOut V5(PF_1);

struct Jogador{
    int x, y;
    AnalogIn VRx, VRy;
    int pontuacao;
    eDirecao dir;
};

Jogador jogador1 = { 14, 4, PA_0, PA_1, 0, DOWN };
Jogador jogador2 = { 14, 1, PC_1, PC_0, 0, RIGHT };


char mapa[9][30] = {
    "#############################", "#*                         *#",
    "# ############ ############ #", "# ############ ############ #",
    "#                           #", "# ############ ############ #",
    "# ############ ############ #", "#*                         *#",
    "#############################"};

void Iniciar() {
  gameOver = false;
}

void RenderizarMapa() {
  printf("\033[2J\033[H");
  printf("Pontuação: %d\n\n", jogador1.pontuacao);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 30; j++) {
      if (i == jogador1.y && j == jogador1.x) {
        cout << "\033[1;33m" << '>' << "\033[0m";
        continue;
      }

      if(i == jogador2.y && j == jogador2.x) {
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
  if (jogador1.VRx.read() <= 0.33) {
    jogador1.dir = LEFT;
  } else if (jogador1.VRx.read() >= 0.66) {
    jogador1.dir = RIGHT;
  } else if (jogador1.VRy.read() <= 0.33) {
    jogador1.dir = UP;
  } else if (jogador1.VRy.read() >= 0.66) {
    jogador1.dir = DOWN;
  }
}

 void Input2() {
   if (jogador2.VRx.read() <= 0.33) {
     jogador2.dir = LEFT;
   } else if (jogador2.VRx.read() >= 0.66) {
     jogador2.dir = RIGHT;
   } else if (jogador2.VRy.read() <= 0.33) {
     jogador2.dir = UP;
   } else if (jogador2.VRy.read() >= 0.66) {
     jogador2.dir = DOWN;
   }
}

void Logic2() {
  if (jogador2.dir == UP && mapa[jogador2.y - 1][jogador2.x] == '#')
    return;

  if (jogador2.dir == DOWN && mapa[jogador2.y + 1][jogador2.x] == '#')
    return;

  if (jogador2.dir == RIGHT && mapa[jogador2.y][jogador2.x + 1] == '#')
    return;

  if (jogador2.dir == LEFT && mapa[jogador2.y][jogador2.x - 1] == '#')
    return;

  
  
  switch (jogador2.dir) {
  case UP:
    jogador2.y--;
    break;
  case RIGHT:
    jogador2.x++;
    break;
  case LEFT:
    jogador2.x--;
    break;
  case DOWN:
    jogador2.y++;
    break;
  default:
    break;
  }

  if (jogador2.y == jogador1.y && jogador2.x == jogador1.x) {
    gameOver = true;
    mensagemFinal = "Jogador 2 venceu";
  }
}

void Logic() {
  if (jogador1.dir == UP && mapa[jogador1.y - 1][jogador1.x] == '#')
    return;

  if (jogador1.dir == DOWN && mapa[jogador1.y + 1][jogador1.x] == '#')
    return;

  if (jogador1.dir == RIGHT && mapa[jogador1.y][jogador1.x + 1] == '#')
    return;

  if (jogador1.dir == LEFT && mapa[jogador1.y][jogador1.x - 1] == '#')
    return;

  switch (jogador1.dir) {
  case UP:
    jogador1.y--;
    break;
  case RIGHT:
    jogador1.x++;
    break;
  case LEFT:
    jogador1.x--;
    break;
  case DOWN:
    jogador1.y++;
    break;
  default:
    break;
  }
  if (mapa[jogador1.y][jogador1.x] == '*') {
    jogador1.pontuacao += 10;
    mapa[jogador1.y][jogador1.x] = ' ';
  }
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

  cout << mensagemFinal;
  return 0;
}
