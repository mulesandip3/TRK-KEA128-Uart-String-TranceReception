#include"SKEAZ1284.h"

#define TDRE 1<<7
#define RDRF 1<<5

char buf2[100],c2;
unsigned int i2,j2;

void UART2_Init()
{
	 //SIM_PINSEL1 |= SIM_PINSEL1_UART2PS_MASK; /* MASK(Rx = PTI0 and Tx = PTI1)*/
	 SIM_PINSEL1 |= SIM_PINSEL1_UART2PS_SHIFT; /*SHIFT(Rx = PTD6  and Tx = PTD7)*/
	 SIM_SCGC |=  SIM_SCGC_UART2_MASK;		/* Enable bus clock in UART2*/
	 UART2_BDH = 0;							/* One stop bit*/
	 UART2_BDL = 128;						/* Baud rate at 9600*/
	 UART2_C1  = 0;							/* No parity enable,8 bit format*/
	 UART2_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
	 UART2_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
	 UART2_C2 |= UART_C2_RIE_MASK;	
}

char isEmpty_2()  // buffer is empty to write
{
   if(UART2_S1 & TDRE)
			return 1;
		else
			return 0;
}


char isReady_2() // buffer is full to read
{
		if(UART2_S1 & RDRF)
			return 1;
		else
			return 0;
}


void Send_Char_2(char ch)
{
		while((isEmpty_2()) == 0);
		UART2_D = ch;
} 
	
char Receive_Char_2()
{
		
		while(!(isReady_2()));
		c2 = UART2_D;
		return c2;
}
			
unsigned int puts_2(char *str)
{
		i2=0;
		while( str[i2] != '\0')
			Send_Char_2(str[i2++]);
		return i2;
}
	
char * gets_2()
{
		j2=0;
		char c2;
		while((c2 = Receive_Char_2()) != '\n')
		{
			buf2[j2++] = c2;
    }
		buf2[j2] = '\0' ;
		return buf2;
}

void flushBuffer_2()
{
		for(i2=0; i2 < 100; i2++) 
		buf2[i2] = '\0' ;
}
