#ifndef INPUTCONTROL_H
#define INPUTCONTROL_H

#include "Arduino.h"
#include "ScreenStates.h"
#include "MenusEntries.h"

enum Button {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    SELECT,
    BACK,
    IDLE
};


class InputControl {
public:
    InputControl(int row1Pin, int row2Pin, int col1Pin, int col2Pin, int col3Pin);
    InputControl(int row1Pin, int row2Pin, int col1Pin, int col2Pin, int col3Pin, Button buttonMatrix[2][3]);
    void handleInput(ScreenState &currentScreen, int &itemSelected);
    Button getButtonPressed();
private:
    int row1Pin;
    int row2Pin;
    int col1Pin;
    int col2Pin;
    int col3Pin;
    int rows[2];
    int cols[3];
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 200; // Debounce delay in ms
    bool buttonStates[2][3];
    Button buttonMatrix[2][3] = {
        {LEFT, UP, RIGHT},
        {DOWN, BACK, SELECT}
    };
};

#endif
