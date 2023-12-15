#include "Jogo.h"

Jogo::Jogo() { }

void Jogo::VerificarVencedor() {
    if (inimigo.y == comeCome.y && inimigo.x == comeCome.x) {
        mensagemFinal = "🏆 Jogador 2 venceu! 🏆";
        cout << "\033[45;32H\033[33m" << mensagemFinal;
        ThisThread::sleep_for(300ms);
        gameOver = true;
    }
    else if(comeCome.pontuacao == pontuacaoMaxima) {
        mensagemFinal = "🏆 Jogador 1 venceu! 🏆";
        cout << "\033[44;32H\033[33m" << mensagemFinal;
        ThisThread::sleep_for(300ms);
        gameOver = true;
    }
}

void Jogo::GameOver() {
  while (!gameOver) {
    mutex.lock();
    VerificarVencedor();
    mutex.unlock();
  }
}

void Jogo::MovimentarComeCome() {
    char v[3], v2[3], h[3];
    char novoV[3], novoV2[3], novoH[3];

    while (!gameOver) {
      mutex.lock();

      sprintf(v, "%d", comeCome.antigoY);
      sprintf(v2, "%d", comeCome.antigoY + 1);
      sprintf(h, "%d", comeCome.antigoX);

      sprintf(novoV, "%d", comeCome.y);
      sprintf(novoV2, "%d", comeCome.y++);
      sprintf(novoH, "%d", comeCome.x);
      
      cout << "\033[" << v << ";" << h << "H ";
      cout << "\033[" << v2 << ";" << h << "H ";
      cout << "\033[" << novoV << ";" << novoH << "H\033[32m👀";
      cout << "\033[" << novoV2 << ";" << novoH << "H\033[32m👄";

      mutex.unlock();
      ThisThread::sleep_for(200ms);
    }
}

void Jogo::MovimentarInimigo() {
    char v[3], v2[3], h[3];
    char novoV[3], novoV2[3], novoH[3];

    while (!gameOver) {
      mutex.lock();

      sprintf(v, "%d", inimigo.antigoY);
      sprintf(v2, "%d", inimigo.antigoY + 1);
      sprintf(h, "%d", inimigo.antigoX);

      sprintf(novoV, "%d", inimigo.y);
      sprintf(novoV2, "%d", inimigo.y + 1);
      sprintf(novoH, "%d", inimigo.x);

      if (mapa.mapa[inimigo.antigoY - 1][inimigo.antigoX - 1] == '*') {
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

void Jogo::Direcao() {
  
  while (!gameOver) {
    mutex.lock();
    comeCome.DefinirDirecao();
    inimigo.DefinirDirecao();
    comeCome.AlterarPosicaoComeCome();
    inimigo.AlterarPosicaoInimigo();
    mutex.unlock();
    ThisThread::sleep_for(200ms);
  }
}

void Jogo::Executar() {
    mapa.RenderizarMapa();
    thread1.start(Direcao);
    player1.start(MovimentarComeCome);
    player2.start(MovimentarInimigo);
    thread3.start(GameOver);
}