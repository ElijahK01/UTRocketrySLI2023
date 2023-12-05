#include "RadioComm.h"

RadioController::RadioController()
{
  Serial.begin(SERIAL_BAUD);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setHighPower(); //must include this only for RFM69HW/HCW!
  radio.encrypt(ENCRYPTKEY);
}

Packet RadioController::MakePacket(vec3 orient, vec3 accel, vec3 vel, uint8_t state)
{
  long upTime = millis();
  long flightTime = upTime - launchTime;
  
  return Packet{
    ID,
    orient,
    accel,
    vel,
    upTime,
    flightTime,
    state
  };
}

bool RadioController::TxPacket(Packet p)
{
  char buff[48];
  char frame0[8]; // ID
  char frame1[48];// Orientation and Acceleraton
  char frame2[41];// velocity, uptime, flight time, state

  int i;
  // frame 0 construction
  for(i = 0; i < 8; i++)
  {
    frame0[i] = *(reinterpret_cast<unsigned char*>(&p.ID));
  }

  // frame 1 construction
  for(i = 0; i < 24; i++)
  {
    frame1[i] = *(reinterpret_cast<unsigned char*>(&p.orientation));
  }
  for(i = 0; i < 24; i++)
  {
    frame1[i + 24] = *(reinterpret_cast<unsigned char*>(&p.accel));
  }

  // frame 2 construction
  for(i = 0; i < 24; i++)
  {
    frame2[i] = *(reinterpret_cast<unsigned char*>(&p.vel));
  }

  for(i = 0; i < 8; i++)
  {
    frame2[i + 24] = *(reinterpret_cast<unsigned char*>(&p.upTime));
  }

  for(i = 0; i < 8; i++)
  {
    frame2[i + 32] = *(reinterpret_cast<unsigned char*>(&p.flightTime));
  }

  frame2[41] = *(reinterpret_cast<unsigned char*>(&p.state));

  // transmission
  sprintf(buff, frame0, 915);
  sprintf(buff, frame1, 915);
  sprintf(buff, frame2, 915);
}