#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "configGpios.h"

#define FREQUENCIA_BUZZER 350 // Frequência do buzzer em Hz
void configurar_pino(uint pin, bool INorOUT)
{
    gpio_init(pin);
    gpio_set_dir(pin, INorOUT);
}
// Função para inicializar periféricos
void inicializar_perifericos(uint pino_vermelho, uint pino_verde, uint pino_azul, int *pinos_linhas_teclado, int *pinos_colunas_teclado, uint pino_Buzzer){
    configurar_pino(pino_vermelho, GPIO_OUT);
    configurar_pino(pino_verde, GPIO_OUT);
    configurar_pino(pino_azul, GPIO_OUT);

    gpio_set_function(pino_Buzzer, GPIO_FUNC_PWM);
    int slice_num = pwm_gpio_to_slice_num(pino_Buzzer);

    uint32_t freq_sistema = clock_get_hz(clk_sys); // Frequência do sistema
    uint16_t wrap_valor = freq_sistema / FREQUENCIA_BUZZER - 1; // Define o valor de wrap
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
