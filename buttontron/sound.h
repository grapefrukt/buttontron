#include "AudioSampleGong.h"       // http://www.freesound.org/people/zgump/sounds/86334/

// GUItool: begin automatically generated code
AudioPlayMemory          sound0;       //xy=319,302
AudioPlayMemory          sound1;       //xy=321,360
AudioPlayMemory          sound2;       //xy=321,412
AudioPlayMemory          sound3;       //xy=332,464
AudioMixer4              mix;         //xy=534,364
AudioOutputAnalog        dac;           //xy=662,357
AudioConnection          patchCord1(sound0, 0, mix, 0);
AudioConnection          patchCord2(sound1, 0, mix, 1);
AudioConnection          patchCord3(sound2, 0, mix, 2);
AudioConnection          patchCord4(sound3, 0, mix, 3);
AudioConnection          patchCord5(mix, dac);
// GUItool: end automatically generated code


void setupSound() {
	AudioMemory(10);
	mix.gain(0, 0.4);
	mix.gain(1, 0.4);
	mix.gain(2, 0.4);
	mix.gain(3, 0.4);
	dac.analogReference(INTERNAL);
}

void playBeep(){
	sound0.play(AudioSampleGong);
}