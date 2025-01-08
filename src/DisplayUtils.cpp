#include "DisplayUtils.h"

String rfidUidString = "";       // 125kHz RFID UID
String nfcUidString = "";        // NFC UID
String nfcTagType = "";          // NFC Tag Type
String nfcMessageType = "";      // NFC Message Type
String nfcMessagePayload = "";   // NFC Message Payload
bool nfcPayloadPresent = false;  // Variable to check if payload is present