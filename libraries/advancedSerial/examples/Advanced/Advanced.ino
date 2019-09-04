/*
   advancedSerial Library - Advanced Example
   https://github.com/klenov/advancedSerial
*/

#include <advancedSerial.h>

void setup() {
  Serial.begin(9600);

  aSerial.setPrinter(Serial);
  aSerial.setFilter(Level::vv);
  /* Uncomment the following line to disable the output. By defalut the ouput is on. */
  // aSerial.off();
}

void loop() {
  // This message will be printed
  aSerial.v().println("Level v() is less verbose than the filtering threshold");
  // This message also will be printed
  aSerial.vv().println("Level vv() is equal to the filtering threshold");

  // This message won't be printed
  aSerial.vvv().println("Level::vvv is more verbose than the filtering threshold");
  // This message won't be printed
  aSerial.vvvv().println("Level::vvvv is more verbose than the filtering threshold");
  
  // Consider storing long strings on flash memory rather than RAM using F() macro
  aSerial.v().pln(F("This string will be stored in flash memory"));

  // Two empty lines
  aSerial.v().println().pln();

  delay(3000);
}
