#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <Bounce2.h>
#include "buttontron.h"
#include "sound.h"

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

Bounce buttonBig = Bounce();

void setup() {
	setupSound();

	buttonBig.attach(PIN_BUTTON_BIG);
	buttonBig.interval(BUTTON_DEBOUNCE_TIME_MS);

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

	playBeep();

	pinMode(PIN_BUTTON_BIG, INPUT_PULLUP);

	Serial.println(F("Hello World"));

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
	if (buttonBig.update()) {
		if (buttonBig.fell()) {
			if (gameTaps == 0) gameTime = 0;

			gameTapTimes[gameTaps] = gameTime;
			gameTaps++;

			if (gameTaps > 10) {
				for (int i = 0; i < gameTaps; i++) {
					Serial.println(gameTapTimes[i]);
				}
				gameTaps = 0;
				playBeep();
			}

			matrix.println(gameTaps);
			matrix.writeDisplay();
		}
	}
}

