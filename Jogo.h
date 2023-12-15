#include "Jogador.h"
#include "Mapa.h"
#include <string>

class Jogo {
    public:
        int pontuacaoMaxima = 60;
        bool gameOver = false;
        string mensagemFinal = "";
        Jogador comeCome = {74, 37, 75, 38, 0, PA_0, PA_1, UP};
        Jogador inimigo = {2, 1, 3, 2, 0, PC_1, PC_0, RIGHT};;
        Mapa mapa;
        Thread thread1, player1, player2, thread3;
        Jogo();
        void Executar();
        void VerificarVencedor();
        void GameOver();
        void Direcao();
        void MovimentarComeCome();
        void MovimentarInimigo();
    private:
        Mutex mutex;
};