// All the libraries to be included

#include <pic18f4520.h>
#include <math.h>
#include<stdio.h>
#include <stdlib.h>
#include "check.c"                                      // External files of the project to be included

#pragma config OSC=HS
#pragma config PWRT=OFF
#pragma config WDT=OFF
#pragma config DEBUG=OFF, LVP=OFF 
#pragma config PBADEN=OFF
  
unsigned char text[] = {"               x"};             // Array to display our dino
// text[15] = dino;

void LCDinterface(){                                     // User defined fucntion to interface the LCD
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1=0x0F;
    lcdinit();
    lcddisplay(1,sl);

    
    while(1){
        lcddisplay(2,text);
        delay(10);
        changeQueue();

    }
        
}  

 
void lcdinit(void){                                       // User defined fucntion to initialize the LCD
    lcdcmd(0x38);
    delay(1);
    lcdcmd(0x0E);
    delay(1);
    lcdcmd(0x01);
    delay(1);
    lcdcmd(0x06);
    delay(1);
}

void lcdcmd(unsigned char value){                             // User defined fucntion for passing commands
    ldata=value;
    rs=0;
    en=1;
    delay(1);
    en=0;
}

void lcddata(unsigned char value){                             // User defined fucntion for passing Data
    ldata=value;
    rs=1;
    en=1;
    delay(1);
    en=0;
}

void lcddisplay(int row, unsigned char *str){                   // User defined fucntion to display the content of LCD
    int k;
    if (row==1)
    lcdcmd(0x80);
    else
    lcdcmd(0xC0);
    for(k=0;k<16;k++){
        if(str[k] !=0)
        lcddata(str[k]);
        else
        break;
    }
}

void delay(unsigned int value){                               // User defined fucntion to provide a delay
    int i,j;
    for(i=0; i<=value; i++)
        for(j=0;j<=200;j++);
}


void changeQueue(){                                         // User defined fucntion that deals with the obstacles
    for (int i=13; i>=0; i--)
        text[i+1]=text[i];    

    int x = rand()%10;                                     // Generates 0-9 randomly to provide random obstacles
    
    if (x == 0)
        text[0] = 'o';
    else
        text[0] = ' ';
 
    text[15] = 'x';
    buttonIntr(text[14]);
    delay(10);

    
}



void buttonIntr(char lastObs){                                  // User defined fucntion to take the queue at (n-1) position, where n is the position of our dino
    
    if (button == 0){                                          // If the user presses the button to jump over the obstacle 
        text[15] = ' ';
        if (lastObs == 'o'){
        score = score+1;                                       // The score increases
        sl[7] = (char)(score%10)+'0';
        sl[6] = (char)(score/10)+'0';
        lcddisplay(1,sl);
        }
        
    }
    else{                                                     // If the user bumps into the obstacle
        if (lastObs == 'o'){
           life--;                                            // The life decreases
            sl[15] = (char)life+'0';

          lcddisplay(1,sl);
           if (life==0){                                     // When all the lives are lost
            lcddisplay(1,"Game Over");                       // LCD displays "Game Over"
            
            while(1);
           }
        }
        
    }

}

