#include"SKEAZ1284.h"

#define TDRE 1<<7
#define RDRF 1<<5

char buf1[100],c1;
unsigned int i1,j1;

void UART1_Init()
{
    //SIM_PINSEL1 |= SIM_PINSEL1_UART1PS_MASK; /* MASK(Rx = PTF2 and Tx = PTF3)*/
	  SIM_PINSEL1|= SIM_PINSEL1_UART1PS_SHIFT; /*SHIFT(Rx = PTC6 and Tx = PTC7)*/
	  SIM_SCGC |=  SIM_SCGC_UART1_MASK;		/* Enable bus clock in UART2*/
		UART1_BDH = 0;							/* One stop bit*/
		UART1_BDL = 128;						/* Baud rate at 9600*/
		UART1_C1  = 0;							/* No parity enable,8 bit format*/
		UART1_C2 |= UART_C2_TE_MASK;			/* Enable Transmitter*/
		UART1_C2 |= UART_C2_RE_MASK;			/* Enable Receiver*/
		UART1_C2 |= UART_C2_RIE_MASK;
}

char isEmpty_1()  // buffer is empty to write
{
   if(UART1_S1 & TDRE) //buffer is empty
			return 1;
		else
			return 0;
}

char isReady_1() // buffer is full to read
{
		if(UART1_S1 & RDRF) //buffer is full
			return 1;
		else
			return 0;
}

void Send_Char_1(char ch)
{
		while ((isEmpty_1()) == 0);
		UART1_D = ch;
}
	
char Receive_Char_1()
{
		while(!(isReady_1()) == 0);
		c1 = UART1_D;
		return c1;
}
			
unsigned int puts_1(char *str)
{
		i1=0;
		while( str[i1] != '\0')
			Send_Char_1(str[i1++]);
		return i1;
}
	
char *gets_1()
{
		j1=0;
		char c1;
		while((c1 = Receive_Char_1()) != '\n')
		{
			buf1[j1++] = c1;
    }
		buf1[j1] = '\0' ;
		return buf1;
}
	

void flushBuffer_1()
{
		for(i1=0; i1 < 100; i1++) 
		buf1[i1] = '\0' ;
}


