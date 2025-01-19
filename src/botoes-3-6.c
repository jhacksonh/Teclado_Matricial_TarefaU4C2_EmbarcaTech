#include "botoes-3-6.h"
#include "pico/stdlib.h"
#include "buzzer.h"
#include "leds.h"

void leds_ritmo(int ritmo, uint red, uint green, uint blue)
{
    if (ritmo == 1)
    {
        controlar_leds(red, true, green, false, blue, false); // LED vermelho
        sleep_ms(300);
        controlar_leds(red, false, green, false, blue, false);
        sleep_ms(300);
    }
    // Adicionar outros padrões de LED conforme necessário
}

void musica_doom(uint pino_buzzer,uint red, uint green, uint blue)
{
    int frequencias[] = {
        440, 440, 440, 349, 440, 440, 440, 349,
        440, 440, 440, 349, 440, 440, 440, 349,
        440, 440, 440, 349, 440, 440, 440, 440};

    int duracoes[] = {
        200, 200, 200, 200, 200, 200, 200, 200,
        200, 200, 200, 200, 200, 200, 200, 200,
        200, 200, 200, 200, 200, 200, 200, 200};

    for (int i = 0; i < sizeof(frequencias) / sizeof(frequencias[0]); i++){
        tocar_nota(pino_buzzer, frequencias[i], duracoes[i]);
        leds_ritmo(1, red,green,blue);
    }
}

void musica_ghostbusters(uint pino_buzzer, uint red, uint green, uint blue)
{
    int frequencias[] = {
        330, 330, 330, 330, 392, 392, 330, 330, 330, 330,
        330, 330, 392, 392, 330, 330, 330, 330, 330, 330,
        392, 392, 330, 330, 330, 330, 330, 330, 392, 392,
        330, 330, 330, 330, 330, 330, 392, 392, 330, 330,
        330, 330, 330, 330, 392, 392, 330, 330, 330, 330};

    int duracoes[] = {
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300};

    for (int i = 0; i < sizeof(frequencias) / sizeof(frequencias[0]); i++)
    {
        tocar_nota(pino_buzzer, frequencias[i], duracoes[i]);
        leds_ritmo(1, red,green,blue);
    }
}