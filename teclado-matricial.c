#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "configGpios.h"
#include "tecladoMatricial4x4.h"
#include "leds.h"
#include "buzzer.h"

// Definição dos pinos e constantes
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BUZZER_PINO 21
#define TEMPO_DEBOUNCE 200    // Delay para debounce em milissegundos

// Configuração do teclado matricial
const uint pinos_colunas[4] = {4, 3, 2, 1}; // Pinos das colunas
const uint pinos_linhas[4] = {5, 6, 7, 8};  // Pinos das linhas

// Notas da música Imperial March de Star Wars
int notas_imperial_march[] = {440, 440, 440, 349, 262, 440, 349, 262, 440,  // Primeira parte
                              880, 880, 880, 698, 523, 440, 349, 262, 440}; // Segunda parte
// Duração de cada nota em milissegundos
int duracoes_imperial_march[] = {500, 500, 500, 350, 150, 500, 350, 150, 1000,
                                 500, 500, 500, 350, 150, 500, 350, 150, 1000};
int tamanho_imperial_march = 18;

// Prototípos das funções
int main()
{

    stdio_init_all();
    // Inicialização dos periféricos
    inicializar_perifericos(LED_VERMELHO, LED_VERDE, LED_AZUL, pinos_linhas, pinos_colunas, BUZZER_PINO);
    while (true)
    {
        char tecla = detectar_tecla(pinos_linhas, pinos_colunas);
        switch (tecla)
        {
        case '1':
            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                    controlar_leds(LED_VERMELHO, true,LED_VERDE, false,LED_AZUL, false);
                else if (i == 1)
                    controlar_leds(LED_VERMELHO, false,LED_VERDE, true,LED_AZUL, false);
                else if (i == 2)
                    controlar_leds(LED_VERMELHO, false,LED_VERDE, false,LED_AZUL, true);
                else
                    controlar_leds(LED_VERMELHO,true,LED_VERDE, true,LED_AZUL, true);
                sleep_ms(500);
            }
            controlar_buzzer(BUZZER_PINO, true);
            // tocar(BUZZER_PINO, notas_imperial_march, duracoes_imperial_march, tamanho_imperial_march);
            tocar_nota(BUZZER_PINO, 500, 300);
            break;
        case '2':
            break;
        case '#':
            printf("Tecla # pressionada\n");
            controlar_leds(LED_AZUL,true,LED_VERDE, false,LED_AZUL, false);
            tocar(BUZZER_PINO, notas_imperial_march, duracoes_imperial_march, tamanho_imperial_march);
            controlar_leds(LED_VERMELHO, false,LED_VERDE, false,LED_AZUL, false);
            break;
        case '*':
            printf("Tecla * pressionada\n");
            tocar_nota(BUZZER_PINO, 1000, 500);
            break;
        case '8': 
            codigo_morse();
            break;
        default:
            break;
        }
        sleep_ms(TEMPO_DEBOUNCE); // Delay para debounce
    }

    return 0;
}