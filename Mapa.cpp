#include "Mapa.h"
#include <iostream>

Mapa::Mapa() {
   const char mapaInicial[linhas][colunas] = {
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

    //Atribuindo os valores de mapaInicial à mapa
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            mapa[i][j] = mapaInicial[i][j];
        }
    }
}

void Mapa::RenderizarMapa() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (i == 37 && j == 74) {
        cout << "\033[1;32m" << "👀";
        continue;
      }

      if (i == 38 && j == 74) {
        cout << "\033[1;32m" << "👄";
        continue;
      }

      if ((i == 37 && j == 75) || (i == 38 && j == 75))
        continue;

      if (i == 1 && j == 2) {
        cout << "\033[1;31m" << "👀";
        continue;
      }

      if (i == 2 && j == 2) {
        cout << "\033[1;31m" << "👄";
        continue;
      }

      if ((i == 1 && j == 3) || (i == 2 && j == 3))
        continue;

      if (mapa[i][j] == 'o') {
        cout << "\033[1;34;44m" << mapa[i][j];
      } else if (mapa[i][j] == '*') {
        cout << "\033[1;31m" << mapa[i][j];
      } else {
        cout << "\033[0m" << mapa[i][j];
      }
    }
    cout << endl;
  }
  //jogador1.y = jogador1.antigoY;
  //jogador1.x = jogador1.antigoX;
  //jogador2.y = jogador2.antigoY;
  //jogador2.x = jogador2.antigoX;
}