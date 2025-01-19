#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "configGpios.h"
#include "tecladoMatricial4x4.h"
#include "leds.h"
#include "buzzer.h"
#include "pico/bootrom.h"
#include "botoes-1-2.h"
#include "botoes-3-6.h"
#include "botoes8-9.h"
#include "botoes_a_b.h"

// Definição dos pinos e constantes
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BUZZER_PINO 21
#define TEMPO_DEBOUNCE 200 // Delay para debounce em milissegundos

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

void tocar_musica_mario();
void letra_d_em_morse();
// botões 5 e 7
void tocar_fur_elise();
void notas_som();

void piscar_led_quatro_vezes();
void letra_c_em_morse();

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
        case '0': // Toca a música do Mario e anima leds quando a tecla 0 é pressionada
            tocar_musica_mario();
            break;

        case '1':
            Notas_Musicais_Tecla_1(BUZZER_PINO, LED_VERMELHO, LED_VERDE, LED_AZUL);
            break;
        case '2':
            Sequencia_Aleatoria_Tecla_2(BUZZER_PINO, LED_VERMELHO, LED_VERDE, LED_AZUL);
            break;
        case 'D':
            letra_d_em_morse();
            break;
        case '3':
            musica_doom(BUZZER_PINO, LED_VERMELHO, LED_VERDE, LED_AZUL);
            break;
        case '4':
            piscar_led_quatro_vezes();
            break;
        case '6':
            musica_ghostbusters(BUZZER_PINO, LED_VERMELHO, LED_VERDE, LED_AZUL);
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

        case '5':
            tocar_fur_elise();
            break;
        case '7':
            notas_som();
            break;
        case '8':
            codigoMorse();
            break;
        case '9':
            tocar_musica_jingle_bells();
            break;
        case 'A':
            printf("Tecla A pressionada\n");
            jogo_memoria(pinos_linhas, pinos_colunas, (uint[]){LED_VERMELHO, LED_AZUL, LED_VERDE}, BUZZER_PINO);
            break;
        case 'B':
            printf("Tecla B pressionada\n");
            jogo_memoria(pinos_linhas, pinos_colunas, (uint[]){LED_VERMELHO, LED_AZUL, LED_VERDE}, BUZZER_PINO);
            break;
        case 'C':
            letra_c_em_morse();
            break;
        default:
            break;
        }
        sleep_ms(TEMPO_DEBOUNCE); // Delay para debounce
    }

    return 0;
}

void tocar_musica_mario()
{
    // animação de leds
    controlar_leds(LED_VERMELHO, true, LED_VERDE, false, LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, true);
    sleep_ms(500);
    controlar_leds(LED_VERMELHO, false, LED_VERDE, true, LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, true);
    sleep_ms(500);
    controlar_leds(LED_VERMELHO, true, LED_VERDE, false, LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(LED_VERMELHO, true, LED_VERDE, true, LED_AZUL, true);

    controlar_buzzer(BUZZER_PINO, true); // Ativa o buzzer

    // Melodia do tema do Mario
    int melodia[] = {
        2637,
        2637,
        0,
        2637,
        0,
        2093,
        2637,
        0,
        3136,
        0,
        0,
        0,
        1568,
        0,
    };

    // Duração das notas (tempo reduzido para acelerar a melodia)
    int tempo[] = {
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
        150,
    };

    const uint tamanho_melodia = 14; // Tamanho da melodia

    tocar(BUZZER_PINO, melodia, tempo, tamanho_melodia); // Toca a melodia

    controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, false); // Desliga os LEDs
}

// Função para representar a letra D em código Morse
void letra_d_em_morse()
{

    // A letra D é representada por "-.."
    // O ponto é representado por 200 ms e o traço por 800 ms
    // o intervalo entre os sinais é 125 ms

    int melodia[] = {
        1000, 0, 1000, 0, 1000, 0};

    int tempo[] = {
        800, 125, 200, 125, 200, 125};

    const uint tamanho_melodia = 6; // Tamanho da melodia

    controlar_buzzer(BUZZER_PINO, true);

    tocar(BUZZER_PINO, melodia, tempo, tamanho_melodia); // Toca a melodia
}

/* Função responsável por controlar o botão 5 do teclado matricial. Ao acionar este botão, será
reproduzido com o buzzer as 20 primeiras notas da música Fur Elise */

///
void tocar_fur_elise()
{
    // 20 primeiras notas da música Fur Elise de Beethoven

    int notas_fur_elise[] = {659, 622, 659, 622, 659, 494, 587, 523, 440, 494, 523, 587, 659, 494, 523, 587, 659, 622, 659, 622};

    // para definir a duracao de cada nota, será utilizado 200 ms entre cada nota
    int duracao_notas_fur[] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200};

    // quantidade das notas tocadas
    int tamanho_fur_elise = 20;

    controlar_buzzer(BUZZER_PINO, true);
    tocar(BUZZER_PINO, notas_fur_elise, duracao_notas_fur, tamanho_fur_elise);
    controlar_buzzer(BUZZER_PINO, false);
}

//
void notas_som()
{
    // Sequência de cores e sons
    int cores[] = {LED_VERMELHO, LED_VERDE, LED_AZUL, LED_VERMELHO, LED_VERDE, LED_AZUL};
    int notas[] = {262, 294, 330, 349, 392, 440};    // Notas C, D, E, F, G, A
    int duracoes[] = {500, 500, 500, 500, 500, 500}; // Duração de cada nota em ms

    for (int i = 0; i < 6; i++)
    {
        // Acende o LED correspondente e toca cada nota
        controlar_leds(LED_VERMELHO,true, LED_VERDE,false, LED_AZUL,false);
        tocar_nota(BUZZER_PINO, notas[i], duracoes[i]);

        // Pausa entre as mudanças
        sleep_ms(200);
    }

    // Desliga todos os LEDs no final
    controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, false);
}

// Função para piscar os leds 4 vezes
void piscar_led_quatro_vezes() {
    for (int i = 0; i < 4; i++) {
        controlar_leds(LED_VERMELHO, true, LED_VERDE, true, LED_AZUL, true);
        sleep_ms(500);
        controlar_leds(LED_VERMELHO, false, LED_VERDE, false, LED_AZUL, false);
        sleep_ms(500);
    }
}

// Função para representar a letra C em código Morse
void letra_c_em_morse() 
{

    // A letra C é representada por "-.-."

    int melodia[] = {
        1000, 0, 1000, 0, 1000, 0, 100, 0};

    int tempo[] = {
        800, 125, 200, 125, 800, 125, 200, 125};

    const uint tamanho_melodia = 8; // Tamanho da melodia

    controlar_buzzer(BUZZER_PINO, true);

    tocar(BUZZER_PINO, melodia, tempo, tamanho_melodia); // Toca a melodia
}