#include "HexDecUtils.h"

String convertNfcUidToDecimal() {
  // Remove any spaces from the UID String (if present)
  String hexString = nfcUidString;
  hexString.replace(" ", "");  // Remove spaces
  
  // Call hexstr_to_value to convert hex String to decimal
  long decimalValue = strtol(hexString.c_str(), NULL, 16);  // Convert hex to decimal
  
  // Convert the decimal value to a String
  String decimalString = String(decimalValue);
  
  // Return the decimal String
  return decimalString;
}

long hexstr_to_value(char *str, unsigned int length) {
  char* copy = (char *)malloc((sizeof(char) * length) + 1); 
  memcpy(copy, str, sizeof(char) * length);
  copy[length] = '\0'; 
  long value = strtol(copy, NULL, 16);
  free(copy);
  return value;
}

// Helper function to print hex data
void printHex(uint8_t *data, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        Serial.print(" 0x");
        Serial.print(data[i], HEX);
    }
    Serial.println();
}