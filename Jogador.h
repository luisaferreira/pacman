#pragma once

#include "mbed.h"
#include "Mapa.h"

enum eDirecao { LEFT, RIGHT, UP, DOWN };

class Jogador {
    public:
        int x, y, antigoX, antigoY, pontuacao;
        AnalogIn VRx, VRy;
        eDirecao dir;
        Jogador(int x, int y, int antigoX, int antigoY, int pontuacao, AnalogIn VRx, AnalogIn VRy, eDirecao dir);
        void DefinirDirecao();
        void AlterarPosicaoComeCome();
        void AlterarPosicaoInimigo();
    private:
        Mapa mapaJogo;
};