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
    int notas_doom[] = { 523, 523, 523, 523, 523, 523, 523, 523, 523, 523 }; 
    for (int i = 0; i < sizeof(notas_doom) / sizeof(int); i++) {
        tocar_nota(pino_buzzer, notas_doom[i], 500);
        leds_ritmo(1);  
    }
}

void musica_ghostbusters(uint pino_buzzer) {
    int notas_ghostbusters[] = { 330, 330, 330, 330, 392, 392 };
    for (int i = 0; i < sizeof(notas_ghostbusters) / sizeof(int); i++) {
        tocar_nota(pino_buzzer, notas_ghostbusters[i], 300);  
        leds_ritmo(1);  
    }
}


