#ifndef RADIOCOMM_H

#include <stdint.h>
#include <RFM69.h>         //get it here: https://www.github.com/lowpowerlab/rfm69
#include <RFM69_ATC.h>     //get it here: https://www.github.com/lowpowerlab/rfm69
#include <SPIFlash.h>      //get it here: https://www.github.com/lowpowerlab/spiflash
#include <SPI.h>           //included with Arduino IDE install (www.arduino.cc)

#define SERIAL_BAUD 115200
#define FREQUENCY   RF69_915MHZ
#define NODEID      99
#define NETWORKID   100
#define GATEWAYID   1
#define ENCRYPTKEY  "UTolRocketryBlue"

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

class RadioController
{
  private:
    long launchTime;
    const long ID = 0xFEFEFEF;
    RFM69_ATC radio;
    byte sendSize=0;
    bool requestACK = false;
    int TRANSMITPERIOD = 300; //transmit a packet to gateway so often (in ms)
  public:
    RadioController();
    Packet MakePacket(vec3 orient, vec3 accel, vec3 vel, uint8_t state);
    bool TxPacket(Packet p);
};




#endif