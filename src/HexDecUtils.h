#ifndef HEXDECUTILS_H
#define HEXDECUTILS_H

#include <Arduino.h>
#include "DisplayUtils.h"

// Function declarations
String convertNfcUidToDecimal();    // Converts NFC UID to a decimal string
long hexstr_to_value(char *str, unsigned int length); // Converts hex string to a long value
void printHex(uint8_t *data, uint8_t length); // Prints hex data in readable format

#endif