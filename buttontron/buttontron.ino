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
#include "button.h"
#include "sound.h"
#include "no_sleep.h"
#include "printer.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
	setupSound();
	setupNoSleep();
	setupPrinter();
	setupButton();

	// led display init
	matrix.begin(0x70);
	matrix.setBrightness(15); // 15 is max
	matrix.clear();
	matrix.writeDisplay();
	delay(100);

	Serial.println(F("buttontron booted"));
	setState(IDLE);
}

void loop() {
	updateButton();
	updateNoSleep();
}

// BUTTON

#define PIN_BUTTON_BIG 			11
#define GAME_MAX_PRESSES 		1024
#define GAME_TIME_US			5 * 1000 * 1000
#define SLEEP_AFTER_TIME_US		60 * 1000 * 1000
#define BUTTON_DEBOUNCE_TIME_MS	5

State state = BOOT;
int gameTaps = 0;
int gameTapTimes[GAME_MAX_PRESSES];
elapsedMicros stateTime = 0;
int lastElapsedSecond = 0;
Bounce buttonBig = Bounce();

void setupButton() {
	pinMode(PIN_BUTTON_BIG, INPUT_PULLUP);
	buttonBig.attach(PIN_BUTTON_BIG);
	buttonBig.interval(BUTTON_DEBOUNCE_TIME_MS);
}

void updateButton() {
	if (state == IDLE) updateIdle();
	if (state == PLAY) updatePlay();
}

void updateIdle() {
	if (buttonBig.update() && buttonBig.fell()) setState(PLAY);
	if (stateTime > SLEEP_AFTER_TIME_US) setNoSleepEnabled(false);
	matrix.print(0x8888, HEX);
	matrix.writeDisplay();
}

void updatePlay() {
	if (buttonBig.update() && buttonBig.fell()) {
		gameTapTimes[gameTaps] = stateTime;
		gameTaps++;
	}

	int seconds = stateTime / (1000 * 1000);
	if (lastElapsedSecond != seconds) {
		lastElapsedSecond = seconds;
		playSoundTick();
		Serial.println(lastElapsedSecond);
	}

	matrix.println(gameTaps);
	matrix.writeDisplay();

	if (stateTime > GAME_TIME_US) setState(END);
}

void enterIdle() {
	Serial.println(F("enter idle"));
	playSoundReady();
}

void enterPlay() {
	Serial.println(F("enter play"));
	// start at one because the "first tap" triggered this state
	gameTaps = 1;
}

void enterEnd() {
	Serial.println(F("enter end"));
	playSoundEnd();

	for (int i = 0; i < gameTaps; i++) {
		Serial.println(gameTapTimes[i]);
	}
	printResults(gameTaps);

	setState(IDLE);
}

void enterPrint() {
	Serial.println(F("enter print"));
}

void setState(State newState) {
	stateTime = 0;
	state = newState;
	setNoSleepEnabled(true);
	switch (state) {
		case IDLE : 
			enterIdle();
			break;
		case PLAY :
			enterPlay();
			break;
		case END :
			enterEnd();
			break;
		case PRINT :
			enterPrint();
			break;
		default :
			break;
	}
}