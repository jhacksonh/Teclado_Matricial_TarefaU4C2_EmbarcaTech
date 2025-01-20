# 🧠 Jogo de Memória com LEDs e Buzzer (Teclas A e B)

Este é um jogo de memória implementado onde o jogador deve memorizar e repetir uma sequência de LEDs acesos. A cada rodada, a sequência aumenta, e o jogador deve pressionar as teclas corretas para continuar. Se errar, o jogo termina e uma música de erro é tocada.

## 🔑 Funcionalidades

### 🎶 Música de Início
- **Função:** `musica_inicio(uint pino_buzzer)`
- Toca uma sequência de notas musicais no buzzer para indicar o início do jogo.
- **Notas:** C, D, E, F, G.

### ❌ Música de Erro
- **Função:** `musica_erro(uint pino_buzzer)`
- Toca uma sequência de notas no buzzer para indicar que o jogador errou a sequência.

### 💡 Controle de LEDs
- **Função:** `acender_led(int led, uint pino_buzzer)`
  - Acende o LED correspondente e toca uma nota no buzzer.
- **Função:** `apagar_led(int led)`
  - Apaga o LED correspondente.
- **Função:** `apagar_leds()`
  - Apaga todos os LEDs.

### 🎮 Função Principal do Jogo
- **Função:** `jogo_memoria(int pinos_linhas_teclado[4], int pinos_colunas_teclado[4], uint pinos_leds[NUM_LEDS], uint pino_buzzer)`
- Esta função controla o fluxo do jogo, incluindo:
  - Geração de uma sequência aleatória de LEDs.
  - Apresentação da sequência de LEDs ao jogador.
  - Verificação se o jogador consegue repetir a sequência corretamente.
  - Incremento da sequência a cada rodada.
  - Toca músicas de erro ou de vitória.

### 📝 Verificação da Sequência
- **Função:** `verificar_sequencia(int *sequencia, int tamanho, int pinos_linhas_teclado[4], int pinos_colunas_teclado[4])`
  - A função verifica se a sequência de teclas pressionadas pelo jogador está correta.

### 🔲 Teclado Matricial
- **Função:** `detectar_tecla(pinos_linhas_teclado, pinos_colunas_teclado)`
  - Detecta a tecla pressionada no teclado matricial.

## ⚙️ Como Funciona

1. O jogo começa tocando uma música de início.
2. Uma sequência aleatória de LEDs é gerada e exibida ao jogador.
3. O jogador deve repetir a sequência pressionando as teclas correspondentes.
4. Se o jogador errar, uma música de erro é tocada e o jogo termina.
5. Se o jogador acertar, a sequência aumenta e o jogo continua.
6. O jogo termina quando o jogador atingir o número máximo de rodadas ou errar a sequência.

---

Boa sorte, e que vença o melhor jogador! 🎮✨
