/*
    RTTY Transmission Library
    Date: 10-08-2010
    Author: Mark Jessop
    
    This library will transmit strings over RTTY modulation (Binary FSK), at a specified baud rate, carrier frequency and frequency shift, with 1 start bit and 2 stop bits.
*/

#include "avr_compiler.h"
#include "AD9835_Xmega.h"
#include "MOD_RTTY.h"

double RTTY_Delay_Time = 109; // Delay between bit changes, in ms
uint8_t stop_bits = 1;

void RTTY_Setup(uint32_t base_freq, uint32_t shift_freq, uint16_t baud_rate,  uint8_t stops){
   uint32_t LOGICAL_0 = base_freq;
   uint32_t LOGICAL_1 = base_freq + shift_freq;
   RTTY_Delay_Time = (uint16_t)32768/baud_rate;
   stop_bits = stops;
   

   AD9835_Setup();
   AD9835_UseFSEL(0);
   AD9835_SelectFREG(0);
   AD9835_SetFreq(LOGICAL_0);
   AD9835_SelectFREG(1);
   AD9835_SetFreq(LOGICAL_1);
   AD9835_UseFSEL(1);
}

void RTTY_TXBit(int bit_val){
    AD9835_SelectFREG(bit_val);
    RTTY_Delay();
}

void RTTY_Delay(){
   while (!(RTC.INTFLAGS & RTC_OVFIF_bm));
   RTC.INTFLAGS = RTC_OVFIF_bm; 
}

void RTTY_TXByte(uint8_t data){
    uint8_t i = 0;
    
    // Send Start bit
    RTTY_TXBit(0);
    
    // Send byte bits, LSB first.
    for (i=0; i<8; i++){
        if( data & 1 ) RTTY_TXBit(1);
        else RTTY_TXBit(0);
        data = data >> 1;
    }
    
    // Send Stop bits
    for( i = 0; i < stop_bits; i++){
        RTTY_TXBit(1);
    }
}

void RTTY_TXString(char *string) {
    Setup32KHzRTC(109);//RTTY_Delay_Time);
    RTTY_Delay();

	for (int i = 0; i < strlen(string); i++) {
		RTTY_TXByte(string[i]);
	}
}




    
    