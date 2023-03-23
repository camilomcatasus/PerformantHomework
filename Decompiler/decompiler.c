#include <stdio.h>
#include <string.h>
#include <stdint.h>
char registerTable[16][3] = {
    "al", "ax", "cl", "cx", "dl", "dx", "bl", "bx", "ah", "sp", "ch", "bp", "dh", "si", "bh", "di"
};

char effectiveAddressTable[8][8] = {
    "bx + si",
    "bx + di",
    "bp + si",
    "bp + di",
    "si",
    "di",
    "bp",
    "bx"
};

const char MOV_IMMEDIATE_TO_R = 0b1011;
const char MOV_IMMEDIATE_TO_RM = 0b1100011;
const char MOV_REGISTER_TO_R = 0b100010;

short int GetDisp(char);
void MovImmediateToRegister(int);
void MovRegisterToRegister(int);
void MovImmediateToRegisterMemory(int);

void MovImmediateToRegister(int firstByte) {
    int secondByte = getchar();
    char wField = (firstByte >> 3) & 0b1;
    char regField = firstByte & 0b00000111;
    char regTableIndex = (regField << 1) + wField;

    short int immediate = 0x0000;
    immediate = (secondByte >> 7) * 0xFF00;
    immediate = immediate | secondByte;

    if(wField)
    {
        int thirdByte = getchar();
        immediate = immediate & 0x00FF;
        immediate = immediate ;
        immediate = immediate | (thirdByte << 8);
    }

    printf("mov %s, %i\n", registerTable[regTableIndex], immediate);
}

void MovRegisterToRegister(int firstByte) {
    int secondByte = getchar();
    char wField = firstByte & 0b1;
    char dField = (firstByte >> 1) & 0b1;
    char modField = (secondByte >> 6) & 0b11;
    char regMemBits = secondByte & 0b00000111;
    char regBits = (secondByte >> 3) & 0b00000111;

    char regMemTableIndex = (regMemBits << 1) + wField;
    char regTableIndex = (regBits << 1) + wField;

    if(modField == 0b11)
    {
        char source = regMemTableIndex * (1-dField) + regTableIndex * dField;
        char dest = regTableIndex * (1-dField) + regMemTableIndex * dField;
        printf("mov %s, %s\n", registerTable[source], registerTable[dest]);
        return;
    }

    short int disp = GetDisp(modField);
    if(disp == 0 && regMemBits == 110)
    {
        printf("mov %s, %i\n", registerTable[regBits], regMemBits);
        return;
    }

    if(disp == 0)
    {
        if(dField == 1)
            printf("mov %s, [%s]\n", registerTable[regTableIndex], effectiveAddressTable[regMemBits]);
        else
            printf("mov [%s], %s \n", effectiveAddressTable[regMemBits], registerTable[regTableIndex]);
        return;
    }

    char displacementStr[40]  = "";

    if(disp < 0)
        sprintf(displacementStr, "- %i", -disp);
    else
        sprintf(displacementStr, "+ %i", disp);

    if(dField == 1)
        printf("mov %s, [%s %s]\n", registerTable[regTableIndex], effectiveAddressTable[regMemBits], displacementStr);
    else
        printf("mov [%s %s], %s\n", effectiveAddressTable[regMemBits], displacementStr, registerTable[regTableIndex]);
}

void MovImmediateToRegisterMemory(int firstByte) {
    int secondByte = getchar();
    char wField = firstByte & 0b1;
    char modField = (secondByte >> 6) & 0b111;
    char regMemBits = secondByte & 0b111;

    short int disp = GetDisp(modField);
    //short int data = GetData();
}

short int GetDisp(char modField) {
    short int disp = 0x0000;
    if(modField == 0b10 || modField == 0b01)
    {
        int loByte = getchar();
        disp = (loByte >> 7) * 0xFF00;
        disp = disp | loByte;
    }
    if (modField == 0b10)
    {
        disp = disp & 0x00FF;
        int highByte = getchar();
        disp = disp | (highByte << 8);
    }
    return disp;
}

int main() {


    printf("bits 16\n\n");

    int firstByte;
    while((firstByte = getchar()) != EOF) {

        //char opcode = leftByte >> 2;
        if(firstByte >> 4 == MOV_IMMEDIATE_TO_R)
        {
            MovImmediateToRegister(firstByte);
        }
        else if(firstByte >> 1 == MOV_IMMEDIATE_TO_RM)
        {
            MovImmediateToRegisterMemory(firstByte);
        }
        else if(firstByte >> 2 == MOV_REGISTER_TO_R)
        {
            MovRegisterToRegister(firstByte);
        }
    }
    return 0;
}


