#include "Jogador.h"
#include "mbed.h"

Jogador::Jogador(int x, int y, int antigoX, int antigoY, int pontuacao, AnalogIn VRx, AnalogIn VRy, eDirecao dir)
    : x(x), y(y), antigoX(antigoX), antigoY(antigoY), pontuacao(pontuacao), VRx(VRx), VRy(VRy), dir(dir) { }

void Jogador::DefinirDirecao() {
    if (VRx.read() <= 0.33) {
        dir = LEFT;
    } else if (VRx.read() <= 0.66) {
        dir = RIGHT;
    } else if (VRy.read() <= 0.33) {
        dir = UP;
    } else if (VRy.read() <= 0.66) {
        dir = DOWN;
    }
}

void Jogador::AlterarPosicaoComeCome() {
    if (dir == UP && mapaJogo.mapa[y - 2][x] == 'o')
        return;

    if (dir == DOWN && mapaJogo.mapa[y + 1][x] == 'o')
        return;

    if (dir == RIGHT && mapaJogo.mapa[y][x + 2] == 'o')
        return;

    if (dir == LEFT && mapaJogo.mapa[y][x - 2] == 'o')
        return;

    antigoX = x;
    antigoY = y;

    switch(dir) {
        case UP:
            y = y - 2;
            break;
        case RIGHT:
            x = x + 2;
            break;
        case LEFT:
            x = x - 2;
            break;
        case DOWN:
            y = y + 2;
            break;
        default:
            break;
    }

    if (mapaJogo.mapa[antigoY--][antigoX--] == '*') {
        pontuacao += 10;
        mapaJogo.mapa[antigoY--][antigoX--] = ' ';
  }
}

void Jogador::AlterarPosicaoInimigo() {
    if (dir == UP && mapaJogo.mapa[y - 2][x] == 'o')
        return;

    if (dir == DOWN && mapaJogo.mapa[y + 1][x] == 'o')
        return;

    if (dir == RIGHT && mapaJogo.mapa[y][x + 2] == 'o')
        return;

    if (dir == LEFT && mapaJogo.mapa[y][x - 2] == 'o')
        return;

    antigoY = y;
    antigoX = x;

    switch(dir) {
        case UP:
            y = y - 2;
            break;
        case RIGHT:
            x = x + 2;
            break;
        case LEFT:
            x = x - 2;
            break;
        case DOWN:
            y = y + 2;
            break;
        default:
            break;
    }
}