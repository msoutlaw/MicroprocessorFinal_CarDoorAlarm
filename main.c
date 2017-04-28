// Final Project: Car Door Alarm
//
//Daniel Cerdeira and Nichelle Outlaw


#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer


    P1DIR = 0b11111111;  	 // Port 1 direction is set to HIGH
    P2DIR = 0b00000000;  	   // Port 2 direction is set to LOW
    P1OUT = 0b00000000;  	//  output



    int BIT_MASK_DOORS = 0b00001111; // Doors initialized to high, carDoors are open
    int BIT_MASK_ALARM = BIT4; 		// Master Lock is set to P2.4
    int Doors = 0;				//Doors is declared
    int Lock = 0; 				//Lock declared
    int NOT_OPEN = 0;			//Declaration
    while(1)

    {
    	Doors = P2IN & BIT_MASK_DOORS; // Doors initialized

     if(Doors == BIT_MASK_DOORS) // If all Doors are closed, then the master carLock can turn on
		{
			if((P2IN & BIT4) == BIT4) // If Doors on Port 2 are closed and are EQUAL to BIT4
			{
				if(!NOT_OPEN)
				{
					Lock ^= BIT0;  //XOR
					NOT_OPEN = 1;
				}
			}

			else
			{
				NOT_OPEN = 0;
			}
		}


		if(Lock) // This is inverts the Doors // If the car is locked the LED will go
		{
			P1OUT = ~(BIT_MASK_DOORS | BIT_MASK_ALARM);
		}
		else //else car P1OUT depends on the input from push buttons and Lock Lock is on
		{

			P1OUT = ~Doors | BIT_MASK_ALARM;
		}
    }
}








