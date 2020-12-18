// All the libraries to be included

#include <pic18f4520.h>
#include <math.h>
#include<stdio.h>
#include <stdlib.h>
#include "check.c"                                      // External files of the project to be included

#pragma config OSC=HS                   // pragma config = directive, used to turn ON/OFF particular functionalities, OSC = oscillator
#pragma config PWRT=OFF                 // Power Up Timer Enable
#pragma config WDT=OFF                  // Watch Dog Timer
#pragma config DEBUG=OFF, LVP=OFF       // LVP = enabling Low Voltage     
#pragma config PBADEN=OFF               // Port B Analog to Digital Enable
  
unsigned char text[] = {"               x"};             // Array to display our dino
// text[15] = dino;

void LCDinterface(){                                     // User defined function to interface the LCD
    TRISD = 0x00;                       // Set port D as Output
    TRISE = 0x00;                       // Set port E as Output
    ADCON1=0x0F;                        // 0000 1111 : PCFG[0:3] = 1111 so AN0-AN12 take digital inputs
    lcdinit();
    lcddisplay(1,sl);

    
    while(1){
        lcddisplay(2,text);
        delay(10);
        changeQueue();

    }
        
}  

 
void lcdinit(void){                                       // User defined function to initialize the LCD
    lcdcmd(0x38);                                         // 2 lines, 5x7 matrix
    delay(1);
    lcdcmd(0x0E);                                         // Display ON, cursor blinking
    delay(1);
    lcdcmd(0x01);                                         // Clear display screen
    delay(1);
    lcdcmd(0x06);                                         // Increment cursor rightwards
    delay(1);
}

void lcdcmd(unsigned char value){                             // User defined function for passing commands
    ldata=value;
    rs=0;                                                     // To accept commands: Register Select = 0
    en=1;
    delay(1);
    en=0;
}

void lcddata(unsigned char value){                             // User defined function for passing Data
    ldata=value;
    rs=1;                                                      // To accept data: Register Select = 1
    en=1;
    delay(1);
    en=0;
}

void lcddisplay(int row, unsigned char *str){                   // User defined function to display the content of LCD
    int k;
    if (row==1)
    lcdcmd(0x80);                                               // Force cursor to beginning of 1st line
    else
    lcdcmd(0xC0);                                               // Force cursor to beginning of 2nd line
    for(k=0;k<16;k++){
        if(str[k] !=0)
        lcddata(str[k]);                                        // Print character by character till you encounter null ('/0')
        else
        break;
    }
}

void delay(unsigned int value){                               // User defined function to provide a delay
    int i,j;
    for(i=0; i<=value; i++)
        for(j=0;j<=200;j++);
}


void changeQueue(){                                         // User defined function to spawn the obstacles
    for (int i=13; i>=0; i--)
        text[i+1]=text[i];                                  // Shifts obstacle course one place to the right

    int x = rand()%10;                                     // Generates 0-9 randomly, if 0 = *obstacle*   else *space*
    
    if (x == 0)
        text[0] = 'o';
    else
        text[0] = ' ';
 
    text[15] = 'x';                                        // Dino position fixed at 15 of 2nd line
    buttonIntr(text[14]);                                  // Checks if obstacle present at position 14 and sets score/life accordingly
    delay(10);

    
}



void buttonIntr(char lastObs){                                 // User defined function to check for button press when obstacle encountered 
    
    if (button == 0){                                          // If the user presses the button, button = 0
        text[15] = ' ';                                        // Dino dissappears
        if (lastObs == 'o'){                                    // If button pressed when obstacle encountered, score increases
        score = score+1;                                       
        sl[7] = (char)(score%10)+'0';                           // Converts integer to ASCII of required number. ASCII of '0' = 48
        sl[6] = (char)(score/10)+'0';
        lcddisplay(1,sl);                                       // Score and life displayed on row 1
        }
        
    }
    else{                                                     // If the user bumps into the obstacle
        if (lastObs == 'o'){
           life--;                                            // The life decreases
            sl[15] = (char)life+'0';

          lcddisplay(1,sl);
           if (life==0){                                     // When all the lives are lost
            lcddisplay(1,"Game Over");                       // LCD displays "Game Over"
            
            while(1);                                         // If Game Over, indefinite loop runs to show 'Game Over' on LCD, cannot play until Hex is reloaded
           }
        }
        
    }

}

