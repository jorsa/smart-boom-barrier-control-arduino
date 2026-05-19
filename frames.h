/*
Holds the definitions for the frames to display on the Arduino Uno R4 LED Matrix.

You can easily build the frames by drawing them with the LED Matrix Editor:
https://ledmatrix-editor.arduino.cc

*/

const uint32_t arrow_right[] = {
		0x10030070,
		0xffffff7,
		0x300100,
		66
};

const uint32_t arrow_left[] = {
		0x800c00,
		0xeffffff0,
		0xe00c008,
		66
};

const uint32_t arrow_up[] = {
		0x600f01f,
		0x83fc0600,
		0x60060060,
		66
};

const uint32_t arrow_down[] = {
		0x6006006,
		0x603fc1,
		0xf80f0060,
		66
};

const uint32_t stop[] = {
		0x20410809,
		0x600600,
		0x90108204,
		66
};

const uint32_t heart[] = {
		0x19826440,
		0x24022041,
		0x8090060,
		66
};

const uint32_t car[] = {
		0x0,
		0x1e01f87,
		0xfe7fe30c,
		66
};

const uint32_t titi[] = {
		0xeb,
		0xa4924924,
		0x92000000,
		66
};