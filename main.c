/* 
 * File:   main.c
 * Author: takumi
 *
 * Created on 2016/12/28, 7:09
 */

#include <stdio.h>
#include <stdlib.h>
#include "skADXL345I2C.h"
#include "skI2Cmaster.h"
#include <math.h>
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


int Xangle, Yangle, Zangle;

void accele() {
    int x1, y1, z1, x2, y2, z2, x, y, z;

    x1 = 0;
    y1 = 0;
    z1 = 0;
    for (int lcoun = 0; lcoun < 10; lcoun++) {
        acceler_Read(&x, &y, &z);
        x1 += x;
        y1 += y;
        z1 += z;
    }
    x2 = x1 / 10;
    y2 = y1 / 10;
    z2 = z1 / 10;


    Xangle = (int) (atan2(x2 + 10, z2 - 4) / 3.14159 * 180.0); // X$BJ}8~(B
    Yangle = (int) (atan2(y2 - 5, z2 - 4) / 3.14159 * 180.0); // Y$BJ}8~(B
    Zangle = (int) (atan2(z2 - 4, y2 - 5) / 3.14159 * 180.0); // Y$BJ}8~(B
}

char map[27][27];

void show(char, char);
void setup();
//void mapcopy(char, char);
//void trans(char);
void makefig(char, char, char, char);
void posh(char, char, int, char);
char Map(char, char, char, char);
int mapcopy(char, char);

/*
 * 
 */

char di = 0, dj = 0;
int fx, fz;
int m;

void interrupt intertimer() {
    if (SSPIF == 1) {
        if (AckCheck == 1) AckCheck = 0;
        SSPIF = 0; // $B!)(Bt$B!)!)!)(BO$B!)(BN$B!)!)!)(BA
    } else if (BCLIF == 1) {
        BCLIF = 0;
    } else if (T0IF == 1) {
        m = (m + 1) % 5;
        if (m == 0) {
            char th = 40;
            if (Xangle > fx - th && di != 0)di--;
            else if (Xangle < fx + th && di != 38)di++;
            if (Zangle > fz - th && dj != 38)dj++;
            else if (Zangle < fz + th && dj != 0)dj--;
        }
        T0IF = 0;
    }
}

int main(int argc, char** argv) {
    setup();
    OPTION_REG = 0b00000111;
    TMR0 = 0;
    T0IF = 0;
    T0IE = 1;
    GIE = 1;
    InitI2C_Master2();
    acceler_Init();
    accele();

    fx = 0;
    fz = 0;

    for (char i = 0; i < 27; i++)for (char j = 0; j < 27; j++)map[i][j] = 0;
    for (char i = 0; i < 27; i++) {
        map[i][0] = 17;
        map[i][26] = 68;
        map[0][i] = 5;
        map[26][i] = 80;
    }
    map[0][0] = 21;
    map[26][26] = 84;
    map[0][26] = 69;
    map[26][0] = 85;

    int figure = 0;

    int count = 0;
    int preangle = 0;
    int prexangle = 0;


    makefig(7, 7, 8, 1);
    makefig(46, 46, 3, 1);

    while (1) {
        count = (count + 1) % 10;
        if (count == 0)accele();
        int wait = 1;
        show(di, dj);
    }
    return 1;
}

void setup() {
    OSCCON = 0b01110000;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0b00011000;
    TRISD = 0x00;
    TRISE = 0x00;
}

void show1(char num1, char num2) {
    LATD = 0x00;
    LATA = 0x00;
    LATE2 = 0;
    LATE1 = 1;
    LATE1 = 0;
    mapcopy(num1, num2);
    __delay_us(300);
    LATE2 = 1;
    for (char i = 1; i < 27; i++) {
        LATD = 0x00;
        LATA = 0x00;
        LATE1 = 1;
        LATE1 = 0;
        mapcopy(num1, num2 + i);
        __delay_us(300);
    }
}

void show(char num1, char num2) {
    int dataa;
    LATD = 0x00;
    LATA = 0x00;
    LATE2 = 0;
    LATE1 = 1;
    LATE1 = 0;
    dataa = mapcopy(num1, num2);
    LATA = dataa / 256;
    LATD = dataa % 256;
    __delay_us(50);
    LATE2 = 1;
    dataa = mapcopy(num1, num2 + 1);
    for (char i = 1; i < 16; i++) {
        LATD = 0x00;
        LATA = 0x00;
        LATE1 = 1;
        LATE1 = 0;
        LATA = dataa / 256;
        LATD = dataa % 256;
        if (i != 15)dataa = mapcopy(num1, num2 + i + 1);
        __delay_us(50);
    }
}

int mapcopy(char num1, char num2) {
    char datatempa = 0;
    char datatemp = 0;
    datatemp = Map(num1 + 7, num2, map[(num1 + 7) / 2 ][num2 / 2 ], 1);
    datatempa = Map(num1 + 15, num2, map[(num1 + 15) / 2 ][num2 / 2 ], 1);
    for (char i = 7; i > 0; i--) {
        datatemp = datatemp * 2 + Map(num1 + i - 1, num2, map[(num1 + i - 1) / 2][num2 / 2], 1);
        datatempa = datatempa * 2 + Map(num1 + i + 7, num2, map[(num1 + i + 7) / 2][num2 / 2], 1);
    }

    return datatempa *256 + datatemp;
}

void mapcopy1(char num1, char num2) {
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
    if (point < 0)point = point*-1 + 200;
    if (point > 99)makefig(num1, num2, point / 100, mode);
    if (point > 9)makefig(num1, num2 + 4, (point % 100) / 10, mode);
    makefig(num1, num2 + 8, point % 10, mode);
}

void makefig1(char num1, char num2, char figure, char mode) {
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
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
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
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2] = mode;
            map[num1 + 4][num2 + 1] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 4:
            map[num1][num2] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 1][num2 + 2] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
            map[num1 + 3][num2 + 2] = mode;
            map[num1 + 4][num2 + 2] = mode;
            break;
        case 5:
            map[num1][num2] = mode;
            map[num1][num2 + 1] = mode;
            map[num1][num2 + 2] = mode;
            map[num1 + 1][num2] = mode;
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
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
            map[num1 + 2][num2] = mode;
            map[num1 + 2][num2 + 1] = mode;
            map[num1 + 2][num2 + 2] = mode;
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
            map[num1 + 1][num2 + 2] = mode;
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

//*

//*

void makefig(char num1, char num2, char figure, char mode) {
    switch (figure) {
        case 1:
            Map(num1, num2 + 1, mode, 0);
            Map(num1 + 1, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 3, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            break;
        case 2:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 3:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 4:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 5:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 6:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 7:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 8:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 9:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 1, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
            break;
        case 0:
            Map(num1, num2, mode, 0);
            Map(num1, num2 + 1, mode, 0);
            Map(num1, num2 + 2, mode, 0);
            Map(num1 + 1, num2, mode, 0);
            Map(num1 + 1, num2 + 2, mode, 0);
            Map(num1 + 2, num2, mode, 0);
            Map(num1 + 2, num2 + 2, mode, 0);
            Map(num1 + 3, num2, mode, 0);
            Map(num1 + 3, num2 + 2, mode, 0);
            Map(num1 + 4, num2, mode, 0);
            Map(num1 + 4, num2 + 1, mode, 0);
            Map(num1 + 4, num2 + 2, mode, 0);
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

char Map(char num1, char num2, char num, char mode) {
    if (mode == 1) {
        char te = num;
        if (num1 % 2 == 1 && num2 % 2 == 1)return te >> 6;
        else if (num1 % 2 == 1 && num2 % 2 == 0)return (te % 64) >> 4;
        else if (num1 % 2 == 0 && num2 % 2 == 1)return (te % 16) >> 2;
        else if (num1 % 2 == 0 && num2 % 2 == 0)return te % 4;
    } else {
        if (num1 % 2 == 1 && num2 % 2 == 1)map[num1 / 2 + 1][num2 / 2 + 1] += num << 6;
        else if (num1 % 2 == 1 && num2 % 2 == 0)map[num1 / 2 + 1][num2 / 2 + 1] += num << 4;
        else if (num1 % 2 == 0 && num2 % 2 == 1)map[num1 / 2 + 1][num2 / 2 + 1] += num << 2;
        else if (num1 % 2 == 0 && num2 % 2 == 0)map[num1 / 2 + 1][num2 / 2 + 1] += num;
    }
}