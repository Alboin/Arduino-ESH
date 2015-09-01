#include <IRLib.h>

IRsendSony My_Sender;

int message = 0;


void setup()
{
  Serial.begin(9600);

}

void loop() {
  if (Serial.read() != -1) {
    message = Serial.read();
    //send a code every time a character is received from the serial port
    //Sony DVD power A8BCA
  My_Sender.send(message, 20);
  //My_Receiver.enableIRIn(); // Re-enable receiver
  }
}

