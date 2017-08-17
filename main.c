/* 
 * File:   main.c
 * Author: takumi
 *
 * Created on 2016/12/28, 7:09
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 32000000

// PIC16F1939 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

// 0x10,0x50,0x7f,0x55,0x35,0x51,0x50 },/* 0x00 ? */
// 0x75,0x00,0x4e,0x3a,0x37,0x3a,0x46 },/* 0x01 ? */


int checkgit = 460;

char map[18][18];

void show(char, char);
void setup();
void mapcopy(char, char);
//void trans(char);
void makefig(char, char, char, char);
void posh(char, char, int, char);

/*
 * 
 */
int main(int argc, char** argv) {
    setup();
    for (char i = 0; i < 18; i++) {
        for (char j = 0; j < 18; j++) {
            map[i][j] = 0;
        }
    }

    int figure = 0;

    int count = 0;

    while (1) {
        show(0, 0);
        posh(1,1,460,1);
    }
    return (EXIT_SUCCESS);
}

void setup() {
    OSCCON = 0b01110000;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
}

void show(char num1, char num2) {
    LATD = 0x00;
    LATA = 0x00;
    LATE2 = 0;
    LATE1 = 1;
    LATE1 = 0;
    mapcopy(num1, num2);
    __delay_us(100);
    LATE2 = 1;
    for (char i = 1; i < 16; i++) {
        LATD = 0x00;
        LATA = 0x00;
        LATE1 = 1;
        LATE1 = 0;
        mapcopy(num1, num2 + i);
        __delay_us(100);
    }
}

void mapcopy(char num1, char num2) {
    char datatempa = 0;
    char datatemp = 0;
    datatemp = map[num1 + 7][num2];
    datatempa = map[num1 + 15][num2];
    for (char i = 7; i > 0; i--) {
        datatemp = datatemp * 2 + map[num1 + i - 1][num2];
        datatempa = datatempa * 2 + map[num1 + i + 7][num2];
    }

    LATD = datatemp;
    LATA = datatempa;
}

void posh(char num1, char num2, int point, char mode) {
    if (point > 99)makefig(num1, num2, point / 100, mode);
    if (point > 9)makefig(num1, num2 + 4, (point % 100) / 10, mode);
    makefig(num1, num2 + 8, point % 10, mode);
}

void makefig(char num1, char num2, char figure, char mode) {
    switch (figure) {
        case 1:
            map[num1][num2 + 1] = mode;
            map[num1 + 1][num2 + 1] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 3][num2 + 1] = mode;
            map[num1 + 4][num2 + 1] = mode;
            break;
        case 2:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 3][num2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 3:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2 + 2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 ] = mode;
            break;
        case 4:
            map[num1][num2] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 5:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 6:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 3][num2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 7:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 8:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 3][num2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 9:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 0:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 3][num2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
    }
}

/*
void trans(char num) {
    char datatempa = 0;
    char datatemp = 0;
    datatemp = data_moment[7][num];
    datatempa = data3[7][num];
    for (char i = 7; i > 0; i--) {
        datatemp = datatemp * 2 + data_moment[i - 1][num];
        datatempa = datatempa * 2 + data3[i - 1][num];
    }

    LATD = datatemp;
    LATA = datatempa;
}
 */

/*char data2_neru[8][16] = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char data3[8][16] = {
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/*char data_neru[8][16] = {
    {0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char data_moment[8][16] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};*/