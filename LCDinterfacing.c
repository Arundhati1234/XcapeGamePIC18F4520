#include <pic18f4520.h>
#include <math.h>
#include "check.c"
#pragma config OSC=HS
#pragma config PWRT=OFF
#pragma config WDT=OFF
#pragma config DEBUG=OFF, LVP=OFF 
#pragma config PBADEN=OFF


void LCDinterface(){
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1=0x0F;
    lcdinit();
    // lcddisplay(1,text1);
    TRISBbits.RB3 = 1;
    
      //first location for stickman; rest locations for spawn
    while(1){
        delay(1000);
        
        lcddisplay(2,queue);
        changeQueue();
        delay(1000); 
        
        
        if (queue[0]==1){
            if (PORTBbits.RB3){
             // bouncyJump();
            score++;
            }
        }  
    }
}
    


void lcdinit(void){
    lcdcmd(0x38);
    delay(1);
    lcdcmd(0x0E);
    delay(1);
    lcdcmd(0x01);
    delay(1);
    lcdcmd(0x06);
    delay(1);
}

void lcdcmd(unsigned char value){
    ldata=value;
    rs=0;
    en=1;
    delay(1);
    en=0;
}

void lcddata(unsigned int value){
    ldata=value;
    rs=1;
    en=1;
    delay(1);
    en=0;
}

void lcddisplay(int row, unsigned int *queue){
    int k;
    if (row==1)
    lcdcmd(0x80);
    else
    lcdcmd(0xC0);
    for(k=0;k<15;k++){
        //if(queue[k] !=0)
        lcddata(queue[k]);
        // else
        // break;
    }
}

void delay(unsigned int value){
    int i,j;
    for(i=0;i<=value;i++)
        for(j=0;j<=50;j++);
}


void changeQueue(){
    for (int i=0;i<14;i++)
        queue[i]=queue[i+1];    

    queue[14] = rand()%2; // generates 0 or 1 randomly
 
    delay(10);
    
    
    
}






