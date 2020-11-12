#include<pic18f4520.h>

void delay(unsigned int value);
void lcdcmd(unsigned char value);
void lcddata(unsigned int value);
void lcdinit(void);
void lcddisplay(int row,unsigned int *queue);
void LCDinterface();
void changeQueue();

#define ldata PORTD
#define rs PORTEbits.RE2
#define en PORTEbits.RE1
unsigned int score = 0;
unsigned int queue[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};



