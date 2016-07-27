#include <CoDrone.h>
void setup() {
  // put your setup code here, to run once:
  CoDrone.begin(115200);
  byte droneAddress[6] = {0x14, 0xC2, 0x60, 0x78, 0xD5, 0xA4};
  CoDrone.AutoConnect(AddressInputDrone, droneAddress);

}
void loop() {
  byte sensor1 = digitalRead(11);
  byte sensor4 = digitalRead(14);
  byte sensor8 = digitalRead(18);
  if ( sensor1 == 1){
    CoDrone.FlightEvent(Stop);
    }
  else if (sensor8 == 1) { 
    CoDrone.FlightEvent(TakeOff);
  }
    else if (sensor4 == 1){
    CoDrone.FlightEvent(Landing);
    }
  }
