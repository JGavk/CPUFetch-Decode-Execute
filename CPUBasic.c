#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMSIZE 512

int accumulator = 0;
int D1, D2, D3, D4, D5, D8;
int memorySize[1000];

int* getRegisterPointer(const char* reg);

void executeInstruction(const char *opcode, const char *reg, int value) {
  

    if (strcmp(opcode, "SET") == 0) {
        int* reg_ptr = getRegisterPointer(reg);
        *reg_ptr = value;
    } else if (strcmp(opcode, "LDR") == 0) {
        if (strcmp(reg, "ACC") == 0) {
            accumulator = value; 
        } else {
    
            int* reg_ptr = getRegisterPointer(reg);
            accumulator = *reg_ptr;
        }
    }else if (strcmp(opcode, "ADD") == 0) {
    int* reg_ptr = getRegisterPointer(reg);

    // Añade el valor al acuulador
    if (reg_ptr != NULL) {
        accumulator += *reg_ptr;

        // Si no se registra en ACC lo actualiza
        if (strcmp(reg, "ACC") != 0) {
            *reg_ptr = accumulator;
        }
    } else {
        // Si el registro no esta especificado lo añade al acumulador
        accumulator += value;
    }
    } else if (strcmp(opcode, "STR") == 0) {
        // Guarda el acumulador en la memoria
        if (strcmp(reg, "ACC") == 0) {
            // Guarda el registro en el acumulador
            accumulator = value;
        } else {
            
            int* reg_ptr = getRegisterPointer(reg);
            *reg_ptr = accumulator;
        }
    } else if (strcmp(opcode, "SHW") == 0) {
        // Muestra los diferentes
        if (strcmp(reg, "ACC") == 0) {
            printf("Output: %d\n", accumulator);
        } else {
            // Muestra
            int* reg_ptr = getRegisterPointer(reg);
            printf("Output: %d\n", *reg_ptr);
        }
    } else if (strcmp(opcode, "END") == 0) {
        exit(0);
    }

}
//Funcion de ayuda de registros
int* getRegisterPointer(const char* reg) {
    if (strcmp(reg, "D2") == 0) return &D2;
    else if (strcmp(reg, "D3") == 0) return &D3;
    else if (strcmp(reg, "D5") == 0) return &D5;
    else if (strcmp(reg, "D8") == 0) return &D8;

    else return NULL;  
}

int main() {
    FILE *pArch;
    pArch = fopen("sample1.txt", "r");

    if (pArch == NULL) {
        perror("Error opening file");
        return 1; 
    }

    char line[100]; 

    while (fgets(line, sizeof(line), pArch) != NULL) {
        char opcode[5];
        char reg[4];
        int value;

        if (sscanf(line, "%4s %3s %d", opcode, reg, &value) == 3) {
            printf("Read: %s %s %d\n", opcode, reg, value); 
            printf("Antes de ejecutar:\n Acumulador = %d, D2 = %d, D3 = %d, D5 = %d, D8 = %d\n",
                    accumulator, D2, D3, D5, D8);
            executeInstruction(opcode, reg, value);
            printf("Despues de ejecutar:\n Acumulador = %d, D2 = %d, D3 = %d, D5 = %d, D8 = %d\n",
                    accumulator, D2, D3, D5, D8);
        }
    }

    fclose(pArch); // Cierra al terminar

    return 0;
}