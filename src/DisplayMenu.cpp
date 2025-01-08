#include "DisplayMenu.h"

DisplayMenu::DisplayMenu(U8G2 &display) : u8g2(display) {
}

void DisplayMenu::drawMenu(Menu menu, int itemSelected) {
    u8g2.clearBuffer();
    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    u8g2.setFont(u8g2_font_profont17_tr);

    // Get the menu items based on the menu name
    std::vector<String> items = menuItems[menu];

    // Loop through menu items
    for (int i = 0; i < items.size(); i++) {
        // Draw frame for selected or unselected item
        if (i == itemSelected) {
            u8g2.drawXBMP(2, 1 + (i * 21), 124, 20, image_frame_selected_bits);
            u8g2.setDrawColor(2);
        } else {
            u8g2.drawXBMP(2, 1 + (i * 21), 124, 20, image_frame_not_selected_bits);
        }

        // Get the current menu item text
        String menuItem = items[i];

        // Look up the icon information (width, height, and data)
        Bitmap icon = imageMap[iconMap[menuItem]];

        // Draw the icon with the correct width and height
        u8g2.drawXBMP(17, 3 + (i * 21), icon.width, icon.height, icon.data);

        // Draw the menu item text
        u8g2.drawStr(49, 16 + (i * 21), menuItem.c_str());

        // Reset draw color for next item
        u8g2.setDrawColor(1);
    }

    u8g2.sendBuffer();
}

void DisplayMenu::updateUI(ScreenState &currentScreen, int &itemSelected, GWIOT_7941W &gwiot_7941w) {
    if (currentScreen == START_SCREEN) {
        // Get the current time
        unsigned long currentMillis = millis();
        
        // Check if it's time to toggle the blink state
        if (currentMillis - previousMillis >= interval) {
                previousMillis = currentMillis; // Save the current time
                blinkState = !blinkState; // Toggle the blink state
        }
        
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.setFont(u8g2_font_profont17_tr);
        u8g2.drawStr(21, 18, "Willy NFC");

        // Only draw "Press select" when blinkState is true
        if (blinkState) {
            u8g2.setFont(u8g2_font_4x6_tr);
            u8g2.drawStr(10, 47, "Press select");
            u8g2.drawXBMP(63, 24, 64, 42, image_whale_copy_bits);
        } else {
            u8g2.drawXBMP(63, 22, 64, 42, image_whale_copy_bits);
        }

	u8g2.sendBuffer();
    } else if (currentScreen == MAIN_MENU) {
        drawMenu(MAIN, itemSelected);
    } else if (currentScreen == READ_FREQUENCIES_MENU) {
        drawMenu(READ_FREQUENCIES, itemSelected);
    } else if (currentScreen == READ_NFC_INFO_SCREEN) {
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);

        u8g2.setFont(u8g2_font_4x6_tr);
        u8g2.drawStr(14, 7, "Place the card or the tag");
        u8g2.drawStr(12, 14, "on the back and hold still");
        u8g2.drawStr(102, 56, "start");
        u8g2.drawXBMP(42, 16, 43, 47, image_nfc_read_bits);
        u8g2.drawXBMP(113, 58, 7, 5, image_arrow_curved_right_up_down_bits);

        u8g2.sendBuffer();
    } else if (currentScreen == READ_NFC_LOADING_SCREEN) {
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.setFont(u8g2_font_4x6_tr);
        u8g2.drawStr(10, 35, "Reading...");
        u8g2.drawXBMP(53, 12, 73, 52, image_whale_signal_bits);
        u8g2.sendBuffer();

        //ModuleResponse response = gwiot_7941w.read_HF_UID();
        //nfcUidString = response.getHexData();
        //response = gwiot_7941w.read_specific_block(0x00, 0x00);
        //Serial.println(response.getHexData());
        //Serial.println(String(response.command, HEX));
        HFTagInfo tagInfo = gwiot_7941w.read_HF_Card();
        nfcUidString = tagInfo.getUID();
        nfcTagType = tagInfo.getTagType();
        if(tagInfo.isNdefFormatted()) {
        nfcMessagePayload = tagInfo.getNdef().getNdefDataHex();
        nfcPayloadPresent = true;
        nfcMessageType = tagInfo.getNdef().getNdefType();
        } else {
        nfcPayloadPresent = false;
        }
        Serial.println(tagInfo.getTagData());
        Serial.println(tagInfo.getSectorsReadCount());
        Serial.println(tagInfo.getBlocksReadCount());
        Serial.println("Try keys");
        byte keyA[6] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};
        byte keyA2[6] = {0xD3, 0xF7, 0xD3, 0xF7, 0xD3, 0xF7};
        Serial.println("BLOCK 0");
        Serial.println(gwiot_7941w.read_specific_block(0x00, 0x00, 0x0A, keyA).getHexData());
        Serial.println(gwiot_7941w.read_specific_block(0x00, 0x01, 0x0A, keyA).getHexData());
        Serial.println(gwiot_7941w.read_specific_block(0x00, 0x02, 0x0A, keyA).getHexData());
        Serial.println(gwiot_7941w.read_specific_block(0x00, 0x03, 0x0A, keyA).getHexData());
        Serial.println("BLOCK 1");
        Serial.println(gwiot_7941w.read_specific_block(0x01, 0x00, 0x0A, keyA2).getHexData());
        Serial.println(gwiot_7941w.read_specific_block(0x01, 0x01, 0x0A, keyA2).getHexData());
        Serial.println(gwiot_7941w.read_specific_block(0x01, 0x02, 0x0A, keyA2).getHexData());
        Serial.println(gwiot_7941w.read_specific_block(0x01, 0x03, 0x0A, keyA2).getHexData());
        currentScreen = START_SCREEN;
    } else if (currentScreen == NFC_INFO_SCREEN) {
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.drawXBMP(117, 55, 9, 7, image_arrow_right_bits);
        u8g2.drawXBMP(0, 0, 61, 11, image_heading_frame_bits);
        u8g2.setDrawColor(2);
        u8g2.setFont(u8g2_font_profont12_tr);
        u8g2.drawStr(3, 9, "NFC info");
        u8g2.setDrawColor(1);
        u8g2.drawBox(0, 14, 20, 8);
        u8g2.setDrawColor(2);
        u8g2.setFont(u8g2_font_5x8_tr);
        u8g2.drawStr(1, 21, "UID:");
        u8g2.setDrawColor(1);
        u8g2.drawStr(0, 31, nfcUidString.c_str());
        u8g2.drawStr(0, 40, convertNfcUidToDecimal().c_str());
        u8g2.drawBox(0, 44, 44, 9);
        u8g2.setDrawColor(2);
        u8g2.drawStr(0, 51, "Tag Type:");
        u8g2.setDrawColor(1);
        u8g2.drawStr(1, 61, nfcTagType.c_str());
        u8g2.sendBuffer();
    } else if (currentScreen == NFC_MESSAGE_SCREEN) {
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.drawXBMP(117, 55, 9, 7, image_arrow_right_bits);
        u8g2.drawXBMP(0, 0, 61, 11, image_heading_frame_bits);
        u8g2.setDrawColor(2);
        u8g2.setFont(u8g2_font_profont12_tr);
        u8g2.drawStr(3, 9, "NFC info");
        u8g2.setDrawColor(1);
        u8g2.drawBox(0, 14, 80, 8);
        u8g2.setDrawColor(2);
        u8g2.setFont(u8g2_font_5x8_tr);
        u8g2.drawStr(1, 21, "Message Type:");
        u8g2.setDrawColor(1);
        u8g2.drawStr(0, 31, nfcMessageType.c_str());
        u8g2.drawBox(0, 40, 40, 9);
        u8g2.setDrawColor(2);
        u8g2.drawStr(1, 47, "Payload:");
        u8g2.setDrawColor(1);
        if(nfcMessageType == "Not NDEF formatted") {
        u8g2.drawStr(1, 57, nfcMessagePayload.c_str());
        } else if(nfcPayloadPresent) {
        u8g2.drawStr(1, 57, "Present");
        } else {
        u8g2.drawStr(1, 57, "Not Present");
        }
        u8g2.sendBuffer();
    } else if (currentScreen == NFC_READ_OPTIONS_MENU) {
        //drawMenu(NFC_READ_OPTIONS_MENU);
    } else if (currentScreen == CRACKING_SCREEN) {
        u8g2.clearBuffer();
        u8g2.setFontMode(1);
        u8g2.setBitmapMode(1);
        u8g2.setFont(u8g2_font_5x8_tr);
        u8g2.drawStr(37, 12, "Cracking...");
        u8g2.drawXBMP(4, 21, 121, 43, image_whale_shooting_bits);
        u8g2.sendBuffer();
    } else if (currentScreen == LOW_FREQ_READ) {
        
    }
    // Continue for other screens
}

// Implement other methods and move the image data here
