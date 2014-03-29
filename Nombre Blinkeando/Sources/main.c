/*
@author: 		Walter Gonzalez Domenzain
@description: 	6030 Group
@functions:		None
@environment: 	KL25Z
@date: 			02/07/2012
@comments:		
@version:		1.0 - Initial
*/

#include "derivative.h" /* include peripheral declarations */

#define GPIO_PIN_MASK 0x1Fu
#define GPIO_PIN(x) (((1)<<(x & GPIO_PIN_MASK)))

//define PortLeds 		GPIOC_PDOR
#define PortLCD 		GPIOC_PDOR

#define PortEnable_1 	GPIOB_PDOR |= 0x01
#define PortEnable_0 	GPIOB_PDOR &= 0xFE

#define PortRS_1 		GPIOB_PDOR |= 0x02
#define PortRS_0 		GPIOB_PDOR &= 0xFD

#define PortButtons 	GPIOB_PDIR

#define ntime_15msec	0x0AD0
#define ntime_40msec	0x0AD0
#define ntime_1sec	0xFFFFF
#define	nIns	0
#define	nData	1


//--------------------------------------------------------------
//Declare Prototypes
/* Functions */
void cfgPorts(void);
void delay(int ntime);
void initLCD(void);
void sendCode(int Code, int PortData);

/* Variables */
int x;

/*@description: Initial Port Cfg 
*/

int main(void)
{
	
	
	
	for(;;)
	{//Loop
		cfgPorts();
		initLCD();
		sendCode(nIns, 0xC5);
		sendCode(nData,'A');
		sendCode(nData,'D');
		sendCode(nData,'R');
		sendCode(nData,'I');
		sendCode(nData,'A');
		sendCode(nData,'N');
		sendCode(nData,'A');
        delay(ntime_1sec);
        sendCode(nIns, 0x01);
        delay(ntime_1sec);

	}
	return 0;
}

void cfgPorts(void)
{
	//Turn on clock for portd and portb
	SIM_SCGC5 = 0x1C00;//0001 1110 0000 0000 see page 206
	//Also, we can use predefined masks created by freescale, such as:
	//SIM_SCGC5_PORTB_MASK;
	
	/* Set pins of PORTD as GPIO */
	PORTD_PCR0=(PORT_PCR_MUX(1));
	PORTD_PCR1=(PORT_PCR_MUX(1));
	PORTD_PCR2=(PORT_PCR_MUX(1));
	PORTD_PCR3=(PORT_PCR_MUX(1));
	PORTD_PCR4=(PORT_PCR_MUX(1));
	PORTD_PCR5=(PORT_PCR_MUX(1));
	PORTD_PCR6=(PORT_PCR_MUX(1));
	PORTD_PCR7=(PORT_PCR_MUX(1));	

	/* Set pins of PORTB as GPIO */
	PORTB_PCR0=(PORT_PCR_MUX(1));
	PORTB_PCR1=(PORT_PCR_MUX(1));
	
	/* Set pins of PORTC as GPIO */
	PORTC_PCR0=(PORT_PCR_MUX(1));
	PORTC_PCR1=(PORT_PCR_MUX(1));
	PORTC_PCR2=(PORT_PCR_MUX(1));
	PORTC_PCR3=(PORT_PCR_MUX(1));
	PORTC_PCR4=(PORT_PCR_MUX(1));
	PORTC_PCR5=(PORT_PCR_MUX(1));
	PORTC_PCR6=(PORT_PCR_MUX(1));
	PORTC_PCR7=(PORT_PCR_MUX(1));
	
	//Reasure first PortD value
	GPIOD_PDOR = 0x00;
	//Configure PortD as outputs
	GPIOD_PDDR = 0xFF;
	
	//Configure PortB as inputs
	GPIOB_PDDR = 0xFF;
	
	//Reasure first PortC value
	GPIOC_PDOR = 0x00;
	//Configure PortC as outputs
	GPIOC_PDDR = 0xFF;
}

void delay (ntime)

{
	x = ntime;
	while(x>0)
	{
	x--;
	}
}

void initLCD(void)
{


	//delay(ntime_15msec);
	//Commands = {0x38, 0x38, 0x38, 0x0C, 0x01};
	sendCode(nIns, 0x38);
	//delay(ntime_15msec);
	sendCode(nIns, 0x38);
	//delay(ntime_15msec);
	sendCode(nIns, 0x38);
	//delay(ntime_15msec);
	sendCode(nIns, 0x0C);
	//delay(ntime_15msec);
	sendCode(nIns, 0x01);
	
}

void sendCode(int Code, int PortData)
{
	PortRS_0;
	PortEnable_0;
	
	PortLCD = PortData;
	
	if (Code == nIns)
	{
		PortRS_0;
		PortEnable_1;
		delay(ntime_40msec);
		PortEnable_0;
		PortRS_0;
	}
	else if (Code == nData)
	{
		PortRS_1;
		PortEnable_1;
		delay(ntime_40msec);
		PortEnable_0;
		PortRS_0;
	}
}
