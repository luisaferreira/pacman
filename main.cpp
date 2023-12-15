/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "rtos.h"
#include "Jogo.h"

DigitalOut V5(PF_1);


int main() {
    BufferedSerial pc(USBTX, USBRX, 115200);
    V5 = 1;
   
    Jogo jogo;

    jogo.Executar();

    while(true) {
        ThisThread::sleep_for(5000ms);
    }
}