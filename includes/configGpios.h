#ifndef CONFIGGPIOS_H
#define CONFIGGPIOS_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

void configurar_pino(uint pin, bool INorOUT);
void inicializar_perifericos(uint pino_vermelho, uint pino_verde, uint pino_azul, int *pinos_linhas_teclado, int *pinos_colunas_teclado, uint pino_Buzzer);

#endif