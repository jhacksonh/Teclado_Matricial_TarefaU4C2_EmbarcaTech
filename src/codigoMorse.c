#include "leds.h"
#include "codigoMorse.h"
#include <pico/stdlib.h>
#define COD_LED_VERMELHO 13
#define COD_LED_AZUL 12
#define COD_LED_VERDE 11

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
    controlar_leds(COD_LED_VERMELHO, false, COD_LED_VERDE, false, COD_LED_AZUL, false);

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

    controlar_leds(COD_LED_VERMELHO, false, COD_LED_VERDE, false, COD_LED_AZUL, false);
}

void ponto() {
    controlar_leds(COD_LED_VERMELHO, true, COD_LED_VERDE, false, COD_LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(COD_LED_VERMELHO, false, COD_LED_VERDE, false, COD_LED_AZUL, false);
    sleep_ms(300);
}

void traco() {
    controlar_leds(COD_LED_VERMELHO, false, COD_LED_VERDE, true, COD_LED_AZUL, false);
    sleep_ms(500);
    controlar_leds(COD_LED_VERMELHO, false, COD_LED_VERDE, false, COD_LED_AZUL, false);
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