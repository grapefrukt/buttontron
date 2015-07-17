enum State {
	BOOT,
	IDLE,
	PLAY,
	END,
	PRINT
};

State state = BOOT;

void setState(State newState) {
	state = newState;
}
