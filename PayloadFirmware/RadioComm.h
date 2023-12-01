#ifndef RADIOCOMM_H

#include <stdint.h>

struct vec3 {
  double x;
  double y;
  double z;
};

struct Packet {
  long ID;
  vec3 orientation;
  vec3 accel;
  vec3 vel;
  long upTime;
  long flightTime;
  uint8_t state;
};

Packet makePacket(vec3 orient, vec3 accel, vec3 vel, uint8_t state);
bool TxPacket(Packet p);



#endif