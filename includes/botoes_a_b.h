#ifndef BOTOES_A_B_H
#define BOTOES_A_B_H

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "tecladoMatricial4x4.h"
#include "leds.h"
#include "buzzer.h"


#define NUM_LEDS 3
#define MAX_SEQUENCIA 100

void jogo_memoria(int pinos_linhas_teclado[4], int pinos_colunas_teclado[4], uint pinos_leds[NUM_LEDS], uint pino_buzzer);

#endif // BOTOES_A_B_H
