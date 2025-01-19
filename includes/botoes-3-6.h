#ifndef BOTOES_3_6_H
#define BOTOES_3_6_H

#include "pico/stdlib.h"

void musica_doom(uint pino_buzzer);
void musica_ghostbusters(uint pino_buzzer);
void tocar_nota(uint pino_buzzer, int frequencia, int duracao);
void leds_ritmo(int ritmo);

#endif
