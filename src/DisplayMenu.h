#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <map>
#include <vector>
#include <7941w.h>
#include "ScreenStates.h"
#include "MenusEntries.h"
#include "HexDecUtils.h"
#include "DisplayUtils.h"

class DisplayMenu {
public:
    DisplayMenu(U8G2 &display);
    void drawMenu(Menu menu, int itemSelected);
    void updateUI(ScreenState &currentScreen, int &itemSelected, GWIOT_7941W &gwiot_7941w);

private:
    U8G2 &u8g2;
    
    bool blinkState = false; // State of the blink (visible or not)
    unsigned long previousMillis = 0; // To keep track of time
    const long interval = 500; // Interval at which to blink (milliseconds)
};

#endif
