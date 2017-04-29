/*
** ESP8266 Blink Sketch - more on http://42bots.com
** Note that you need to use the D0, D1...format for addressing the pins printed on the nodeMCU board.
** For the pin mapping diagram see: https://github.com/nodemcu/nodemcu-devkit-v1.0
** Connect an LED between pin marked as D0 on NodeMCU board and ground through a resistor 1K Ohm, or more.
** The onboard LED for NodeMCU Dev Kit Board v2 is on GPIO pin 16, marked as D0 on the board.
** The wider "unofficial" v3 of the NodeMCU board has no onboard LED.
** The onboard LED is connected in sink mode: it will be on when the pin is set to low (ground).
** If you have an LED connected to pin D0 it will be high, when the onboard LED is low.
*/

int ledPin = D0; // LED attached to pin D0 through a 1k Ohm resistor           

void setup() {
  pinMode(ledPin, OUTPUT);     // Initialize the LED pin as an output
}

void loop() {
  digitalWrite(ledPin, LOW);   // Onboard LED is on, and the LED you connected to pin D0 is off.
  delay(1000);                 // Wait for a second
  digitalWrite(ledPin, HIGH);  // Onboard LED is off, and the LED you connected to pin D0 is on.
  delay(2000);                 // Wait for two seconds
}
