#include "InputControl.h"

InputControl::InputControl(int row1Pin, int row2Pin, int col1Pin, int col2Pin, int col3Pin)
    : row1Pin(row1Pin), row2Pin(row2Pin),
      col1Pin(col1Pin), col2Pin(col2Pin), col3Pin(col3Pin),
      lastDebounceTime(0) {
    rows[0] = row1Pin;
    rows[1] = row2Pin;
    cols[0] = col1Pin;
    cols[1] = col2Pin;
    cols[2] = col3Pin;

    for (int i = 0; i < 2; i++) {
        pinMode(rows[i], OUTPUT);
        digitalWrite(rows[i], LOW);
    }

    for (int i = 0; i < 3; i++) {
        pinMode(cols[i], INPUT_PULLUP);
    }
}

Button InputControl::getButtonPressed() {
    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime < debounceDelay) {
        return IDLE;
    }

    for (int r = 0; r < 2; r++) {
        digitalWrite(rows[r], HIGH);

        for (int c = 0; c < 3; c++) {
            bool isPressed = !digitalRead(cols[c]); // Invert logic for pull-up
            if (isPressed && !buttonStates[r][c]) { // Button just pressed
                buttonStates[r][c] = true;
                lastDebounceTime = currentTime;
                digitalWrite(rows[r], LOW);
                return buttonMatrix[r][c];
            } else if (!isPressed && buttonStates[r][c]) { // Button released
                buttonStates[r][c] = false;
            }
        }

        digitalWrite(rows[r], LOW);
    }

    return IDLE;
}

void InputControl::handleInput(ScreenState &currentScreen, int &itemSelected) {
    Button pressedButton = getButtonPressed();

    if (currentScreen == START_SCREEN) {
        if (pressedButton == SELECT) {
            currentScreen = MAIN_MENU;
        }
    } else if (currentScreen == MAIN_MENU) {
        if (pressedButton == UP) {
            itemSelected--;
            if (itemSelected < 0) {
                itemSelected = menuItems[MAIN].size() - 1;
            }
        } else if (pressedButton == DOWN) {
            itemSelected++;
            if (itemSelected >= menuItems[MAIN].size()) {
                itemSelected = 0;
            }
        } else if (pressedButton == SELECT) {
            if (itemSelected == 0) {
                // Wallet screen
            } else if (itemSelected == 1) {
                currentScreen = READ_FREQUENCIES_MENU;
                itemSelected = 0;
            } else if (itemSelected == 2) {
                // Write screen
            }
        }
    } else if (currentScreen == READ_FREQUENCIES_MENU) {
        if (pressedButton == UP) {
            itemSelected--;
            if (itemSelected < 0) {
                itemSelected = menuItems[READ_FREQUENCIES].size() - 1;
            }
        } else if (pressedButton == DOWN) {
            itemSelected++;
            if (itemSelected >= menuItems[READ_FREQUENCIES].size()) {
                itemSelected = 0;
            }
        } else if (pressedButton == SELECT) {
            if (itemSelected == 0) {
                currentScreen = READ_NFC_INFO_SCREEN;
                itemSelected = 0;
            } else if (itemSelected == 1) {
                currentScreen = READ_RFID_INFO_SCREEN;
                itemSelected = 0;
            }
        }
    } else if (currentScreen == READ_NFC_INFO_SCREEN) {
        if (pressedButton == SELECT) {
            currentScreen = READ_NFC_LOADING_SCREEN;
        }
    } else if (currentScreen == READ_NFC_LOADING_SCREEN) {
    } else if (currentScreen == NFC_INFO_SCREEN) {
        if(pressedButton == SELECT) {
            currentScreen = NFC_MESSAGE_SCREEN;
        }
    } else if (currentScreen == NFC_MESSAGE_SCREEN) {
        if(pressedButton == SELECT) {
            currentScreen = NFC_READ_OPTIONS_MENU;
        }
        if(pressedButton == BACK) {
            currentScreen = NFC_INFO_SCREEN;
        }
    } else if (currentScreen == NFC_READ_OPTIONS_MENU) {
        if(pressedButton == SELECT) {
            currentScreen = CRACKING_SCREEN;
        }
    } else if (currentScreen == CRACKING_SCREEN) {
    }
}

// Implement other methods as needed
