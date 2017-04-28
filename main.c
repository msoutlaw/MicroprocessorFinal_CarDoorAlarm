// Final Project: Car Door Alarm
//
//Daniel Cerdeira and Nichelle Outlaw


#include <msp430.h> 

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    P1OUT = 0b00000000;  	// Port 1 is the output
       P1DIR = 0b11111111;  	 // Port 1 direction is set to HIGH
       P2DIR = 0b00000000;  	   // Port 2 direction is set to LOW


    int BIT_MASK_DOORS = 0b00001111; // carDoors initialized to high, carDoors are open
    int BIT_MASK_ALARM = BIT4; 		// Master carLock is set to P2.4
    int carDoors = 0;				//carDoors is declared
    int carLock = 0; 				//carLock declared
    int NOT_OPEN = 0;			//Declaration
    while(1)
    {
    	carDoors = P2IN & BIT_MASK_DOORS; // carDoors initialized

     if(carDoors == BIT_MASK_DOORS) // If all carDoors are closed, then the master carLock can turn on
		{
			if((P2IN & BIT4) == BIT4) // If carDoors on Port 2 are closed and are EQUAL to BIT4
			{
				if(!NOT_OPEN)
				{
					carLock ^= BIT0;  //XOR
					NOT_OPEN = 1;
				}
			}
			else
			{
				NOT_OPEN = 0;
			}
		}


		if(carLock) // This is inverts the carDoors // If the car is locked the LED will go
		{
			P1OUT = ~(BIT_MASK_DOORS | BIT_MASK_ALARM);
		}
		else //else car P1OUT depends on the input from push buttons and carLock carLock is on
		{

			P1OUT = ~carDoors | BIT_MASK_ALARM;
		}
    }
}










