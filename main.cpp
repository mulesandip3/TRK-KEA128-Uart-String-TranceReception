#include <SKEAZ1284.h>
#include "string.h"
#include "uart0.h"
#include "uart1.h"
#include "uart2.h"

void Clk_Init();
void delay(unsigned int itime);
char buffer[100];
int main()
{
	Clk_Init();
	UART0_Init();
	UART1_Init();
	UART2_Init();	
	while(1)
	{	
		
		if(isReady_1())
		{
			puts_0(gets_1());
		}
		else if(isReady_0())
		{
			puts_1(gets_0());
		}
		/*
					puts_0("ATZ");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
		      puts_1("Reset: ");
		      delay(1000);
		      if(isReady_0())
					{
		      strcpy(buffer , gets_0());
		      puts_1(buffer);
		      delay(100);
					}
					
					puts_0("ATE0");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
		      puts_1("Echo Off: ");
		      delay(1000);
		      puts_1(gets_0());
		      delay(100);
					
					puts_0("010C");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
					puts_1("RPM: ");
					delay(1000);
		      puts_1(gets_0());
		      delay(100);
					
					puts_0("010D");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
					puts_1("Speed: ");
					delay(1000);
		      puts_1(gets_0());
		      delay(100);
					
						puts_0("0105");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
					puts_1("ECT: ");
					delay(1000);
		      puts_1(gets_0());
		      delay(100);
					
					puts_0("0110");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
					puts_1("MAF: ");
					delay(1000);
		      puts_1(gets_0());
		      delay(100);
					
					
					puts_0("0111");
		      Send_Char_0(0x0D);
		      Send_Char_0(0x0A); 
		      delay(100);
					puts_1("TP: ");
					delay(1000);
		      puts_1(gets_0());
		      delay(100);
					*/
	}
return 0;		
}

void Clk_Init()
{
	ICS_C1|=ICS_C1_IRCLKEN_MASK; 		/* Enable the internal reference clock*/ 
	ICS_C3= 0x90;						        /* Reference clock frequency = 31.25 KHz*/		
	while(!(ICS_S & ICS_S_LOCK_MASK)); /* Wait for PLL lock, now running at 40 MHz (1280 * 31.25Khz) */		
  ICS_C2|=ICS_C2_BDIV(1)  ; 			/*BDIV=2, Bus clock = 20 MHz*/
	ICS_S |= ICS_S_LOCK_MASK ; 			/* Clear Loss of lock sticky bit */	
}

void delay(unsigned int itime)
{
unsigned int i,j;
for(i=0;i<=itime;i++)
for(j=0;j<=3000;j++);
}
