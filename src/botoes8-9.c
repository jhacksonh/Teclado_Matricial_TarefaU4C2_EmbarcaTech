#include "leds.h"
#include "botoes8-9.h"
#include <pico/stdlib.h>
#include "buzzer.h"

#define LOCAL_LED_VERMELHO 13
#define LOCAL_LED_AZUL 12
#define LOCAL_LED_VERDE 11
#define LOCAL_BUZZER_PINO 21

static void letra_E();
static void letra_M();
static void letra_B();
static void letra_A();
static void letra_R();
static void letra_C();
static void letra_A();
static void letra_D();
static void letra_O();


/* 
função: codigoMorse

E -> um ponto 
M -> dois traços
B -> um traço, três pontos
A -> um ponto, um traço
R -> um ponto, um traço, um ponto
C -> um traço, um ponto, um traço, um ponto
A -> um ponto, um traço
D -> um traço, dois pontos
O -> três traços 


um ponto -> led vermelho aceso por 500 ms
um traço -> led verde aceso por 500 ms 
tempo entre pontos e traços -> leds apagados por 300 ms 
tempo entre letras -> leds apagados por 600 ms

*/
void codigoMorse() {
    controlar_leds(LOCAL_LED_VERMELHO, false, LOCAL_LED_VERDE, false, LOCAL_LED_AZUL, false);

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

    controlar_leds(LOCAL_LED_VERMELHO, false, LOCAL_LED_VERDE, false, LOCAL_LED_AZUL, false);
}

void tocar_musica_jingle_bells() {
    int frequencias[] = {330, 330, 330, 330, 330, 330, 330, 392, 261, 294, 330, 349, 349, 349, 349, 349, 330, 330, 330, 330, 294, 294, 330, 294, 392};
    int duracoes[] = {200, 200, 400, 200, 200, 400, 200, 200, 200, 200, 600, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 400, 400};

    
    controlar_buzzer(LOCAL_BUZZER_PINO, true);

    tocar(LOCAL_BUZZER_PINO, frequencias, duracoes, sizeof(frequencias) / sizeof(int));
}

void ponto() {
    controlar_leds(LOCAL_LED_VERMELHO, true, LOCAL_LED_VERDE, false, LOCAL_LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(LOCAL_LED_VERMELHO, false, LOCAL_LED_VERDE, false, LOCAL_LED_AZUL, false);
    sleep_ms(300);
}

void traco() {
    controlar_leds(LOCAL_LED_VERMELHO, false, LOCAL_LED_VERDE, true, LOCAL_LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(LOCAL_LED_VERMELHO, false, LOCAL_LED_VERDE, false, LOCAL_LED_AZUL, false);
    sleep_ms(300);
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