/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"
#include <iostream>
#include <vector>

string mensagemFinal;
int pontuacaoMaxima;
bool gameOver;
enum eDirecao { LEFT, RIGHT, UP, DOWN, STOP };
DigitalOut V5(PF_1);

struct Jogador {
  int x, y;
  AnalogIn VRx, VRy;
  int pontuacao;
  eDirecao dir;
};

Jogador jogador1 = {74, 37, PA_0, PA_1, 0, UP};
Jogador jogador2 = {2, 1, PC_1, PC_0, 0, DOWN};

char mapa[40][79] = {
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
"oo  *                             oooo                            oooo*     oo",
"oo                                oooo                            oooo      oo",
"oo  oooooooooooo  oooooooooooooo  oooo  oooooooooo  oooooooooo  oooooooooo  oo",
"oo  oooooooooooo  oooooooooooooo  oooo  oooooooooo  oooooooooo  oooooooooo  oo",
"oo                                                                          oo",
"oo                                                                          oo",
"oo  oooooooooooo  oo  oooooooooooooooooooooooooooooooooooooooo  oo  oooooo  oo",
"oo  oooooooooooo  oo  oooooooooooooooooooooooooooooooooooooooo  oo  oooooo  oo",
"oo  oo        oo  oo                                            oo    oo    oo",
"oo  oo        oo  oo                                            oo    oo    oo",
"oo      oooo      oooooooooooooooooooooo    oooooooooooooooooooooo      oo  oo",
"oo      oooo      oooooooooooooooooooooo    oooooooooooooooooooooo      oo  oo",
"oo  oo        oo  oo                                          * oo  oo      oo",
"oo  oo        oo  oo                                            oo  oo      oo",
"oo      oooo      oooo  oooooooo  oooooooo  oooooooo  oooooooo  oo      oo  oo",
"oo      oooo      oooo  oooooooo  oooooooo  oooooooo  oooooooo  oo      oo  oo",
"oo  oo  *     oo  oo                                            oo  oo      oo",
"oo  oo        oo  oo                                            oo  oo      oo",
"oo      oooo      oooooooooooooo  oooooooo  oooooooo  oooooooooooo      oo  oo",
"oo      oooo      oooooooooooooo  oooooooo  oooooooo  oooooooooooo      oo  oo",
"oo  oo        oo                                                    oo      oo",
"oo  oo        oo                                                    oo      oo",
"oo      oooo      oo  oooooooooooooooooooooooooooooooooooooooo  oo      oo  oo",
"oo      oooo      oo  oooooooooooooooooooooooooooooooooooooooo  oo      oo  oo",
"oo  oo        oo  oo                    * oo                    oo  oo      oo",
"oo  oo        oo  oo                      oo                    oo  oo      oo",
"oo     oooo       oo  oooooo  oooooo    oooooo  oooooo  oooooo  oo      oo* oo",
"oo     oooo       oo  oooooo  oooooo    oooooo  oooooo  oooooo  oo      oo  oo",
"oo  oo        oooooo                                            oo  oo    * oo",
"oo  oo        oooooo                                            oo  oo      oo",
"oo          oooooooo  oooooooooooooooo  oooooooooooooooooooooo  oo  oo  oo* oo",
"oo          oooooooo  oooooooooooooooo  oooooooooooooooooooooo  oo  oo  oo  oo",
"oo  oo                oooooooooooooooo  oooooooooooooooooooooo      oo    * oo",
"oo  oo                oooooooooooooooo  oooooooooooooooooooooo      oo      oo",
"oo      oo   ooooooooooooooooooooooooo  oooooooooooooooooooooooooo      oo* oo",
"oo      oo   ooooooooooooooooooooooooo  oooooooooooooooooooooooooo      oo  oo",
"oo                                                                          oo",
"oo                                                                          oo",
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
};

void Iniciar() { gameOver = false;
pontuacaoMaxima = 50; }

void RenderMapa() {
  for (int i = 0; i < 40; i++)
    cout << mapa[i] << endl;
}

void RenderizarMapa() {
  printf("\033[2J\033[H");
  printf("Pontuação: %d\n\n", jogador1.pontuacao);
  for (int i = 0; i < 40; i++) {
    for (int j = 0; j < 79; j++) {
      if (i == jogador1.y && j == jogador1.x) {
        cout << "\033[1;33m"
             << "👀"
             << "\033[0m";
        continue;
      }

      if (i == jogador1.y + 1 && j == jogador1.x) {
        cout << "\033[1;33m" << "👄" << "\033[0m";
        continue;
      }

      if ((i == jogador1.y && j == jogador1.x + 1) ||
          (i == jogador1.y + 1 && j == jogador1.x + 1))
        continue;

      if (i == jogador2.y && j == jogador2.x) {
        cout << "\033[1;32m"
             << "👀"
             << "\033[0m";
        continue;
      }

      if (i == jogador2.y + 1 && j == jogador2.x) {
        cout << "\033[1;32m"
             << "👄"
             << "\033[0m";
        continue;
      }

      if ((i == jogador2.y && j == jogador2.x + 1) ||
          (i == jogador2.y + 1 && j == jogador2.x + 1))
        continue;

      if (mapa[i][j] == 'o') {
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
  if (jogador2.dir == UP && mapa[jogador2.y - 1][jogador2.x] == 'o')
    return;

  if (jogador2.dir == DOWN && mapa[jogador2.y + 2][jogador2.x] == 'o')
    return;

  if (jogador2.dir == RIGHT && (mapa[jogador2.y][jogador2.x + 2] == 'o' ||
                                mapa[jogador2.y + 1][jogador2.x + 2] == 'o'))
    return;

  if (jogador2.dir == LEFT && (mapa[jogador2.y][jogador2.x - 1] == 'o' ||
                               mapa[jogador2.y + 1][jogador2.x - 1] == 'o'))
    return;

  switch (jogador2.dir) {
  case UP:
    jogador2.y = jogador2.y -2;
    break;
  case RIGHT:
    jogador2.x = jogador2.x + 2;
    break;
  case LEFT:
    jogador2.x = jogador2.x - 2;
    break;
  case DOWN:
    jogador2.y = jogador2.y + 2;
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

  if (jogador1.dir == UP && mapa[jogador1.y - 1][jogador1.x] == 'o')
    return;

  if (jogador1.dir == DOWN && mapa[jogador1.y + 2][jogador1.x] == 'o')
    return;

  if (jogador1.dir == RIGHT && (mapa[jogador1.y][jogador1.x + 2] == 'o' ||
                                mapa[jogador1.y + 1][jogador1.x + 2] == 'o'))
    return;

  if (jogador1.dir == LEFT && (mapa[jogador1.y][jogador1.x - 1] == 'o' ||
                               mapa[jogador1.y + 1][jogador1.x - 1] == 'o'))
    return;

  switch (jogador1.dir) {
  case UP:
    jogador1.y = jogador1.y - 2;
    break;
  case RIGHT:
    jogador1.x = jogador1.x + 2;
    break;
  case LEFT:
    jogador1.x = jogador1.x - 2;
    break;
  case DOWN:
    jogador1.y = jogador1.y + 2;
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
    //   RenderMapa();
    RenderizarMapa();
if(jogador1.pontuacao == pontuacaoMaxima)
        gameOver = true;
    Input();
    Input2();
    Logic();
    Logic2();
  }

  cout << gameOver;
  return 0;
}
