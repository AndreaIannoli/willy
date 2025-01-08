#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h> // library requires for IIC communication
#include <map>
#include <vector>
#include <7941w.h>
#include <DisplayMenu.h>
#include <InputControl.h>
#include "ScreenStates.h"

const int DISPLAY_ALIMENTATION = 5;

const int MAX_ITEM_LENGTH = 7; // maximum characters for the item name

int item_selected = 0; // which item in the menu is selected

ScreenState current_screen = START_SCREEN; // current screen

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display
DisplayMenu displayMenu(u8g2); // create an instance of the DisplayMenu class
InputControl inputControl(13, 12, 14, 33, 32); // create an instance of the InputControl class

bool nfcScanInProgress = false;  // Flag to indicate whether NFC scanning is in progress

const int BUFFER_SIZE = 14;
const int DATA_SIZE = 10;
const int DATA_VERSION_SIZE = 2;
const int DATA_TAG_SIZE = 8;
const int CHECKSUM_SIZE = 2;

uint8_t buffer[BUFFER_SIZE];
int buffer_index = 0;

GWIOT_7941W gwiot_7941w;

void setup(void) {
  pinMode(DISPLAY_ALIMENTATION, OUTPUT);  // Set the GPIO pin as an output
  digitalWrite(DISPLAY_ALIMENTATION, HIGH);  // Set the GPIO pin to HIGH (3.3V)
  
  // Initialize serial communication for 7941w module
  Serial.begin(115200);
  
  gwiot_7941w.init(2, 16, 17); // Initialize the 7941w module with the number of hardware serial, RX pin and TX pin

  u8g2.begin(); // start the u8g2 library
}

void loop(void) {
  inputControl.handleInput(current_screen, item_selected); // handle the input from the user
  displayMenu.updateUI(current_screen, item_selected, gwiot_7941w); // update the UI based on the current screen and selected item
}
