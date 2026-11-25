# SISTEMA-DE-CALCULADORA-DE-MATRIZES

## 1. Objetivo do Sistema
Desenvolver uma ferramenta computacional robusta e interativa em linguagem C para o cadastro e a execução de operações matemáticas sequenciais entre duas ou mais matrizes. O projeto implementa rigorosamente a modularização de código, validações de dimensões e restrições matemáticas (como verificação de matrizes singulares).

## 2. Funcionalidades
- **Cadastro Dinâmico:** Permite definir a quantidade de matrizes (mínimo de 2), suas dimensões (linhas e colunas) e o preenchimento individual de cada elemento.
- **Menu Interativo:** Opções para exibir matrizes cadastradas, realizar cálculos e encerrar o programa a qualquer momento.
- **Operações Matemáticas Sequenciais:**
  - Adição ($A + B + C \dots$)
  - Subtração ($A - B - C \dots$)
  - Multiplicação ($A \times B \times C \dots$)
  - Divisão Matricial ($A \times B^{-1} \times C^{-1} \dots$)
- **Validação de Erros:** Identifica e avisa o usuário caso dimensões sejam incompatíveis ou caso ocorra tentativa de divisão por matriz não quadrada ou singular (sem inversa).

## 3. Funções Implementadas
O código é totalmente modularizado por meio de funções específicas:
- `criarMatriz()`: Realiza a leitura das dimensões e dos valores informados pelo usuário.
- `exibirMatriz()`: Imprime a matriz formatada em linhas e colunas.
- `validarSomaSub()`: Verifica se as dimensões são iguais para adição e subtração.
- `validarMultiplicacao()`: Verifica se o número de colunas da primeira matriz equivale ao número de linhas da segunda.
- `somarMatrizes()`: Executa a operação de adição.
- `subtracarMatrizes()`: Executa a operação de subtração.
- `multiplicarMatrizes()`: Executa a operação de multiplicação tradicional.
- `calcularInversa()`: Calcula a matriz inversa utilizando o método de Gauss-Jordan com pivoteamento parcial.
- `dividirMatrizes()`: Gerencia a divisão matricial baseada no produto pela matriz inversa ($A \times B^{-1}$).
- `main()`: Coordena o fluxo geral de execução, alocação de memória e o menu interativo.

## 4. Procedimentos de Compilação e Execução
Certifique-se de ter um compilador C (como o GCC) instalado em sua máquina.

### No Linux / macOS / WSL:
1. Abra o terminal na pasta do projeto.
2. Compile o programa usando a flag `-lm` para incluir a biblioteca matemática:
   ```bash
   gcc main.c -o main -lm
