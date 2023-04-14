#include "nu32dip.h" // constants, functions for startup and UART
#include <stdio.h>
#include <math.h>

#define SINE_POINTS 100

void send_sine(); // blink the LEDs function

int main(void) {
  
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
    //keep checking if the button is pressed (ie. if A4 goes LOW)
      if(PORTAbits.RA4 == 0){
          send_sine();
      }
  }
}

// blink the LEDs
void send_sine(){
    char message[100];
	for(int i=0; i< SINE_POINTS; i++){
        //send the appropriate value
        //1 period of sin = 0, 2pi
        double x = (((double)i)/SINE_POINTS) * 2 * M_PI;
        double s = sin(x) + 1.65;
        
        //send the value with UART
        sprintf(message, "%lf\r\n", s);
        NU32DIP_WriteUART1(message);
        
        //wait 10ms
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 240000){}
		
	}
}
		
