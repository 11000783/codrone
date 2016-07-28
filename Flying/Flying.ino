
 // 3. Include the CoDrone library in your code
#include <CoDrone.h>
// 1. Add the method that runs once, before anything else
 void setup() {
//   4. Set up the thread - HINT: 115200
CoDrone.begin(115200);
//   5. Create a byte array that holds your specific drone address//   6. Connect to your drone using the address - HINT: It functions as an AddressInputDrone
byte droneAddress[6] = {0x14, 0xC2, 0x60, 0x78, 0xD5, 0xA4};
  CoDrone.AutoConnect(AddressInputDrone, droneAddress);
// 2. Add the method that runs repeatedly once the program starts
 }
void loop() {
//    7. Create a variable to hold each sensor value
//    HINT: You can name them left, middle, and right (despite being digital sensors 11, 14, and 18)
byte sensorright = digitalRead(18);
byte sensorleft = digitalRead(14);
byte sensormiddle = digitalRead(11);
//    8. Check to see if the left sensor is triggered
if (sensorleft == 1) {
  CoDrone.FlightEvent(TakeOff);
}
//        10. Kill the drone - HINT: Stop the drone with a FlightEvent
   else if (sensormiddle == 1){
  CoDrone.FlightEvent(Stop);
 }
//    9. If not, check to see if the right sensor is triggered
else if (sensorright == 1) {
CoDrone.FlightEvent(Landing);

//        11. TakeOff
    
//        12. Go up with a speed of 100
THROTTLE = 100;
//        Send the command - HINT: Use .Control()
CoDrone.Control();
//        Wait for one second - HINT: Use delay(____);
delay(2000);
//        13. Go forward (80) and keep going up with a speed of 80
PITCH = 80;
THROTTLE = 100;
//        Send the commandDS/
CoDrone.Control();
//        Wait for half a second
delay(750);
//        14. Go right (80) and keep going up with a speed of 80
ROLL = 80;
THROTTLE = 100;
//        Send the command
CoDrone.Control();
//        Wait for half a second
delay(750);
//        15. Go back (80) and keep going up with a speed ;of 80
PITCH = -80;
THROTTLE = 100;
//        Send the command
CoDrone.Control();
//        Wait for half a second
delay(750);
//        16. Go left (80) and keep going up with a speed of 80
ROLL = -80;
THROTTLE = 100;
//        Send the command
CoDrone.Control();
//        Wait for half a second
delay(750);
//        17. Land

}
}
