#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define PIN_PRINTER_TX 3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define PIN_PRINTER_RX 4 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(PIN_PRINTER_RX, PIN_PRINTER_TX); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setupPrinter() {
	mySerial.begin(19200);
}

void printResults(int numPresses) {
	printer.wake();       // MUST wake() before printing again, even if reset
	printer.begin();
	printer.justify('C');
	printer.println(F("YOUR SCORE IS:"));
	printer.doubleHeightOn();
	printer.println(numPresses);
	printer.doubleHeightOff();
	printer.println(F("good job."));
	printer.feed(5);
	printer.sleep();
}