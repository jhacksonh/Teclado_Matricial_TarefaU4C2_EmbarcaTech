#include <pico/stdlib.h>
#include "leds.h"

void controlar_leds(uint pino_vermelho,bool vermelho,uint pino_verde,bool verde, uint pino_azul, bool azul)
{
    gpio_put(pino_vermelho, vermelho);
    gpio_put(pino_verde, verde);
    gpio_put(pino_azul, azul);
}

