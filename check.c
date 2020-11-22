// /*
//  * File:   check.c
//  * Author: bandopadhyaya.arundhati.btech2018@sitpune.edu.in
//  *
//  * Created on 11/11/2020 2:07:11 PM UTC
//  * "Created in MPLAB Xpress"
//  */

// #include<pic18f4520.h>
// #include<xc.h>

// #pragma config PBADEN = OFF


 
// void main(){ 

//     TRISDbits.RD1 = 0; 
//     TRISBbits.RB3 = 1; 

//     while(1){ 

//         if (PORTBbits.RB3 == 1) 
//         LATD1 = 1; 
//         else
//         LATD1 = 0;

//     }     

// } 

#include<pic18f4520.h>

// Declaration of functiones used

void delay(unsigned int value);
void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void lcdinit(void);
void lcddisplay(int row, unsigned char *queue);
void LCDinterface();
void dinoLocation();
void changeQueue();
void buttonIntr(char lastChar);
void segmentdisp();

// Defining all the registers used

#define ldata PORTD
#define rs PORTEbits.RE2
#define en PORTEbits.RE1
#define button PORTBbits.RB4

unsigned int score = 0;            // Initializing the origional score
unsigned int life = 4;             // Initializing the total number of lives 

//unsigned char dino[8] = {
    
//    0x00,0x0A,0x15,0x1F,0x0E,0x04,0x04,0x00
    
//};

char sl[] = "Score:00  Life:3";       // String array to display score and life on the LCD

