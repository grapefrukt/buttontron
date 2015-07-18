#include <elapsedMillis.h>

#define PIN_NOSLEEP_RESISTOR 	12
#define PIN_NOSLEEP_LED			13

#define NOSLEEP_ACTIVE_MS		20
#define NOSLEEP_INACTIVE_MS		2000

elapsedMillis noSleepTime = 0;
bool noSleepActive = false;

void setupNoSleep() {
	pinMode(PIN_NOSLEEP_RESISTOR, OUTPUT);
	pinMode(PIN_NOSLEEP_LED, OUTPUT);
}

void updateNoSleep() {
	if (noSleepActive && noSleepTime > NOSLEEP_ACTIVE_MS) {
		// set inactive 
		digitalWrite(PIN_NOSLEEP_RESISTOR, LOW);
		digitalWrite(PIN_NOSLEEP_LED, LOW);
		noSleepActive = false;
		noSleepTime = 0;
	} else if (!noSleepActive && noSleepTime > NOSLEEP_INACTIVE_MS) {
		// set active 
		digitalWrite(PIN_NOSLEEP_RESISTOR, HIGH);
		digitalWrite(PIN_NOSLEEP_LED, HIGH);
		noSleepActive = true;
		noSleepTime = 0;
	}
}