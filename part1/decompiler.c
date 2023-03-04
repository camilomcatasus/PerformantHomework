#include <stdio.h>
#include <string.h>
char registerTable[16][3] = {
    "al", "ax", "cl", "cx", "dl", "dx", "bl", "bx", "ah", "sp", "ch", "bp", "dh", "si", "bh", "di"
};

char opcodeTable[64][4] = {
    "err", // OpCode #:0 - 0b0
    "err", // OpCode #:1 - 0b1
    "err", // OpCode #:2 - 0b10
    "err", // OpCode #:3 - 0b11
    "err", // OpCode #:4 - 0b100
    "err", // OpCode #:5 - 0b101
    "err", // OpCode #:6 - 0b110
    "err", // OpCode #:7 - 0b111
    "err", // OpCode #:8 - 0b1000
    "err", // OpCode #:9 - 0b1001
    "err", // OpCode #:10 - 0b1010
    "err", // OpCode #:11 - 0b1011
    "err", // OpCode #:12 - 0b1100
    "err", // OpCode #:13 - 0b1101
    "err", // OpCode #:14 - 0b1110
    "err", // OpCode #:15 - 0b1111
    "err", // OpCode #:16 - 0b10000
    "err", // OpCode #:17 - 0b10001
    "err", // OpCode #:18 - 0b10010
    "err", // OpCode #:19 - 0b10011
    "err", // OpCode #:20 - 0b10100
    "err", // OpCode #:21 - 0b10101
    "err", // OpCode #:22 - 0b10110
    "err", // OpCode #:23 - 0b10111
    "err", // OpCode #:24 - 0b11000
    "err", // OpCode #:25 - 0b11001
    "err", // OpCode #:26 - 0b11010
    "err", // OpCode #:27 - 0b11011
    "err", // OpCode #:28 - 0b11100
    "err", // OpCode #:29 - 0b11101
    "err", // OpCode #:30 - 0b11110
    "err", // OpCode #:31 - 0b11111
    "err", // OpCode #:32 - 0b100000
    "err", // OpCode #:33 - 0b100001
    "mov", // OpCode #:34 - 0b100010
    "err", // OpCode #:35 - 0b100011
    "err", // OpCode #:36 - 0b100100
    "err", // OpCode #:37 - 0b100101
    "err", // OpCode #:38 - 0b100110
    "err", // OpCode #:39 - 0b100111
    "err", // OpCode #:40 - 0b101000
    "err", // OpCode #:41 - 0b101001
    "err", // OpCode #:42 - 0b101010
    "err", // OpCode #:43 - 0b101011
    "err", // OpCode #:44 - 0b101100
    "err", // OpCode #:45 - 0b101101
    "err", // OpCode #:46 - 0b101110
    "err", // OpCode #:47 - 0b101111
    "err", // OpCode #:48 - 0b110000
    "err", // OpCode #:49 - 0b110001
    "err", // OpCode #:50 - 0b110010
    "err", // OpCode #:51 - 0b110011
    "err", // OpCode #:52 - 0b110100
    "err", // OpCode #:53 - 0b110101
    "err", // OpCode #:54 - 0b110110
    "err", // OpCode #:55 - 0b110111
    "err", // OpCode #:56 - 0b111000
    "err", // OpCode #:57 - 0b111001
    "err", // OpCode #:58 - 0b111010
    "err", // OpCode #:59 - 0b111011
    "err", // OpCode #:60 - 0b111100
    "err", // OpCode #:61 - 0b111101
    "err", // OpCode #:62 - 0b111110
    "err", // OpCode #:63 - 0b111111
};

int main() {


    printf("bits 16\n\n");

    int leftByte;
    int rightByte;
    while((leftByte = getchar()) != EOF) {
        rightByte = getchar();

        char opcode = leftByte >> 2;
        char wField = leftByte & 0b1;
        char fromRegisterBits = ((rightByte & 0b00000111) << 1) + wField;
        char firstRegisterBits = ((rightByte >> 2) & 0b00001110)  + wField;
        printf("%s %s, %s\n", opcodeTable[opcode], registerTable[fromRegisterBits], registerTable[firstRegisterBits]);
    }
    return 0;
}


