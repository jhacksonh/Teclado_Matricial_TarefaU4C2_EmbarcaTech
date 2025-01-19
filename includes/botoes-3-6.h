#ifndef BOTOES_3_6_H
#define BOTOES_3_6_H

#include "pico/stdlib.h"

void tocar_nota(uint pino_buzzer, int frequencia, int duracao);
void leds_ritmo(int ritmo, uint red, uint green, uint blue);
void musica_doom(uint pino_buzzer,uint red, uint green, uint blue);
void musica_ghostbusters(uint pino_buzzer, uint red, uint green, uint blue);

#endif
