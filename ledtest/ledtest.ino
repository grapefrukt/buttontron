const int resistorPin =  12;
const int ledPin =  13;

void setup() {
	pinMode(resistorPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
}

void loop() {
	digitalWrite(resistorPin, HIGH);
	digitalWrite(ledPin, HIGH);
	delay(20);
	digitalWrite(resistorPin, LOW);
	digitalWrite(ledPin, LOW);
	delay(2000);
}
