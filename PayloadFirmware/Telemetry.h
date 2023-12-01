#ifndef TELEMETRY_H

#include "RadioComm.h"

class TelemetryData {
  private:
    uint8_t state;
    vec3 orientation;
    vec3 accel;
    vec3 vel;
    long upTime_ms;
    long flightTime_ms;
    long launchTimestamp_ms;

  public:
    TelemetryData();
    void Start();
    void UpdateData();
    void TxData();
};


#endif