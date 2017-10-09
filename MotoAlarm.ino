#include "CoreProtocol.hpp"
#include "debugMode.hpp"


/* ************************************************************************************************
 *  GLOBAL
 * ***********************************************************************************************/
String  numberOK = "+33769346158";
CoreProtocol *prot;   

typedef struct security {
  bool gps_state;
  bool accelerometer_state;
} t_security;


// ************************************************************************************************

void setup() {

  Serial.begin(115200);                       // Initializes serial port at 115200 bauds
  Serial.println("Starting Operating Alarm!");  // Start the Send SMS program
  delay(3000);
}

void activeGPS(bool turn)
{
  if (turn == false)
    LGPS.powerOff();
  else
    LGPS.powerOn();
}

void securitySystemMode(String elem, bool *b_elem, bool turn) {

  *b_elem = turn;
  if (elem == "GPS")
    activeGPS(turn);
  prot->sendMessage(elem + " turn " + turn);
  delay(3000);
}

void parseGPS(){

  Serial.println((char*)info.GPGGA);
  
  parseGPGGA(info.GPGGA);
}

void parseMessage(t_security *security, String message) {
  bool state;
  
  if (message == "S_ON") {
    state = true;
    securitySystemMode("GPS", &security->gps_state, state);
    securitySystemMode("ACCELEROMETER", &security->accelerometer_state, state);
  }
  else if (message == "S_OFF") {
    state = false;
    securitySystemMode("GPS", &security->gps_state, state);
    securitySystemMode("ACCELEROMETER", &security->accelerometer_state, state);
  }
  else if (message == "GPS_ON") {
    state = true;
    securitySystemMode("GPS", &security->gps_state, state);
  }
  else if (message == "GPS_OFF") {
    state = false;
    securitySystemMode("GPS", &security->gps_state, state);
  }
  else if (message == "ACC_ON") {
    state = true;
    securitySystemMode("GPS", &security->accelerometer_state, state);
  }
  else if (message == "ACC_OFF") {
    state = false;
    securitySystemMode("GPS", &security->accelerometer_state, state);
  }
}

void loop() {
  static t_security security;
  static int init =0;
  if (init == 0) {
    prot = new CoreProtocol(numberOK);
    init = 1;
  }
  String message = prot->getMessage();
  if (message.length() > 0)
    parseMessage(&security, message);
}

