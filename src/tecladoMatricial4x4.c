#include "pico/stdlib.h"
#include "tecladoMatricial4x4.h"


static const char mapa_teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
char detectar_tecla(int pinos_linhas_teclado[4], int pinos_colunas_teclado[4]){
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