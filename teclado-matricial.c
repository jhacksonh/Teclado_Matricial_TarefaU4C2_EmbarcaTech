#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "configGpios.h"
#include "tecladoMatricial4x4.h"
#include "leds.h"
#include "buzzer.h"
#include "pico/bootrom.h"
#include "codigoMorse.h"

// Definição dos pinos e constantes
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BUZZER_PINO 21
#define TEMPO_DEBOUNCE 200    // Delay para debounce em milissegundos

// Configuração do teclado matricial
uint pinos_colunas[4] = {4, 3, 2, 1}; // Pinos das colunas
uint pinos_linhas[4] = {5, 6, 7, 8};  // Pinos das linhas

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
                    controlar_leds(LED_VERMELHO, true, LED_VERDE, false, LED_AZUL, false);
                else if (i == 1)
                    controlar_leds(LED_VERMELHO, false, LED_VERDE, true, LED_AZUL, false);
                else if (i == 2)
                    controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, true);
                else
                    controlar_leds(LED_VERMELHO, true, LED_VERDE, true, LED_AZUL, true);
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
            controlar_leds(LED_VERMELHO, true, LED_VERDE, false, LED_AZUL, false);
            tocar(BUZZER_PINO, notas_imperial_march, duracoes_imperial_march, tamanho_imperial_march);
            controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, false);
            break;
        case '*':
            // 1) Ligar LED verde (GPIO 11) – desligar as demais GPIOs
            printf("led verde\n");
            controlar_leds(LED_VERMELHO, false, LED_VERDE, true, LED_AZUL, false);
            sleep_ms(1000); // Aguarda 1 segundo para visualizar a ação

            // 2) Ligar LED azul (GPIO 12) - desligar as demais GPIOs
            printf("led azul\n");
            controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, true);
            sleep_ms(1000);

            // 3) Ligar LED vermelho (GPIO 13) - desligar as demais GPIOs
            printf("led vermelho\n");
            controlar_leds(LED_VERMELHO, true, LED_VERDE, false, LED_AZUL, false);
            sleep_ms(1000);

            // 4) Ligar os três LEDs (luz branca)
            printf("led branco\n");
            controlar_leds(LED_VERMELHO, true, LED_VERDE, true, LED_AZUL, true);
            sleep_ms(1000);

            // 5) Desligar todos os LEDs
            printf("leds desligados\n");
            controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, false);
            sleep_ms(1000);

            // 6) Acionar o buzzer por 2 segundos – emissão de sinal sonoro
            printf("Buzzer\n");
            tocar_nota(BUZZER_PINO, 200, 2000); // 200 Hz por 2 segundos

            // 7) Reboot para o modo de gravação via USB
            printf("Entrando no modo de gravação via USB...\n");
            sleep_ms(1000); // Pequeno delay para garantir que a mensagem seja exibida antes do reboot
            printf("1...");
            sleep_ms(1000);
            printf("2...");
            sleep_ms(1000);
            printf("3...");
            sleep_ms(1000);
            reset_usb_boot(0, 0); // Reboot para modo de gravação
            break;
        case '8': 
            codigoMorse();
            break;
        default:
            break;
        }
        sleep_ms(TEMPO_DEBOUNCE); // Delay para debounce
    }

    return 0;
}