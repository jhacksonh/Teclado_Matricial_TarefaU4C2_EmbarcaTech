#include <stdlib.h>
#include "pico/stdlib.h"
#include "configGpios.h"
#include "botoes-1-2.h"
#include "leds.h"
#include "buzzer.h"

static void Leds_Aleatorios(uint pino_vermelho, uint pino_verde, uint pino_azul)
{
    int random2 = rand() % 8;
    if (random2 == 0)controlar_leds(pino_vermelho, false, pino_verde, false, pino_azul, false);
    if (random2 == 1)controlar_leds(pino_vermelho, false, pino_verde, false, pino_azul, true);
    if (random2 == 2)controlar_leds(pino_vermelho, false, pino_verde, true, pino_azul, false);
    if (random2 == 3)controlar_leds(pino_vermelho, false, pino_verde, true, pino_azul, true);
    if (random2 == 4)controlar_leds(pino_vermelho, true, pino_verde, false, pino_azul, false);
    if (random2 == 5)controlar_leds(pino_vermelho, true, pino_verde, false, pino_azul, true);
    if (random2 == 6)controlar_leds(pino_vermelho, true, pino_verde, true, pino_azul, false);
    if (random2 == 7)controlar_leds(pino_vermelho, true, pino_verde, true, pino_azul, true);
}

void Notas_Musicais_Tecla_1(uint pino_buzzer, uint pino_vermelho, uint pino_verde, uint pino_azul){
    int notas[] = {524, 588, 660, 698, 784, 880, 988, 0};       // Notas (Dó, Ré, Mi...)
    int durations[] = {300, 300, 300, 300, 300, 300, 300, 300}; // Duração de cada nota
    int notes_count = sizeof(notas) / sizeof(notas[0]);
    for (size_t i = 0; i < notes_count; i++){
        tocar_nota(pino_buzzer, notas[i], durations[i]);
        Leds_Aleatorios(pino_vermelho, pino_verde, pino_azul);
    }
    sleep_ms(500);
    for (size_t i = notes_count; i > 0; i--){
        tocar_nota(pino_buzzer, notas[i - 1], durations[i - 1]);
        Leds_Aleatorios(pino_vermelho, pino_verde, pino_azul);
    }
    sleep_ms(300);
    controlar_leds(pino_vermelho, false, pino_verde, false, pino_azul, false);
}
void Sequencia_Aleatoria_Tecla_2(uint pino_buzzer, uint pino_vermelho, uint pino_verde, uint pino_azul){
    int notas[] = {2200, 2200, 2200, 2200, 2400, 2200, 2400, 2200, 0, 2200, 2200, 2200, 2200, 2400, 2200, 2400, 2200, 0, 2200, 2200, 2400, 2400, 2200, 2400, 2200, 0, 2200, 2400, 2200, 2400, 2200, 2400, 0, 2200, 2400, 2200, 2400, 2200, 0, 2200, 2400, 2200, 2400, 2200, 2400, 0, 2200, 2400, 2200, 2400, 2200, 0, 2200, 2400, 2200, 2400, 2200, 0};
    for (size_t i = 0; i < sizeof(notas) / sizeof(notas[0]); i++)
    {
        int random = rand() % 301 + 50;
        tocar_nota(pino_buzzer, notas[i], random);
        sleep_ms(random);
        Leds_Aleatorios(pino_vermelho, pino_verde, pino_azul);
    }
    sleep_ms(300);
    controlar_leds(pino_vermelho, false, pino_verde, false, pino_azul, false);
}