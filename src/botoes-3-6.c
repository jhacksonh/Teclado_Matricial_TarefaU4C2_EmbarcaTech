#include "musicas.h"
#include "pico/stdlib.h"
#include "buzzer.h"
#include "leds.h"

void tocar_nota(uint pino_buzzer, int frequencia, int duracao) {
    controlar_buzzer(pino_buzzer, true);
    sleep_ms(duracao);
    controlar_buzzer(pino_buzzer, false);
}
