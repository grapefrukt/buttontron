// led display
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <Bounce.h>
#include "buttontron.h"

#define PIN_PRINTER_TX 3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define PIN_PRINTER_RX 4 // Arduino receive   GREEN WIRE   labeled TX on printer
#define PIN_BUTTON_BIG 11 // Big button

#define GAME_MAX_PRESSES 		1024
#define GAME_TIME_US			10 * 1000 * 1000
#define BUTTON_DEBOUNCE_TIME_MS	5

Adafruit_7segment matrix = Adafruit_7segment();

// thermal printer
#include <Adafruit_Thermal.h>
#include "SoftwareSerial.h"

SoftwareSerial mySerial(PIN_PRINTER_RX, PIN_PRINTER_TX); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

// game
int gameTaps = 0;
int gameTapTimes[GAME_MAX_PRESSES];
elapsedMicros gameTime = 0;

Bounce buttonBig = Bounce(PIN_BUTTON_BIG, BUTTON_DEBOUNCE_TIME_MS);

void setup() {
	// led display init
	matrix.begin(0x70);
	matrix.setBrightness(15); // 15 is max
	matrix.clear();
	matrix.writeDisplay();
	delay(500);

	for (int i = 5; i--; i >= 0){
		matrix.println(i);
		matrix.writeDisplay();
		delay(300);
	}

	pinMode(PIN_BUTTON_BIG, INPUT_PULLUP);

	Serial.print(F("Hello World"));

	//delay(2000);

	/*mySerial.begin(19200);

	// thermal printer init
	printer.begin();
	printer.justify('C');
	printer.println(F("Philip Linde"));
	printer.println(F("ater chips"));
	printer.println(F("kodar data "));
	printer.feed(5);

	printer.sleep();      // Tell printer to sleep
	delay(3000L);         // Sleep for 3 seconds
	printer.wake();       // MUST wake() before printing again, even if reset
	printer.setDefault(); // Restore printer to defaults
	*/
}

void loop() {

	//if (gameTime > GAME_TIME_US) gameTime = 0;

	//int ms = gameTime / 1000000;
	//matrix.println(ms);
	//matrix.writeDisplay();

	//int foo = digitalRead(PIN_BUTTON_BIG);
	//Serial.print(foo);
	//matrix.println(foo);
	//matrix.writeDisplay();

	if (buttonBig.update()) {
		if (buttonBig.fallingEdge()) {
			gameTaps++;
			gameTapTimes[gameTaps] = gameTime;

			matrix.println(gameTaps);
			matrix.writeDisplay();
		}
	}

	

	// print a hex number
	/*matrix.print(0xDEAD, HEX);
	matrix.writeDisplay();
	delay(1000);
	
	matrix.print(0xBEEF, HEX);
	matrix.writeDisplay();
	delay(1000);
	
	matrix.clear();
	matrix.writeDisplay();
	delay(500);*/
}

