#include<pic18f4520.h>


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

#define ldata PORTD
#define rs PORTEbits.RE2
#define en PORTEbits.RE1
#define button PORTBbits.RB4

unsigned int score = 0;
int life = 4;

// unsigned char dino[8] = {
    
//     0b00000,0b01010,0b10101,0b11111,0b01110,0b00100,0b00000,0b00000
    
    
// };
















