/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File: Biblioteca para controle de display LCD 2x16 e 4x16   
 * Author: Hamilton Canoquela
 * Comments: 
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef lcd_hc_H
#define	lcd_hc_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ 4000000


#define RS_LCD PORTEbits.RE0
//#define RW_LCD PORTEbits.RE1
#define EN_LCD PORTEbits.RE2
#define DATA_LCD PORTD


void comand_LCD(unsigned char comand);
void position_LCD(unsigned char row, unsigned char column);
void wt_LCD(unsigned char character);
void wtf_LCD(unsigned char *character);


//Control LCD:
void comand_LCD(unsigned char comand)
{ 
    RS_LCD = 0;
    //RW_LCD = 0;
    
    DATA_LCD = comand;
    EN_LCD = 1; 
    __delay_ms(10);
    EN_LCD = 1; 
    __delay_ms(10);
}

//Position for first character LCD:
void position_LCD(unsigned char row, unsigned char column)
{
    unsigned char x = 0; 
    --column;
    switch (row)
    {
        case 1: x = 0x80 + column;
                break;
        case 2: x = 0xC0 + column;
                break;
        case 3: x = 0x90 + column;
                break;
        case 4: x = 0xD0 + column;
                break;
        default: break;
    }    
    if (x !=0) comand_LCD(x);
}

// Character writing on LCD:
void wt_LCD(unsigned char character)
{ 
    RS_LCD = 1;
    //RW_LCD = 0;
    
    EN_LCD = 0;
    __delay_ms(10);
    DATA_LCD = character;
    EN_LCD = 1; 
    __delay_ms(10);
    EN_LCD = 0; 
    __delay_ms(10);
}

// write a sentence on the LCD 
void wtf_LCD(unsigned char *character)
{ 
    while(*character != '\0')
    {
        wt_LCD(*character);
        ++character;
        __delay_ms(10);
    }
}


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* lcd_hc_H */

