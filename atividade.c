#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0, zf = 0, running = 1;
int ciclo = 0;

void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc]; *a = mem[pc+1]; *b = mem[pc+2];
    pc += 3;
}

void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
        case 0x01: reg[a] = mem[b]; break;
        case 0x02: mem[b] = reg[a]; break;
        case 0x03: reg[a] = reg[a] + reg[b]; break;
        case 0x04: reg[a] = reg[a] - reg[b]; break;
        case 0x05: reg[a] = b; break;
        case 0x06: zf = (reg[a] == reg[b]) ? 1 : 0; break;
        case 0x07: pc = a; break;
        case 0x08: if (zf) pc = a; break;
        case 0x09: if (!zf) pc = a; break;
        case 0x0A: running = 0; break;
    }
}

void trace(uint8_t op, uint8_t a, uint8_t b) {
    const char *nomes[] = {"","LOAD","STORE","ADD","SUB","MOV",
                            "CMP","JMP","JZ","JNZ","HALT"};
    
    printf("Ciclo %d: %-5s %d,%d | R0=%3d R1=%3d"
            " R2=%3d R3=%3d | PC=%3d ZF=%d\n",
            ciclo, nomes[op], a, b,
            reg[0], reg[1], reg[2], reg[3], pc, zf);
}

void func_sub(void) {
    mem[0x10] = 5;    // N inicial 
    mem[0x11] = 1;    // Para subtrair/comparar

    mem[0x00] = 0x01; mem[0x01] = 0; mem[0x02] = 0x10; // LOAD R0, 0x10 (R0 = 5) 
    mem[0x03] = 0x05; mem[0x04] = 1; mem[0x05] = 1;    // MOV R1, 1    (Resultado começa em 1) 
    mem[0x06] = 0x05; mem[0x07] = 3; mem[0x08] = 1;    // MOV R3, 1    (R3 = constante 1) 

     mem[0x09] = 0x03; mem[0x0A] = 1; mem[0x0B] = 0;    // ADD R1, R0  (Exemplo: R1 += R0) 
    mem[0x0C] = 0x04; mem[0x0D] = 0; mem[0x0E] = 3;    // SUB R0, R3  (N = N - 1) 
    mem[0x0F] = 0x06; mem[0x10] = 0; mem[0x11] = 3;    // CMP R0, R3  (R0 == 1?) 
    mem[0x12] = 0x09; mem[0x13] = 0x09; mem[0x14] = 0; // JNZ 0x09     (Se não for 1, volta p/ 0x09) 

    mem[0x15] = 0x02; mem[0x16] = 1; mem[0x17] = 0x20; // STORE R1, 0x20 [cite: 35, 67]
    mem[0x18] = 0x0A; mem[0x19] = 0; mem[0x1A] = 0;    // HALT 
}

int main() {
    func_sub();
    
    while (running && pc < 256) {
        uint8_t op, a, b;
        ciclo++;
        fetch(&op, &a, &b);
        decode_execute(op, a, b);
        trace(op, a, b);
    }
    return 0;
}