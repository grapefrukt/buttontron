#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "AudioSampleSnare.h"        // http://www.freesound.org/people/KEVOY/sounds/82583/
#include "AudioSampleTomtom.h"       // http://www.freesound.org/people/zgump/sounds/86334/
#include "AudioSampleHihat.h"        // http://www.freesound.org/people/mhc/sounds/102790/
#include "AudioSampleKick.h"         // http://www.freesound.org/people/DWSD/sounds/171104/

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

// GUItool: begin automatically generated code
AudioPlayMemory          sound0;       //xy=319,302
AudioPlayMemory          sound1;       //xy=321,360
AudioPlayMemory          sound2;       //xy=321,412
AudioPlayMemory          sound3;       //xy=332,464
AudioMixer4              mix1;         //xy=534,364
AudioOutputAnalog        dac1;           //xy=662,357
AudioConnection          patchCord1(sound0, 0, mix1, 0);
AudioConnection          patchCord2(sound1, 0, mix1, 1);
AudioConnection          patchCord3(sound2, 0, mix1, 2);
AudioConnection          patchCord4(sound3, 0, mix1, 3);
AudioConnection          patchCord5(mix1, dac1);
// GUItool: end automatically generated code


elapsedMillis time = 0;

const int delayMs = 300;

void setup() {
	AudioMemory(10);
	mix1.gain(0, 0.4);
	mix1.gain(1, 0.4);
	mix1.gain(2, 0.4);
	mix1.gain(3, 0.4);


	// led display init
	matrix.begin(0x70);
	matrix.setBrightness(15); // 15 is max
	matrix.println(0);
	matrix.writeDisplay();
}

int beat = 0;

void loop() {
	if (time < delayMs) return;
	time -= delayMs;

	beat++;
	
	if (beat % 2 == 0){
		sound0.play(AudioSampleKick);
		matrix.print(0xB00F, HEX);
	}

	if (beat % 2 == 1){
		sound1.play(AudioSampleSnare);
		matrix.print(0xFAAA, HEX);
	}

	if (beat % 8 == 0){
		sound2.play(AudioSampleHihat);
		matrix.print(0xC11F, HEX);
	}

	if (beat % 3 == 0){
		sound3.play(AudioSampleTomtom);
		matrix.print(0xCCCC, HEX);
	}

	matrix.writeDisplay();

	//if (beat % 4 == 0) sound2.play(AudioSampleHihat);
}


