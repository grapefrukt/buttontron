#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <Bounce2.h>
#include "buttontron.h"
#include "sound.h"
#include "no_sleep.h"
#include "printer.h"

#define PIN_BUTTON_BIG 11 // Big button

#define GAME_MAX_PRESSES 		1024
#define GAME_TIME_US			10 * 1000 * 1000
#define BUTTON_DEBOUNCE_TIME_MS	5

Adafruit_7segment matrix = Adafruit_7segment();

// game
int gameTaps = 0;
int gameTapTimes[GAME_MAX_PRESSES];
elapsedMicros gameTime = 0;

Bounce buttonBig = Bounce();

void setup() {
	setupSound();
	setupNoSleep();
	setupPrinter();

	buttonBig.attach(PIN_BUTTON_BIG);
	buttonBig.interval(BUTTON_DEBOUNCE_TIME_MS);

	// led display init
	matrix.begin(0x70);
	matrix.setBrightness(15); // 15 is max
	matrix.clear();
	matrix.writeDisplay();
	delay(500);

	for (int i = 5; i -= 1; i >= 0){
		matrix.println(i);
		matrix.writeDisplay();
		delay(300);
	}

	playBeep();

	pinMode(PIN_BUTTON_BIG, INPUT_PULLUP);

	Serial.println(F("Hello World"));
}

void loop() {
	if (buttonBig.update()) {
		if (buttonBig.fell()) {
			if (gameTaps == 0) gameTime = 0;

			gameTapTimes[gameTaps] = gameTime;
			gameTaps++;

			if (gameTaps >= 50) {
				for (int i = 0; i < gameTaps; i++) {
					Serial.println(gameTapTimes[i]);
				}
				printResults(gameTaps);
				playBeep();
				gameTaps = 0;
			}

			matrix.println(gameTaps);
			matrix.writeDisplay();
		}
	}

	updateNoSleep();
}

