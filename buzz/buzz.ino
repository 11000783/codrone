#include <CoDrone.h>
unsigned long startTime;
int step;
void setup() {
  CoDrone.begin(115200);
  byte droneAddress[6] = {0x14, 0xC2, 0x60, 0x78, 0xD5, 0xA4};
  CoDrone.AutoConnect(AddressInputDrone, droneAddress);
}

void loop() {
  byte sensorright = digitalRead(18);
  byte sensorleft = digitalRead(14);
  byte sensormiddle = digitalRead(11);
  if (sensorleft == 1) {
    CoDrone.FlightEvent(Stop);
    step = 0;
  }
  else if (sensormiddle == 1) {
    CoDrone.FlightEvent(Landing);
  }
  else if (sensorright == 1) {
    step = step + 1;
    if (step > 4) {
      step = 0;
    }
    CoDrone.Buzz(3000, 7);
  delay(200);
  }
  

  if (step == 1) {
    THROTTLE = 100;
    PITCH = 50;
  CoDrone.Control();
  }
  
  else if (step == 2) {
    PITCH = 60;
    CoDrone.Control();
  }
  else if (step == 3) {
    ROLL = -90;
    CoDrone.Control();
  }
  else if (step == 4) {
  PITCH = 100;
  CoDrone.Control();
}

else {
  CoDrone.FlightEvent(Landing);
}
}







