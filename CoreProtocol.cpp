#include "CoreProtocol.hpp"
#include "debugMode.hpp"

CoreProtocol::CoreProtocol(String number)
{
  this->_number = number;
  while (!LSMS.ready())                       // Wait for the sim to initialize
  {
    Serial.println(".");
    delay(1000);                              // Wait for a second and then try again
  }
  Serial.println("Sim initialized");          // When SIM is started, print "Sim initialized" in the serial port
}

void CoreProtocol::sendMessage(String message) {
  LSMS.beginSMS(_number.c_str());            // Saves the number where user wants to send SMS. To be changed before uploading sketch
  LSMS.print(message);
  if (LSMS.endSMS())
    Serial.println("SMS Send");
  else
    Serial.println("SMS not Send");
}

String CoreProtocol::receiveMessage(void) {
  String messageReceive = "";
  int c = 0;

  while ((c = LSMS.read()) > 0) {
    messageReceive += (char)c;
  }
  LSMS.flush();
  return (messageReceive);
}

String CoreProtocol::getMessage(void) {
  String message;
  char number[20];

  if (LSMS.available()) {
    Serial.println("Message receive");
    LSMS.remoteNumber(number, 20); // get only 10 number of tel number
    if (strcmp(number, this->_number.c_str()) == 0) { //Test if the Phone Number is mine
      String message = this->receiveMessage();
      Serial.println(message);
      LSMS.flush();
      return message;
    }
    else {
      String message = receiveMessage();
      String errorMessage = "BAD NUMBER (" + String(number) + ") Send : " + message;
      Serial.println(errorMessage);
      sendMessage(String(number) + " try to communicate with your system, message : " + message);
      LSMS.flush();
    }
  }
  return String();
}

