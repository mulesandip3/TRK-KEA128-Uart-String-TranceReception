#include"SKEAZ1284.h"

#define TDRE 1<<7
#define RDRF 1<<5

char buf0[100],c0;
unsigned int i0,j0;



void UART0_Init()
{
		SIM_PINSEL0 |= SIM_PINSEL_UART0PS_MASK; /*Rx = PTA2 and TX = PTA3*/
	//SIM_PINSEL0 |= SIM_PINSEL_UART0PS_SHIFT; /*Rx = PTB0 and Tx = PTB1*/
		SIM_SCGC |=  SIM_SCGC_UART0_MASK;		/* Enable bus clock in UART2*/
		UART0_BDH = 0;							/* One stop bit*/
		UART0_BDL = 128;						/* Baud rate at 9600*/
		UART0_C1  = 0;							/* No parity enable,8 bit format*/
		UART0_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
		UART0_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
		UART0_C2 |= UART_C2_RIE_MASK;
}

char isEmpty_0()  // buffer is empty to write
{
   if(UART0_S1 & TDRE)
			return 1;
		else
			return 0;
}


char isReady_0() // buffer is full to read
{
		if(UART0_S1 & RDRF)
			return 1;
		else
			return 0;
}


void Send_Char_0(char ch)
{
		while((isEmpty_0()) == 0);
		UART0_D = ch;
}
	
char Receive_Char_0()
{	
		while((isReady_0()) == 0);
		c0 = UART0_D;
		return c0;
}
			
unsigned int puts_0(char *str)
{
		i0=0;
		while( str[i0] != '\0')
			Send_Char_0(str[i0++]);
		return i0;
}
	
char *gets_0()
{
		j0=0;
		char c0;
		while((c0 = Receive_Char_0()) != '\n')
		{
			buf0[j0++] = c0;
    }
		buf0[j0] = '\0' ;
		return buf0;
}
	
void flushBuffer_0()
{
		for(i0=0; i0 < 100; i0++) 
		buf0[i0] = '\0' ;
}


