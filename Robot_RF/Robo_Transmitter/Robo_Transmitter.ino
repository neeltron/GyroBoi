// TRANSMITTER CODE

//NOTE :- THIS CODE IS USED WHEN YOU WANT TO CONTROL THE ROBOT VIA THE COMPUTER!!!!

#include <VirtualWire.h>
const int xpin = A0; // x-axis of the accelerometer
const int ypin = A1; // y-axis
const int zpin = A2; // z-axis
void setup()
{
    Serial.begin(9600);    // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
     
    vw_setup(2000);  // Bits per sec
        vw_set_tx_pin(3); //Transmitter Data Pin to Digital Pin 3
}//close setup

void loop()
{
  int x = analogRead(xpin); //read from xpin
delay(1); //
int y = analogRead(ypin); //read from ypin
delay(1);
int z = analogRead(zpin); //read from zpin
 
float zero_G = 512.0; //ADC is 0~1023 the zero g output equal to Vs/2
float scale = 102.3; //ADXL335330 Sensitivity is 330mv/g
//330 * 1024/3.3/1000
float x_a = (x - 331.5)/65*9.8, y_a = (y - 329.5)/68.5*9.8, z_a = (z - 340)/68*9.8;
Serial.print(x_a); //print x value on serial monitor
Serial.print("\t");
Serial.print(y_a); //print y value on serial monitor
Serial.print("\t");
Serial.print(z_a); //print z value on serial monitor
Serial.print("\n");
  

 
    if(y_a>7)
    { 
    char *msg2 = "f";
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    }
     
    else if(y_a<=-3)
    {
   char *msg2 = "b";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);  

    }

    else if(y_a<=7 && y_a > -3) //if controller types s
    {
   char *msg2 = "s";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);  
    }
    
    if(x_a >= 7) {
   char *msg2 = "l";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);    
  }     
    if(x_a<=0) //if controller types r
    {
   char *msg2 = "r";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg2, strlen(msg2));//send byte to the receiver
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);   
    }
   }// close switch-case
  //close if 
//close loop
  
 // End Of Code 
