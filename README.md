# Desafio 3: Simulador MiniCPU - Fatorial

Este repositório contém a implementação de um simulador de CPU capaz de executar o ciclo de instrução **Fetch-Decode-Execute** (Busca, Decodificação e Execução). O projeto faz parte da atividade prática "Torneio de Processadores" da disciplina de Infraestrutura de Hardware.

## 👥 Equipe
* **Hailton Neto**
* **Hugo Tenorio Nogueira Gomes**
* **Mateus Diniz Lima Silva**

---

## 🎯 O Desafio: Fatorial
O objetivo específico do Grupo 3 foi implementar a lógica para calcular o **Fatorial de N=5**. Como a arquitetura MiniCPU não possui uma instrução nativa de multiplicação, o cálculo foi realizado através de **somas repetidas** e controle de fluxo com saltos condicionais.

* **Entrada:** Valor $N=5$ pré-carregado no endereço `0x10`.
* **Saída:** Resultado ($120$) gravado no endereço `0x20`.



---

## ⚙️ Arquitetura do Simulador
O simulador imita o comportamento de um processador real com os seguintes componentes:
* **Memória:** 256 posições (0x00 a 0xFF).
* **Registradores:** R0, R1, R2 e R3 (8-bit).
* **PC (Program Counter):** Aponta para a próxima instrução.
* **ZF (Zero Flag):** Ativada quando o resultado de um `CMP` é zero.

### Ciclo de Instrução (F-D-E):
1. **Fetch:** Busca 3 bytes da memória e incrementa o PC em 3.
2. **Decode:** Identifica o Opcode através de uma estrutura `switch/case` em C.
3. **Execute:** Realiza a operação aritmética ou de desvio (JMP/JNZ).

---

## 🚀 Como Executar
1. Certifique-se de ter um compilador C (como o GCC) instalado.
2. Compile o arquivo:
   ```bash
   gcc atividade.c -o output
   ```
3. Execute o simulador:
   ```bash
   ./output
   ```



---

## 📊 Trace de Execução
O programa exibe o estado detalhado da CPU a cada ciclo, permitindo acompanhar a evolução dos registradores e a tomada de decisão dos saltos (`JNZ`).

> **Nota Técnica:** O projeto utiliza um arquivo `.gitignore` para garantir que binários compilados (pasta `output/`) não sejam rastreados, mantendo a integridade do repositório.

---

**Dica:** Você pode copiar este texto e colar diretamente no seu arquivo `README.md` no VS Code. Depois, basta dar o `git add .`, `git commit -m "docs: atualiza README com membros e descrição"` e o `git push`. 

Deseja que eu te ajude com mais algum nome ou detalhe na descrição técnica?