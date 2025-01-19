#include "botoes_a_b.h"

// Função para tocar uma sequência de notas
void tocar_musica(uint pino_buzzer, int* notas, int tamanho, int duracao) {
    for (int i = 0; i < tamanho; i++) {
        tocar_nota(pino_buzzer, notas[i], duracao);  // Toca a nota
        sleep_ms(duracao + 50);  // Pausa entre as notas
    }
}

// Música para o início do jogo (sequência de notas)
void musica_inicio(uint pino_buzzer) {
    int notas_inicio[] = { 262, 294, 330, 349, 392 };  // Notas (C, D, E, F, G)
    tocar_musica(pino_buzzer, notas_inicio, sizeof(notas_inicio) / sizeof(notas_inicio[0]), 300);
}

// Música para o erro do jogador
void musica_erro(uint pino_buzzer) {
    int notas_erro[] = { 220, 196, 174, 220 };  // Notas (A, G, F#, A)
    tocar_musica(pino_buzzer, notas_erro, sizeof(notas_erro) / sizeof(notas_erro[0]), 400);
}

void apagar_led(int led) {
    gpio_put(led, false);
}

void apagar_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        apagar_led(i);
    }
}

void acender_led(int led, uint pino_buzzer) {
    apagar_leds();
    gpio_put(led, true);
    tocar_nota(pino_buzzer, 400, 300);
    sleep_ms(500);
    apagar_leds();
    sleep_ms(500);
}

// Função para verificar a sequência inserida pelo jogador
bool verificar_sequencia(int *sequencia, int tamanho, int pinos_linhas_teclado[4], int pinos_colunas_teclado[4]) {
    for (int i = 0; i < tamanho; i++) {
        char tecla = 'n';

        // Continua aguardando até que uma tecla seja pressionada
        while (tecla == 'n') {
            tecla = detectar_tecla(pinos_linhas_teclado, pinos_colunas_teclado);
            sleep_ms(10);  // Evita sobrecarga de CPU
        }

        // Ajusta o valor da tecla pressionada para o índice correto
        int tecla_idx = tecla - '1';  // Mapeia as teclas '1', '2', '3' para os índices 0, 1, 2
 
        // Verifica se a tecla pressionada corresponde à sequência
        if (tecla_idx != sequencia[i]) {
            printf("Você pressionou a tecla errada. Esperado: %d, Pressionado: %d\n", sequencia[i], tecla_idx);
            return false;
        }
    }
    return true;
}

void jogo_memoria(int pinos_linhas_teclado[4], int pinos_colunas_teclado[4], uint pinos_leds[NUM_LEDS], uint pino_buzzer) {
    int max_rounds = 15;  // Número máximo de rodadas
    int sequencia[max_rounds];  // A sequência que o jogador precisa memorizar (máximo de 15 LEDs)
    int tamanho_sequencia = 0;

    // Toca a música de início
    musica_inicio(pino_buzzer);

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Gera a sequência aleatória inicial
    for (int i = 0; i < 15; i++) {
        sequencia[i] = rand() % NUM_LEDS; // Gera um número aleatório entre 0 e NUM_LEDS-1
    }

    sleep_ms(1000);  // Pausa antes de começar a sequência

    while (true) {
        // Aumenta o tamanho da sequência para a rodada
        tamanho_sequencia++;

        // Acende os LEDs da sequência até o tamanho da rodada
        for (int i = 0; i < tamanho_sequencia; i++) {
            acender_led(pinos_leds[sequencia[i]], pino_buzzer);  // Passando pino do buzzer
            sleep_ms(500);  // Acende cada LED por 500ms
            apagar_led(pinos_leds[sequencia[i]]);
            sleep_ms(250);  // Pausa entre LEDs
        }

        // Agora o jogador precisa inserir a sequência
        printf("Memorize a sequência e digite-a\n");

        // Verifica se o jogador digitou a sequência corretamente
        bool sucesso = verificar_sequencia(sequencia, tamanho_sequencia, pinos_linhas_teclado, pinos_colunas_teclado);

        if (!sucesso) {
            printf("Você errou! Fim de jogo.\n");
            // Toca a música de erro
            musica_erro(pino_buzzer);
            break;  // Termina o jogo
        }

        // Se o jogador acertou, continua para a próxima rodada
        printf("Acertou! Próxima rodada...\n");
        sleep_ms(1000);  // Pausa antes de iniciar a próxima rodada

        // Se o jogador atingiu o número máximo de rodadas, ele venceu
        if (tamanho_sequencia == max_rounds) {
            printf("Parabéns! Você venceu!\n");
            break;  // Termina o jogo
        }
    }
}
