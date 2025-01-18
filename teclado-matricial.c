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

int notas_imperial_march[] = {440, 440, 440, 349, 262, 440, 349, 262, 440,  // Primeira parte
                              880, 880, 880, 698, 523, 440, 349, 262, 440}; // Segunda parte
// Duração de cada nota em milissegundos
int duracoes_imperial_march[] = {500, 500, 500, 350, 150, 500, 350, 150, 1000,
                                 500, 500, 500, 350, 150, 500, 350, 150, 1000};
int tamanho_imperial_march = 18;

// Configuração do teclado matricial
const uint8_t pinos_colunas[4] = {4, 3, 2, 1}; // Pinos das colunas
const uint8_t pinos_linhas[4] = {5, 6, 7, 8};  // Pinos das linhas
const char mapa_teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Prototípos das funções
void inicializar_perifericos();
void configurar_pino_saida(uint pin);
void configurar_pino_entrada(uint pin);
void controlar_leds(bool vermelho, bool azul, bool verde);
void controlar_buzzer(bool ativar);
char detectar_tecla();
void tocar(int *notas, int *duracoes, int tamanho);
void codigo_morse();
void letra_A();
void letra_E();
void letra_M();
void letra_B();
void letra_R();
void letra_D();
void letra_O();
void letra_C();

int main()
{
    stdio_init_all();
    // Inicialização dos periféricos
    inicializar_perifericos();
    while (true)
    {
        char tecla = detectar_tecla();
        switch (tecla)
        {
        case '1':
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
            controlar_buzzer(true);
            tocar(notas_imperial_march, duracoes_imperial_march, tamanho_imperial_march);
            break;
        case '2':
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
// Função para inicializar periféricos
void inicializar_perifericos()
{
    configurar_pino_saida(LED_VERMELHO);
    configurar_pino_saida(LED_AZUL);
    configurar_pino_saida(LED_VERDE);

    gpio_set_function(BUZZER_PINO, GPIO_FUNC_PWM);
    int slice_num = pwm_gpio_to_slice_num(BUZZER_PINO);

    uint32_t freq_sistema = clock_get_hz(clk_sys);              // Frequência do sistema
    uint16_t wrap_valor = freq_sistema / FREQUENCIA_BUZZER - 1; // Define o valor de wrap

    pwm_set_wrap(slice_num, wrap_valor);
    pwm_set_gpio_level(BUZZER_PINO, wrap_valor / 2); // Define duty cycle de 50%

    for (int i = 0; i < 4; i++)
    {
        configurar_pino_saida(pinos_colunas[i]);
        gpio_put(pinos_colunas[i], 1); // Inicializa como desativado
        configurar_pino_entrada(pinos_linhas[i]);
        gpio_pull_up(pinos_linhas[i]); // Habilita pull-up
    }
}
// Função para configurar um pino como saída
void configurar_pino_saida(uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

// Função para configurar um pino como entrada
void configurar_pino_entrada(uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}
// Função para controlar o estado dos LEDs
void controlar_leds(bool vermelho, bool azul, bool verde)
{
    gpio_put(LED_VERMELHO, vermelho);
    gpio_put(LED_AZUL, azul);
    gpio_put(LED_VERDE, verde);
}
// Função para controlar o estado do buzzer
void controlar_buzzer(bool ativar)
{
    pwm_set_enabled(pwm_gpio_to_slice_num(BUZZER_PINO), ativar);
}
// Função para detectar teclas pressionadas
char detectar_tecla()
{
    static char ultima_tecla = 'n'; // Armazena a última tecla pressionada
    char tecla_atual = 'n';         // Nenhuma tecla pressionada inicialmente

    for (int col = 0; col < 4; col++)
    {
        gpio_put(pinos_colunas[col], 0); // Ativa a coluna

        for (int lin = 0; lin < 4; lin++)
        {
            if (gpio_get(pinos_linhas[lin]) == 0)
            { // Verifica se a tecla foi pressionada
                tecla_atual = mapa_teclado[3 - lin][col];

                while (gpio_get(pinos_linhas[lin]) == 0)
                { // Aguarda liberação da tecla
                    sleep_ms(10);
                }
                break;
            }
        }
        gpio_put(pinos_colunas[col], 1); // Desativa a coluna
        if (tecla_atual != 'n')
            break; // Sai do loop se uma tecla foi detectada
    }

    if (tecla_atual != 'n' && tecla_atual != ultima_tecla)
    {
        ultima_tecla = tecla_atual;
    }
    return tecla_atual; // Retorna a tecla pressionada ou 'n'
}

void tocar(int *notas, int *duracoes, int tamanho)
{
    // Toca cada nota
    for (int i = 0; i < tamanho; i++)
    {
        int frequencia = notas[i];
        int duracao = duracoes[i];
        if (frequencia > 0)
        {
            int slice_num = pwm_gpio_to_slice_num(BUZZER_PINO);
            uint32_t freq_sistema = clock_get_hz(clk_sys);       // Frequência do sistema
            uint16_t wrap_valor = freq_sistema / frequencia - 1; // Define o valor de wrap

            pwm_set_wrap(slice_num, wrap_valor);
            pwm_set_gpio_level(BUZZER_PINO, wrap_valor / 2); // Define duty cycle de 50%
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

/*
função: codigo_morse();

Código morse:
E -> um ponto 
M -> dois traços
B -> um traço, três pontos
A -> um ponto, um traço
R -> um ponto, um traço, um ponto
C -> um traço, um ponto, um traço, um ponto
A -> um ponto, um traço
D -> um traço, dois pontos
O -> três traços 

Representação no código:
um ponto -> led vermelho piscando por 500 ms
um traço -> led verde piscando por 500 ms 
tempo entre pontos e traços -> leds apagados por 300 ms 
tempo entre letras -> leds apagados por 600 ms

*/

void codigo_morse() {
    controlar_leds(false, false, false);

    letra_E();
    sleep_ms(600); 
    letra_M();
    sleep_ms(600);
    letra_B();
    sleep_ms(600);
    letra_A();
    sleep_ms(600);
    letra_R();
    sleep_ms(600);
    letra_C();
    sleep_ms(600);
    letra_A();
    sleep_ms(600);
    letra_D();
    sleep_ms(600);
    letra_O(); 

    controlar_leds(false, false, false); 
}

void ponto() {
    controlar_leds(true, false, false);
    sleep_ms(3000);
    controlar_leds(false, false, false);
    sleep_ms(300);
}

void traco() {
    controlar_leds(false, false, true);
    sleep_ms(500);
    controlar_leds(false, false, false);
    sleep_ms(500);
}

void letra_E() 
{
    ponto();
}

void letra_M() 
{
    traco();
    traco();
}

void letra_B() 
{
    traco();
    ponto(); 
    ponto(); 
    ponto();
}

void letra_A() 
{
    ponto();
    traco();
}

void letra_R() 
{
    ponto();
    traco();
    ponto();
}

void letra_C() 
{
    traco();
    ponto();
    traco();
    ponto();
}

void letra_D() 
{
    traco();
    ponto();
    ponto();
}

void letra_O() 
{
    traco();
    traco();
    traco();
}