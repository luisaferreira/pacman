#pragma once

class Mapa {
    public:
        char mapa[40][79];
        Mapa();
        void RenderizarMapa();
    private:
        static const int linhas = 40;
        static const int colunas = 79;
};