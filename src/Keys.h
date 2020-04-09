#pragma once
#ifndef KEYS_H
#define KEYS_H

#define NUM_OF_KEYS 17

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_HOME, KEY_END, MOUSE_LEFT_BUTTON, KEY_G, KEY_A, KEY_W,KEY_S,KEY_D, KEY_Z, ENTER,SPACEBAR,F1_KEY,LSHIFT
};

static bool key[NUM_OF_KEYS];

inline void initKeys() {
	for (int i = 0; i < NUM_OF_KEYS; i++) {
		key[i] = false;
	}
}
#endif // ! KEYS_H
