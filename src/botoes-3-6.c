#include "musicas.h"
#include "pico/stdlib.h"
#include "buzzer.h"
#include "leds.h"

void tocar_nota(uint pino_buzzer, int frequencia, int duracao) {
    controlar_buzzer(pino_buzzer, true);
    sleep_ms(duracao);
    controlar_buzzer(pino_buzzer, false);
}

void leds_ritmo(int ritmo) {
    if (ritmo == 1) {
        controlar_leds(13, true, 12, false, 11, false);  // LED vermelho
        sleep_ms(300);
        controlar_leds(13, false, 12, false, 11, false);
        sleep_ms(300);
    }
    // Adicionar outros padrões de LED conforme necessário
}

void musica_doom(uint pino_buzzer) {
    int frequencias[] = {
        440, 440, 440, 349, 440, 440, 440, 349, 
        440, 440, 440, 349, 440, 440, 440, 349, 
        440, 440, 440, 349, 440, 440, 440, 440
    };

    int duracoes[] = {
        200, 200, 200, 200, 200, 200, 200, 200,
        200, 200, 200, 200, 200, 200, 200, 200,
        200, 200, 200, 200, 200, 200, 200, 200
    }
}

void musica_ghostbusters(uint pino_buzzer) {
    void tocar_musica_ghostbusters() {
    int frequencias[] = {
        330, 330, 330, 330, 392, 392, 330, 330, 330, 330, 
        330, 330, 392, 392, 330, 330, 330, 330, 330, 330, 
        392, 392, 330, 330, 330, 330, 330, 330, 392, 392, 
        330, 330, 330, 330, 330, 330, 392, 392, 330, 330,
        330, 330, 330, 330, 392, 392, 330, 330, 330, 330
    };

    int duracoes[] = {
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 
        300, 300, 300, 300, 300, 300, 300, 300, 300, 300 
    }
}


