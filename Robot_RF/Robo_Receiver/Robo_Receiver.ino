// RECIEVER CODE

//NOTE :- THIS RECEIVER CODE IS USED WHEN YOU WANT TO CONTROL THE ROBOT VIA THE COMPUTER

#include <VirtualWire.h>

//declaring pin Nos of FIRST L293D
int en1 = 5;
int en2 = 6;
int in1 = 10;
int in2 = 11;
int in3 = 9;
int in4 = 8;
//declaring pin nos of SECOND L293D
int en1o2 = 3;
int en2o2 = 11;
int in1o2 = 4;
int in2o2 = 12;
int in3o2 = 14;
int in4o2 = 15;
int motorPin[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15};//array for storing pin nos

void setup()
{
  Serial.begin(9600);  // Debugging only
  Serial.println("setup");
  // Initialise the IO and ISR
  vw_setup(2000);  // Bits per sec
  vw_set_rx_pin(2);//Receiver at Digital Pin 2
  vw_rx_start();// Start the receiver PLL running


  for (int i = 0; i < 12; i++)
  {
    pinMode(motorPin[i], OUTPUT);
  }//close for loop

  /*
    This is basically what the for loop does :-
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(en1o2, OUTPUT);
    pinMode(en2o2, OUTPUT);
    pinMode(in1o2, OUTPUT);
    pinMode(in2o2, OUTPUT);
    pinMode(in3o2, OUTPUT);
    pinMode(in4o2, OUTPUT);
  */

}//close setup

void loop()
{



  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    digitalWrite(13, true); // Flash a light to show received good message
    // Message with a good checksum received, dump it.

    for (i = 0; i < buflen; i++)
    {
      Serial.print(buf[i]);
      if (buf[i] == 'f')
      {
        forward();//go forward when f is pressed
      }
      if (buf[i] == 'b')
      {
        backward();//go backward when b is pressed
      }
      if (buf[i] == 's')
      {
        stopMotor();//stop/brake when s is pressed
      }
      if (buf[i] == 'l')
      {
        left();//go left when l is presed
      }
      if (buf[i] == 'r')
      {
        right();//go right when r is pressed
      }

    }//close for loop

    digitalWrite(13, false);

  }//close main if
}//close loop
//you can print the data entered when debugging by adding Serial.println

////////////////////////////////////////////////////////////////////////////////////////

//set of functions
void forward()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void backward()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void left()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void right()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void stopMotor()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(en1o2, HIGH);
  digitalWrite(en2o2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in1o2, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in2o2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in3o2, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in4o2, LOW);
}
//End Of Code
