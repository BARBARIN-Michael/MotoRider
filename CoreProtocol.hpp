#pragma once

#include <LGSM.h>                                                 // Include Linkit ONE GSM library
#include "debugMode.hpp"

class CoreProtocol {
  private :
    String  _number;

  public :
    CoreProtocol(String number);
    void sendMessage(String message);
    String receiveMessage(void);
    void parseSMS(String message);
    String getMessage(void);
};

