#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "buzzer.h"

void controlar_buzzer(uint pino_Buzzer, bool ativar)
{
    pwm_set_enabled(pwm_gpio_to_slice_num(pino_Buzzer), ativar);
}
void tocar_nota(uint pino_Buzzer, int frequencia, int duracao)
{
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
}

void tocar(uint pino_Buzzer, int *notas, int *duracoes, int tamanho)
{
    // Toca cada nota usando a função tocar_nota
    for (int i = 0; i < tamanho; i++)
    {
        int frequencia = notas[i];
        int duracao = duracoes[i];

        // Chama a função tocar_nota para tocar a nota específica
        tocar_nota(pino_Buzzer, frequencia, duracao);

        sleep_ms(50); // Pequena pausa entre notas
    }
}