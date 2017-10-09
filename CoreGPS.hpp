#pragma once

#include <LGPS.h>                                                 // Include Linkit ONE GPS library

class CoreGPS {
  private :
    double latitude;
    double longitude;
    int tmp, hour, minute, second, num;
    bool start = false;

  public :
    CoreGPS();
    setStart(bool turn);
    setData(void);
    int getTime_hour(void);
    int getTime_minute(void);
    int getGPS_latitude(void);
    int getGPS_longitude(void);
}

