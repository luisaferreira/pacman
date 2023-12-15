/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"
#include <iostream>
#include <string>
#include <vector>

Thread thread1;
Thread player1;
Thread player2;
Thread thread3;
Ticker ticker;
Mutex mutex;
int x = 0;

string mensagemFinal = "";
int pontuacaoMaxima;
bool gameOver;
enum eDirecao { LEFT, RIGHT, UP, DOWN, STOP };
DigitalOut V5(PF_1);

struct Teste {
    int a,b,c,d,e;
};

Teste teste = {0,0,0,0,0};

struct Jogador {
  int x, y;
  AnalogIn VRx, VRy;
  int pontuacao;
  eDirecao dir;
  int antigoX, antigoY;
};

Jogador jogador1 = {74, 37, PA_0, PA_1, 0, UP, 75, 38};
Jogador jogador2 = {2, 1, PC_1, PC_0, 0, RIGHT, 3, 2};

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
"oo     oooo       oo  oooooo  oooooo    oooooo  oooooo  oooooo  oo      oo  oo",
"oo     oooo       oo  oooooo  oooooo    oooooo  oooooo  oooooo  oo      oo  oo",
"oo  oo        oooooo                                            oo  oo      oo",
"oo  oo        oooooo                                            oo  oo      oo",
"oo          oooooooo  oooooooooooooooo  oooooooooooooooooooooo  oo  oo  oo  oo",
"oo          oooooooo  oooooooooooooooo  oooooooooooooooooooooo  oo  oo  oo  oo",
"oo  oo                oooooooooooooooo* oooooooooooooooooooooo      oo      oo",
"oo  oo                oooooooooooooooo  oooooooooooooooooooooo      oo      oo",
"oo      oo   ooooooooooooooooooooooooo  oooooooooooooooooooooooooo      oo  oo",
"oo      oo   ooooooooooooooooooooooooo  oooooooooooooooooooooooooo      oo  oo",
"oo                                                                          oo",
"oo                                                                          oo",
"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo",
};

void Iniciar() { 
    gameOver = false;
    pontuacaoMaxima = 60;
}

void RenderizarMapa() {
  printf("\033[2J\033[H");
  for (int i = 0; i < 40; i++) {
    for (int j = 0; j < 79; j++) {
      if (i == jogador1.y && j == jogador1.x) {
        cout << "\033[1;32m"
             << "👀"
             << "\033[0m";
        continue;
      }

      if (i == jogador1.y + 1 && j == jogador1.x) {
        cout << "\033[1;32m" << "👄" << "\033[0m";
        continue;
      }

      if ((i == jogador1.y && j == jogador1.x + 1) ||
          (i == jogador1.y + 1 && j == jogador1.x + 1))
        continue;

      if (i == jogador2.y && j == jogador2.x) {
        cout << "\033[1;31m"
             << "👀"
             << "\033[0m";
        continue;
      }

      if (i == jogador2.y + 1 && j == jogador2.x) {
        cout << "\033[1;31m"
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
  jogador1.y = jogador1.antigoY;
  jogador1.x = jogador1.antigoX;
  jogador2.y = jogador2.antigoY;
  jogador2.x = jogador2.antigoX;
}

void DefinirDirecaoJogador1() {
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

void DefinirDirecaoJogador2() {
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

void MovimentarJogador2() {
  if (jogador2.dir == UP && mapa[jogador2.y - 2][jogador2.x] == 'o')
    return;

  if (jogador2.dir == DOWN && mapa[jogador2.y + 1][jogador2.x] == 'o')
    return;

  if (jogador2.dir == RIGHT && mapa[jogador2.y][jogador2.x + 2] == 'o')
    return;

  if (jogador2.dir == LEFT && mapa[jogador2.y][jogador2.x - 2] == 'o')
    return;
  
  jogador2.antigoY = jogador2.y;
  jogador2.antigoX = jogador2.x;

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
}

void MovimentarJogador1() {
  if (jogador1.dir == UP && mapa[jogador1.y - 2][jogador1.x] == 'o')
    return;

  if (jogador1.dir == DOWN && mapa[jogador1.y + 1][jogador1.x] == 'o')
    return;

  if (jogador1.dir == RIGHT && mapa[jogador1.y][jogador1.x + 2] == 'o')
    return;

  if (jogador1.dir == LEFT && mapa[jogador1.y][jogador1.x - 2] == 'o')
    return;

  jogador1.antigoX = jogador1.x;
  jogador1.antigoY = jogador1.y;

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

  if (mapa[jogador1.antigoY - 1][jogador1.antigoX - 1] == '*') {
    jogador1.pontuacao += 10;
    mapa[jogador1.antigoY - 1][jogador1.antigoX - 1] = ' ';
  }
}

void VerificarVencedor() {
    if (jogador2.y == jogador1.y && jogador2.x == jogador1.x) {
        mensagemFinal = "🏆 Jogador 2 venceu! 🏆";
        cout << "\033[45;32H\033[33m" << mensagemFinal;
        ThisThread::sleep_for(300ms);
        gameOver = true;
    }
    else if(jogador1.pontuacao == pontuacaoMaxima) {
        mensagemFinal = "🏆 Jogador 1 venceu! 🏆";
        cout << "\033[44;32H\033[33m" << mensagemFinal;
        ThisThread::sleep_for(300ms);
        gameOver = true;
    }
}

void GameOver() {
  while (!gameOver) {
    mutex.lock();
    VerificarVencedor();
    mutex.unlock();
  }
}


void Movimentar1(){
    char v[3], v2[3], h[3];
    char novoV[3], novoV2[3], novoH[3];

    while (!gameOver) {
      mutex.lock();

      sprintf(v, "%d", jogador1.antigoY);
      sprintf(v2, "%d", jogador1.antigoY + 1);
      sprintf(h, "%d", jogador1.antigoX);

      sprintf(novoV, "%d", jogador1.y);
      sprintf(novoV2, "%d", jogador1.y + 1);
      sprintf(novoH, "%d", jogador1.x);
      
      cout << "\033[" << v << ";" << h << "H ";
      cout << "\033[" << v2 << ";" << h << "H ";
      cout << "\033[" << novoV << ";" << novoH << "H\033[32m👀";
      cout << "\033[" << novoV2 << ";" << novoH << "H\033[32m👄";

      mutex.unlock();
      ThisThread::sleep_for(200ms);
    }
}

void Movimentar2(){
    char v[3], v2[3], h[3];
    char novoV[3], novoV2[3], novoH[3];

    while (!gameOver) {
      mutex.lock();

      sprintf(v, "%d", jogador2.antigoY);
      sprintf(v2, "%d", jogador2.antigoY + 1);
      sprintf(h, "%d", jogador2.antigoX);

      sprintf(novoV, "%d", jogador2.y);
      sprintf(novoV2, "%d", jogador2.y + 1);
      sprintf(novoH, "%d", jogador2.x);

      if (mapa[jogador2.antigoY - 1][jogador2.antigoX - 1] == '*') {
        cout << "\033[" << v << ";" << h << "H\033[31m🍒\033[0m";
        cout << "\033[" << v2 << ";" << h << "H ";
      } else {
        cout << "\033[" << v << ";" << h << "H ";
        cout << "\033[" << v2 << ";" << h << "H ";
      }

      cout << "\033[" << novoV << ";" << novoH << "H\033[31m👀";
      cout << "\033[" << novoV2 << ";" << novoH << "H\033[31m👄";

      mutex.unlock();
      ThisThread::sleep_for(200ms);
    }
}

void Direcao() {
  
  while (!gameOver) {
    mutex.lock();
    DefinirDirecaoJogador1();
    DefinirDirecaoJogador2();
    MovimentarJogador1();
    MovimentarJogador2();
    mutex.unlock();
    ThisThread::sleep_for(200ms);
  }
}

int main() {
    BufferedSerial pc(USBTX, USBRX, 115200);
    V5 = 1;
    
    mutex.lock();
    RenderizarMapa();
    Iniciar();  
    ThisThread::sleep_for(300ms);
    mutex.unlock();
    
    thread1.start(Direcao);

    player1.start(Movimentar1);
    player2.start(Movimentar2);

    thread3.start(GameOver);

    while(true) {
        ThisThread::sleep_for(5000ms);
    }
}