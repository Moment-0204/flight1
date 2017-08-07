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


int checkgit=46;

char data[8][16] = {
    {0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char data2[8][16] = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char map[18][18];

void setup();
void mapcopy(char, char);
void trans(char);
void makefig(char, char, char, char);

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


    int count = 0;
    makefig(0, 8, 2, 1);

    
    while(1){
        LATD = 0x00;
        LATA = 0x00;
        LATE2 = 0;
        LATE1 = 1;
        LATE1 = 0;
        trans(0);
        __delay_us(300);
        for(int i=0; i<15; i++){
            LATD = 0x00;
            LATA = 0x00;
            LATE1 = 1;
            LATE1 = 0;
            trans(i+1);
            __delay_us(300);
        }
    }
    
    while (1) {
        LATD = 0x00;
        LATA = 0x00;
        LATE2 = 0;
        LATE1 = 1;
        LATE1 = 0;
        mapcopy(1, 2);
        __delay_us(300);
        count++;
        if (count % 150 == 0) {
            makefig(count / 150 - 1, 8, 2, 0);
            makefig(count / 150, 8, 2, 1);
            if(count/150>17)count=0;
        }
        LATE2 = 1;
        for (char i = 0; i < 15; i++) {
            LATD = 0x00;
            LATA = 0x00;
            LATE1 = 1;
            LATE1 = 0;
            mapcopy(1, 2 + i);
            __delay_us(300);
        }
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

void trans(char num) {
    char datatempa = 0;
    char datatemp = 0;
    datatemp = data[7][num];
    datatempa = data2[7][num];
    for (char i = 7; i > 0; i--) {
        datatemp = datatemp * 2 + data[i - 1][num];
        datatempa = datatempa * 2 + data2[i - 1][num];
    }

    LATD = datatemp;
    LATA = datatempa;
}

void makefig(char num1, char num2, char figure, char mode) {
    if (mode == 1) {
        map[num1][num2] = 1;
        map[num1][num2 + 1] = 1;
        map[num1][num2 + 2] = 1;
        map[num1 + 1][num2 + 2] = 1;
        map[num1 + 2][num2 + 2] = 1;
        map[num1 + 2][num2 + 1] = 1;
        map[num1 + 2][num2] = 1;
        map[num1 + 3][num2] = 1;
        map[num1 + 4][num2] = 1;
        map[num1 + 4][num2 + 1] = 1;
        map[num1 + 4][num2 + 2] = 1;
    } else {
        map[num1][num2] = 0;
        map[num1][num2 + 1] = 0;
        map[num1][num2 + 2] = 0;
        map[num1 + 1][num2 + 2] = 0;
        map[num1 + 2][num2 + 2] = 0;
        map[num1 + 2][num2 + 1] = 0;
        map[num1 + 2][num2] = 0;
        map[num1 + 3][num2] = 0;
        map[num1 + 4][num2] = 0;
        map[num1 + 4][num2 + 1] = 0;
        map[num1 + 4][num2 + 2] = 0;
    }
}
