# Simulação com Wokwi: Controle com Teclado Matricial 4x4

Este projeto utiliza o simulador de eletrônica [Wokwi](https://wokwi.com) para implementar o controle de componentes eletrônicos por meio de um teclado matricial 4x4, com o microcontrolador RP2040 presente na placa Raspberry Pi Pico W.

## Link do vídeo 
- [Vídeo - Projeto Controle com Teclado Matricial 4x4](https://drive.google.com/file/d/1Hh7Bxug_ILJYOFYea_TvD5Ftc8_VZweT/view?usp=drive_link)

## Funcionalidades

- Controle de **03 LEDs RGB**.
- Acionamento de um **buzzer** para emissão de sinal sonoro.
- Integração com um **teclado matricial 4x4** para gerenciamento dos sinais.

## Componentes Simulados

1. **Teclado matricial 4x4**.
2. **03 LEDs RGB**.
3. **Buzzer**.
4. **Placa Raspberry Pi Pico W**.

## Dependências do Projeto

Este projeto requer os seguintes recursos e ferramentas:

1. **Ambiente de Desenvolvimento**:
   - **Visual Studio Code (VS Code)** configurado com:
     - Extensão do **Wokwi**.
     - Configuração do **Pico SDK**.

2. **Simulador Wokwi**: 
   - O [Wokwi](https://wokwi.com) deve ser integrado ao ambiente de desenvolvimento **VS Code** para realizar a simulação e execução dos códigos.

3. **Kit de Desenvolvimento Pico SDK**:
   - Configurado para compilar e carregar os códigos em C para a simulação da placa Raspberry Pi Pico W.

---

## Desenvolvedores 

- [Jacson Santos](https://github.com/jhacksonh)
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

## Estrutura do Projeto 

```plaintext
├── docs
│   ├──doc_teclas_A_B.md
│   ├──TAREFA 1 -  AS_U4C2O1234A_14_01_2025 - V1.pdf
│   ├──TAREFA 2 -  AS_U4C2O1234A_14_01_2025 - V1.pdf
├── includes                
│   ├── botoes_a_b.h        
│   ├── botoes-1-2.h        
│   ├── botoes-3-6.h        
│   ├── botoes8-9.h         
│   ├── buzzer.h            
│   ├── configGpios.h       
│   ├── leds.h              
│   └── tecladoMatricial4x4.h 
├── src                     
│   ├── botoes_a_b.c        
│   ├── botoes-1-2.c        
│   ├── botoes-3-6.c        
│   ├── botoes8-9.c         
│   ├── buzzer.c            
│   ├── configGpios.c       
│   ├── leds.c              
│   └── tecladoMatricial4x4.c 
├── .gitignore              
├── CMakeLists.txt          
├── diagram.json            
├── pico_sdk_import.cmake   
├── README.md         
└── wokwi.toml              
```

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
  - `botoes-1-2.h`, `botoes8-9.h`, `botoes_a_b.h` e `botoes-3-6.h`: Implementações relacionadas a teclas específicas.

---

## Principais Funções

### 1. `main()`: Controle Principal

- Inicializa periféricos e entra em um loop contínuo para monitorar o teclado.
- Ações baseadas nas teclas pressionadas:
  - **Tecla `0`**: Toca a música do Mario com animação de LEDs.
  - **Tecla `1`**: Toca as notas em duas ordens inversas e executa uma sequência aleatória nos LEDs.
  - **Tecla `2`**: Toca uma sequência aleatória de notas e executa uma sequência aleatória nos LEDs.
  - **Tecla `3`**: 
  - **Tecla `4`**: Pisca o Led vermelho, azul e verde quatro vezes. 
  - **Tecla `5`**: Toca as notas da música Fur Elise de Beethoven.
  - **Tecla `6`**:
  - **Tecla `7`**: Toca uma sequência de notas e aciona os LED's em simultêneo.     
  - **Tecla `8`**: Executa uma rotina para representar mensagens em código Morse com os LEDs.
  - **Tecla `9`**: Toca a música "Jingle Bells".
   - **Tecla `A`**: Contém um [jogo de memória](https://github.com/jhacksonh/Teclado_Matricial_TarefaU4C2_EmbarcaTech/blob/main/TECLAS_A_B.md).
  - **Tecla `B`**: Contém um [jogo de memória](https://github.com/jhacksonh/Teclado_Matricial_TarefaU4C2_EmbarcaTech/blob/main/TECLAS_A_B.md).
  - **Tecla `C`**: Representa a letra C em código morse.
  - **Tecla `D`**: Representa a letra D em código Morse.
  - **Tecla `#`**: Toca a marcha imperial de Star Wars.
  - **Tecla `*`**:
    1. Liga LEDs em sequência.
    2. Emite som no buzzer por 2 segundos.
    3. Reinicia o dispositivo em modo de gravação via USB.

---

### 2. `controlar_leds()`: Controlar LEDs

Essa função tem como objetivo controlar os LEDs RGB (vermelho, verde e azul) conectados aos pinos específicos do microcontrolador. Ela permite acionar ou desligar cada cor de LED de forma independente, utilizando os pinos de controle definidos no código.

### 3. Funções para Controle do Buzzer

Este conjunto de funções permite controlar um buzzer conectado ao microcontrolador para tocar notas musicais utilizando PWM (Pulse Width Modulation). As funções permitem acionar o buzzer, controlar a frequência das notas e a duração das mesmas.

#### **1. Função: `controlar_buzzer()`**

Esta função ativa ou desativa o buzzer utilizando PWM.

#### **2. Função: `tocar_nota()`**

Essa função é responsável por gerar uma nota musical no buzzer, configurando sua frequência e duração, utilizando PWM (Pulse Width Modulation).

#### **3. Função: `tocar()`**

Essa função é responsável por tocar uma sequência de notas musicais em um buzzer, utilizando a função `tocar_nota` para gerar cada nota com base na frequência e na duração fornecidas.

### 4. `detectar_tecla()`: Controlar o teclado matricial

Essa função é responsável por detectar qual tecla foi pressionada em um teclado matricial 4x4. Ela percorre as linhas e colunas do teclado, verificando se uma tecla foi acionada, e retorna o caractere correspondente à tecla pressionada.

### 5. `inicializar_perifericos()`: Inicializar periféricos

Essa configura os periféricos utilizados no sistema, como LEDs (vermelho, verde e azul), o buzzer, e as linhas e colunas de um teclado matricial. Além disso, configura a frequência de operação do buzzer e as funcionalidades dos pinos associados.

