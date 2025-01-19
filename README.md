# Simulação com Wokwi: Controle com Teclado Matricial 4x4

Este projeto utiliza o simulador de eletrônica [Wokwi](https://wokwi.com) para implementar o controle de componentes eletrônicos por meio de um teclado matricial 4x4, com o microcontrolador RP2040 presente na placa Raspberry Pi Pico W.

## Funcionalidades

- Controle de **03 LEDs RGB**.
- Acionamento de um **buzzer** para emissão de sinal sonoro.
- Integração com um **teclado matricial 4x4** para gerenciamento dos sinais.

## Componentes Simulados

1. **Teclado matricial 4x4**.
2. **03 LEDs RGB**.
3. **Buzzer**.
4. **Microcontrolador Raspberry Pi Pico W**.

## Dependências do Projeto

Este projeto requer os seguintes recursos e ferramentas:

1. **Ambiente de Desenvolvimento**:
   - **Visual Studio Code (VS Code)** configurado com:
     - Extensão do **Wokwi**.
     - Configuração do **Pico SDK**.

2. **Simulador Wokwi**: 
   - O [Wokwi](https://wokwi.com) deve ser integrado ao ambiente de desenvolvimento **VS Code** para realizar a simulação e execução dos códigos.

3. **Kit de Desenvolvimento Pico SDK**:
   - Configurado para compilar e carregar os códigos em C para a simulação do microcontrolador Raspberry Pi Pico W.

---

## Desenvolvedores 

- [Jhackson H.](https://github.com/jhacksonh)
- [Luiz Rosario](https://github.com/luizzrosario)
- [Mateus Cavalcanti](https://github.com/mateusjrcavalcanti)
- [Lucas Silva](https://github.com/silvaluccs)
- [Arilson Oliveira](https://github.com/ArilsonOliveira)
- [João Sacerdote](https://github.com/JoaogSacerdote)
- [Ísis Menezes](https://github.com/intermediatesystemis)

---

## Configuração de Hardware

### Pinos Definidos

- **LEDs RGB**:
  - Vermelho: GPIO 13
  - Azul: GPIO 12
  - Verde: GPIO 11
- **Buzzer**: GPIO 21
- **Teclado Matricial**:
  - Colunas: GPIOs 1, 2, 3, 4
  - Linhas: GPIOs 5, 6, 7, 8

---

## Estrutura do Código

### Bibliotecas Utilizadas

- `stdio.h`: Entrada e saída padrão para debug.
- `pico/stdlib.h`: Biblioteca padrão da Raspberry Pi Pico.
- `hardware/pwm.h`: Para controle de PWM (usado no buzzer).
- `hardware/clocks.h`: Para configuração do clock.
- Bibliotecas específicas:
  - `configGpios.h`: Configuração dos pinos GPIO.
  - `tecladoMatricial4x4.h`: Funções para o teclado matricial.
  - `leds.h`: Controle de LEDs.
  - `buzzer.h`: Controle do buzzer.
  - `botoes-1-2.h` e `botoes8-9.h`: Implementações relacionadas a teclas específicas.

---

## Principais Funções

### 1. `main()`: Controle Principal

- Inicializa periféricos e entra em um loop contínuo para monitorar o teclado.
- Ações baseadas nas teclas pressionadas:
  - **Tecla `0`**: Toca a música do Mario com animação de LEDs.
  - **Tecla `1`**: Toca as notas em duas ordens inversas e executa uma sequência aleatória nos LEDs.
  - **Tecla `2`**: Toca uma sequência aleatória de notas e executa uma sequência aleatória nos LEDs.
  - **Tecla `D`**: Representa a letra D em código Morse.
  - **Tecla `#`**: Toca a marcha imperial de Star Wars.
  - **Tecla `*`**:
    1. Liga LEDs em sequência.
    2. Emite som no buzzer por 2 segundos.
    3. Reinicia o dispositivo em modo de gravação via USB.
  - **Tecla `8`**: Executa uma rotina para representar mensagens em código Morse com os LEDs.
  - **Tecla `9`**: Toca a música "Jingle Bells".

---
