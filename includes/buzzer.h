#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
void controlar_buzzer(uint pino_Buzzer, bool ativar);
void tocar(uint pino_Buzzer, int *notas, int *duracoes, int tamanho);
// void tocar_nota(uint pino_Buzzer, int frequencia, int duracao);

#endif