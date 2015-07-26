#include <elapsedMillis.h>

#define PIN_NOSLEEP_RESISTOR 	12
#define PIN_NOSLEEP_LED			13

#define NOSLEEP_ACTIVE_MS		20
#define NOSLEEP_INACTIVE_MS		2000

elapsedMillis noSleepTime = 0;
bool noSleepHigh = false;
bool stayAwake = true;

void setupNoSleep() {
	pinMode(PIN_NOSLEEP_RESISTOR, OUTPUT);
	pinMode(PIN_NOSLEEP_LED, OUTPUT);
}

void setNoSleepEnabled(bool value) {
	if (stayAwake == value) return;
	stayAwake = value;
	Serial.println(F("no sleep toggled"));
}

void updateNoSleep() {
	if (noSleepHigh && noSleepTime > NOSLEEP_ACTIVE_MS) {
		// set inactive 
		digitalWrite(PIN_NOSLEEP_RESISTOR, LOW);
		digitalWrite(PIN_NOSLEEP_LED, LOW);
		noSleepHigh = false;
		noSleepTime = 0;
	} else if (stayAwake && !noSleepHigh && noSleepTime > NOSLEEP_INACTIVE_MS) {
		// set active 
		digitalWrite(PIN_NOSLEEP_RESISTOR, HIGH);
		digitalWrite(PIN_NOSLEEP_LED, HIGH);
		noSleepHigh = true;
		noSleepTime = 0;
	}
}