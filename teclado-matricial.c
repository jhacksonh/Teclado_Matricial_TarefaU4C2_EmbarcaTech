#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definição dos pinos e constantes
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BUZZER_PINO 21
#define FREQUENCIA_BUZZER 350 // Frequência do buzzer em Hz
#define TEMPO_DEBOUNCE 200    // Delay para debounce em milissegundos

// Configuração do teclado matricial
const uint pinos_colunas[4] = {4, 3, 2, 1}; // Pinos das colunas
const uint pinos_linhas[4] = {5, 6, 7, 8};  // Pinos das linhas

// Prototípos das funções
void inicializar_perifericos(uint pino_vermelho, uint pino_verde, uint pino_azul, int freq, int *pinos_linhas_teclado, int *pinos_colunas_teclado, uint pino_Buzzer);
void configurar_pino(uint pin, bool INorOUT);

void controlar_leds(bool vermelho, bool azul, bool verde);

void controlar_buzzer(uint pino_Buzzer, bool ativar);
void tocar(uint pino_Buzzer, int *notas, int *duracoes, int tamanho);

char detectar_tecla(int pinos_linhas_teclado[4], int pinos_colunas_teclado[4]);

void tocar_musica_mario();

int main()
{
    stdio_init_all();
    // Inicialização dos periféricos
    inicializar_perifericos(LED_VERMELHO, LED_VERDE, LED_AZUL, FREQUENCIA_BUZZER, pinos_linhas, pinos_colunas, BUZZER_PINO);
    while (true)
    {
        char tecla = detectar_tecla(pinos_linhas, pinos_colunas);
        switch (tecla)
        {
        case '0':
        tocar_musica_mario();
            break;    
        case '1':
            int notas_imperial_march[] = {440, 440, 440, 349, 262, 440, 349, 262, 440,  // Primeira parte
                                          880, 880, 880, 698, 523, 440, 349, 262, 440}; // Segunda parte
            // Duração de cada nota em milissegundos
            int duracoes_imperial_march[] = {500, 500, 500, 350, 150, 500, 350, 150, 1000,
                                             500, 500, 500, 350, 150, 500, 350, 150, 1000};
            int tamanho_imperial_march = 18;
            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                    controlar_leds(true, false, false);
                else if (i == 1)
                    controlar_leds(false, true, false);
                else if (i == 2)
                    controlar_leds(false, false, true);
                else
                    controlar_leds(true, true, true);
                sleep_ms(500);
            }
            controlar_buzzer(BUZZER_PINO, true);
            tocar(BUZZER_PINO, notas_imperial_march, duracoes_imperial_march, tamanho_imperial_march);
            break;
        case '2':
            break;
        default:
            break;
        }
        sleep_ms(TEMPO_DEBOUNCE); // Delay para debounce
    }

    return 0;
}
void configurar_pino(uint pin, bool INorOUT)
{
    gpio_init(pin);
    gpio_set_dir(pin, INorOUT);
}
// Função para inicializar periféricos
void inicializar_perifericos(uint pino_vermelho, uint pino_verde, uint pino_azul, int freq, int *pinos_linhas_teclado, int *pinos_colunas_teclado, uint pino_Buzzer)
{
    configurar_pino(pino_vermelho, GPIO_OUT);
    configurar_pino(pino_verde, GPIO_OUT);
    configurar_pino(pino_azul, GPIO_OUT);

    gpio_set_function(pino_Buzzer, GPIO_FUNC_PWM);
    int slice_num = pwm_gpio_to_slice_num(pino_Buzzer);

    uint32_t freq_sistema = clock_get_hz(clk_sys); // Frequência do sistema
    uint16_t wrap_valor = freq_sistema / freq - 1; // Define o valor de wrap
    pwm_set_wrap(slice_num, wrap_valor);
    pwm_set_gpio_level(pino_Buzzer, wrap_valor / 2); // Define duty cycle de 50%

    for (int i = 0; i < 4; i++)
    {
        configurar_pino(pinos_colunas_teclado[i], GPIO_OUT);
        gpio_put(pinos_colunas_teclado[i], 1); // Inicializa como desativado
        configurar_pino(pinos_linhas_teclado[i], GPIO_IN);
        gpio_pull_up(pinos_linhas_teclado[i]); // Habilita pull-up
    }
}

// Função para configurar pinoS
// Função para controlar o estado dos LEDs
void controlar_leds(bool vermelho, bool azul, bool verde)
{
    gpio_put(LED_VERMELHO, vermelho);
    gpio_put(LED_AZUL, azul);
    gpio_put(LED_VERDE, verde);
}

// Função para controlar o estado do buzzer
void controlar_buzzer(uint pino_Buzzer, bool ativar)
{
    pwm_set_enabled(pwm_gpio_to_slice_num(pino_Buzzer), ativar);
}
void tocar(uint pino_Buzzer, int *notas, int *duracoes, int tamanho)
{
    // Toca cada nota
    for (int i = 0; i < tamanho; i++)
    {
        int frequencia = notas[i];
        int duracao = duracoes[i];
        if (frequencia > 0)
        {
            int slice_num = pwm_gpio_to_slice_num(pino_Buzzer);
            uint32_t freq_sistema = clock_get_hz(clk_sys);       // Frequência do sistema
            uint16_t wrap_valor = freq_sistema / frequencia - 1; // Define o valor de wrap

            pwm_set_wrap(slice_num, wrap_valor);
            pwm_set_gpio_level(pino_Buzzer, wrap_valor / 2); // Define duty cycle de 50%
            pwm_set_enabled(slice_num, true);                // Ativa o PWM

            sleep_ms(duracao);                 // Duração da nota
            pwm_set_enabled(slice_num, false); // Desativa o PWM
        }
        else
        {
            sleep_ms(duracao); // Pausa (nota silenciosa)
        }
        sleep_ms(50); // Pequena pausa entre notas
    }
}

void tocar_musica_mario() {

    controlar_buzzer(BUZZER_PINO, true);

    // Melodia do tema do Mario
    int melodia[] = {
        2637, 2637, 0, 2637, 0, 2093, 2637, 0,
        3136, 0, 0, 0, 1568, 0,
    };

    // Duração das notas (tempo reduzido para acelerar a melodia)
    int tempo[] = {
        150, 150, 150, 150, 150, 150, 150, 150,
        150, 150, 150, 150, 150, 150, 
    };

    const uint tamanho_melodia = 14;

    tocar(BUZZER_PINO, melodia, tempo, tamanho_melodia);

}

// Função para detectar teclas pressionadas
const char mapa_teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
char detectar_tecla(int pinos_linhas_teclado[4], int pinos_colunas_teclado[4])
{
    static char ultima_tecla = 'n'; // Armazena a última tecla pressionada
    char tecla_atual = 'n';         // Nenhuma tecla pressionada inicialmente
    for (int col = 0; col < 4; col++)
    {
        gpio_put(pinos_colunas_teclado[col], 0); // Ativa a coluna
        for (int lin = 0; lin < 4; lin++)
        {
            if (gpio_get(pinos_linhas_teclado[lin]) == 0)
            { // Verifica se a tecla foi pressionada
                tecla_atual = mapa_teclado[3 - lin][col];
                while (gpio_get(pinos_linhas_teclado[lin]) == 0)
                { // Aguarda liberação da tecla
                    sleep_ms(10);
                }
                break;
            }
        }
        gpio_put(pinos_colunas_teclado[col], 1); // Desativa a coluna
        if (tecla_atual != 'n')
            break; // Sai do loop se uma tecla foi detectada
    }

    if (tecla_atual != 'n' && tecla_atual != ultima_tecla)
    {
        ultima_tecla = tecla_atual;
    }
    return tecla_atual; // Retorna a tecla pressionada ou 'n'
}